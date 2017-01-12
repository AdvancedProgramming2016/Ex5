
#include "MainFlow.h"
#include "../sockets/Tcp.h"
#include <boost/log/trivial.hpp>
#include <cstdlib>
#include <pthread.h>

MainFlow::MainFlow(Socket *socket, int operationNumber) {

    this->socket = socket;
    BOOST_LOG_TRIVIAL(info) << "Opening main socket.";
    this->socket->initialize();
    this->operationNumber = &operationNumber;
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

void MainFlow::sendToSocketVehicle(unsigned int vehicleId, Socket *socket) {

    Vehicle *vehicle = this->getDriverVehicle(vehicleId);
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    socket->sendData(serialVehicle);
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

void MainFlow::addClientThread(ClientThread *clientThread) {
    this->clientThreadVector.push_back(clientThread);
}

std::vector<ClientThread *> MainFlow::getClientThreadVector() {
    return this->clientThreadVector;
}

void MainFlow::selectDrivers(int numOfDrivers) {

    // Receive driver objects from client
    for (int i = 0; i < numOfDrivers; i++) {

        pthread_t currThread;

        // TODO: delete all the client threads
        ClientThread *clientThread = new ClientThread(this);
        this->addClientThread(clientThread);

        // Init thread for driver
        pthread_create(&currThread, NULL,
                       ClientThread::sendToListenToSocketForDriver,
                       (void *) (clientThread));

        BOOST_LOG_TRIVIAL(info) << "New thread created with thread id: "
                                << currThread;
        clientThread->setThread(currThread);
        this->addThreadToVector(currThread);

        // Wait for thread
        // TODO: Check whether necessary
        //pthread_exit(currThread, NULL);
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