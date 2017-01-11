
#include "MainFlow.h"
#include "../sockets/Tcp.h"
#include <boost/log/trivial.hpp>
#include <cstdlib>
#include <pthread.h>

MainFlow::MainFlow(Socket *socket, int *operationNumber) {

    this->socket = socket;
    BOOST_LOG_TRIVIAL(info) << "Opening main socket.";
    this->socket->initialize();
    this->operationNumber = operationNumber;
    this->vacantPort = 42345;
}

MainFlow::~MainFlow() {

    BOOST_LOG_TRIVIAL(info) << "Deleting all the open sockets.";
    delete this->socket;

    // Delete all the client opened sockets
    for (int i = 0; i < this->getSocketVector().size(); i++) {
        delete this->getSocketVector().at(i);
    }
}

int *MainFlow::getOperationNumber() {
    return this->operationNumber;
}

void MainFlow::createMap(Grid *grid) {
    this->map = grid;
}

void MainFlow::createTaxiCenter(Point *location) {

    this->taxiCenter = new TaxiCenter(location);
}

void MainFlow::createDriver(Driver *driver) {

    taxiCenter->addDriver(driver);
}

void MainFlow::createVehicle(Vehicle *vehicle) {

    taxiCenter->addVehicle(vehicle);
}

void MainFlow::createTrip(Trip *trip) {

    Bfs bfs(this->map, trip->getStartPoint(), trip->getEndPoint());

    // Calculate shortest route
    bfs.get_route();
    cleanGrid();

    // Set trip route
    trip->setTripRoute(bfs.getShortestPath());

    // Push new trip to trip queue
    this->taxiCenter->addTrip(trip);

}

TaxiCenter *MainFlow::getTaxiCenter() const {
    return taxiCenter;
}

void MainFlow::sendToSocketVehicle(unsigned int vehicleId) {

    Vehicle *vehicle = this->getDriverVehicle(vehicleId);
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    this->getSocket()->sendData(serialVehicle);
}

Vehicle *MainFlow::getDriverVehicle(unsigned int vehicleId) {

    std::vector<Vehicle *> vehicles = this->getTaxiCenter()->
            getVehicles();
    for (int i = 0; i < vehicles.size(); ++i) {

        if (vehicles[i]->getVehicleId() == vehicleId) {

            return vehicles[i];
        }
    }
}

Socket *MainFlow::getSocket() {
    return this->socket;
}

Serializer MainFlow::getSerializer() {
    return this->serializer;
}

void *MainFlow::sendToListenToSocketForDriver(void *clientThread) {
    return (((ClientThread *) clientThread)->getMainFlow()->listenToSocketForDriver(
            ((ClientThread *) clientThread)->getMutex()));
}

void *MainFlow::listenToSocketForDriver(pthread_mutex_t mtx) {

    char buffer[1024];
    Driver *driver;
    pthread_mutex_t addDriverMtx;

    this->getSocket()->reciveData(buffer, 1024);

    // Allow one thread to add driver at a time
    pthread_mutex_lock(&addDriverMtx);

    this->getSerializer().deserialize(buffer, sizeof(buffer), driver);

    this->getTaxiCenter()->addDriver(driver);

    // Unlock mutex
    pthread_mutex_unlock(&addDriverMtx);

    // Send client new port to communicate with
    this->getSocket()->sendData(
            boost::lexical_cast<string>(this->getVacantPort()));

    // Create new socket for new client
    Socket *newSocket = new Tcp(true, this->getVacantPort());
    newSocket->initialize();
    this->insertClientSocket(newSocket); // Add new socket to vector.
    BOOST_LOG_TRIVIAL(info) << "Initializing new port: "
                            << this->getVacantPort();

    this->increaseVacantPort();

    BOOST_LOG_TRIVIAL(info) << "Sending to client vehicle";
    newSocket->sendData(boost::lexical_cast<string>(driver->getVehicleId()));

    // Perform user selection unless 7 was selected
    while (*(this->getOperationNumber()) != 7) {

        // Wait for server command to continue and write to log
        BOOST_LOG_TRIVIAL(info) << "Waiting for command from server.";
        pthread_mutex_lock(&mtx);

        this->performTask9(newSocket);

    }

// TODO: Understand how to send to specific socket
    newSocket->sendData("exit");

// Kill thread
    BOOST_LOG_TRIVIAL(info) << "Exiting current thread.";
    pthread_exit(NULL);

}

void MainFlow::selectDrivers(int numOfDrivers) {

    // Receive driver objects from client
    for (int i = 0; i < numOfDrivers; i++) {

        pthread_t currThread;
        pthread_mutex_t currMtx;

        //pthread_mutex_lock(&currMtx);
        ClientThread clientThread(currMtx, this);

        // Init thread for driver
        pthread_create(&currThread, NULL,
                       sendToListenToSocketForDriver,
                       (void *) (&clientThread));

        BOOST_LOG_TRIVIAL(info) << "New thread created with thread id: "
                                << currThread;

        this->addThreadToVector(currThread);

        // Wait for thread
        pthread_join(currThread, NULL);
    }
}

void MainFlow::performTask9(Socket *currSocket) {

    pthread_mutex_t assignTripMtx;

    pthread_mutex_lock(&assignTripMtx);

    // Check that all the trips that need to start are attached
    // to a driver
    this->getTaxiCenter()->assignTrip(
            *(currSocket), this->getSerializer());

    // Move all the taxis one step
    this->getTaxiCenter()->moveOneStep(
            *(currSocket), this->getSerializer());

    pthread_mutex_unlock(&assignTripMtx);
}

unsigned int MainFlow::getVacantPort() {
    return this->vacantPort;
}

void MainFlow::increaseVacantPort() {
    ++(this->vacantPort);
}


void MainFlow::sendClientNewPort(unsigned int newPort) {

    // Case newPort to string and send the new socket to client
    this->getSocket()->sendData(boost::lexical_cast<string>(newPort));
}

std::vector<Socket *> MainFlow::getSocketVector() {
    return this->socketVector;
}

void MainFlow::insertClientSocket(Socket *socket) {
    this->socketVector.push_back(socket);
}

std::vector<pthread_mutex_t> MainFlow::getMutexs() {
    return this->mutexs;
}

void MainFlow::addMutex(pthread_mutex_t mtx) {
    this->mutexs.push_back(mtx);
}

Grid *MainFlow::getMap() const {
    return map;
}

std::vector<pthread_t> MainFlow::getThreadsVector() {
    return this->threads;
}

void MainFlow::addThreadToVector(pthread_t thread) {
    this->threads.push_back(thread);
}

void MainFlow::exitSystem() {

    delete this->taxiCenter;
    delete this->map;

    //exit the system
    exit(0);
}

void MainFlow::cleanGrid() {

    Vertex *v;

    for (int i = 0; i < this->map->get_edges().size(); ++i) {

        v = this->map->get_vertex(map->get_edges()[i].getM_point());

        if (!this->getMap()->isObstacle(v->getM_point())) {

            v->set_unvisited();
        }

        v->setFather(0);
    }
}