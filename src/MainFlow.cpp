
#include "MainFlow.h"
#include "../sockets/Tcp.h"
#include "TripThread.h"
#include <boost/log/trivial.hpp>
#include <cstdlib>
#include <pthread.h>

MainFlow::MainFlow(Socket *socket, int operationNumber) {

    this->socket = socket;
    BOOST_LOG_TRIVIAL(info) << "Opening main socket.";
    this->socket->initialize();
    this->operationNumber = &operationNumber;
    //this->vacantPort      = 42345;

    //this->socket->initialize();
    pthread_mutex_init(&this->receiveDriverMutex, NULL);
    pthread_mutex_init(&this->sendCommandMutex, NULL);
    pthread_mutex_init(&this->bfsMutex, NULL);

}

MainFlow::~MainFlow() {

    pthread_mutex_destroy(&this->receiveDriverMutex);
    pthread_mutex_destroy(&this->sendCommandMutex);
    pthread_mutex_destroy(&this->bfsMutex);

    BOOST_LOG_TRIVIAL(info) << "Deleting all the open sockets.";
    delete this->socket;

    // Delete all the client opened sockets
//    for (int i = 0; i < this->getSocketVector().size(); i++) {
  //      delete this->getSocketVector().at(i);
    //}
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

    int       retVal = 0;
    pthread_t pthread;

    TripThread *tripThread = new TripThread(this, trip);

    retVal = pthread_create(&pthread, NULL, &TripThread::callCalculatePath,
                            tripThread);

    if (retVal != 0) {

        BOOST_LOG_TRIVIAL(error) << "ERROR: failed to create trip thread.";
    }

    tripThread->setThread(pthread);

    BOOST_LOG_TRIVIAL(trace) << "TRACE: created trip thread.";

    //TripThread *tripThread = new TripThread(this, trip, pthread);


    this->getTaxiCenter()->getTripThreads().push_back(tripThread);
    this->taxiCenter->addTrip(trip);

}

TaxiCenter *MainFlow::getTaxiCenter() const {
    return taxiCenter;
}

void MainFlow::sendToSocketVehicle(unsigned int vehicleId,
                                   int descriptor) {

    Vehicle     *vehicle = this->getDriverVehicle(vehicleId);
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    socket->sendData(serialVehicle, descriptor);
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


void MainFlow::selectDrivers(int numOfDrivers) {

    // Receive driver objects from client
    for (int i = 0; i < numOfDrivers; i++) {

        pthread_t currThread;

        // TODO: delete all the client threads
        ClientThread *clientThread = new ClientThread(this, i);
        this->addClientThread(clientThread);

        // Init thread for driver
        pthread_create(&currThread, NULL,
                       ClientThread::sendToListenToSocketForDriver,
                       (void *) (clientThread));


        BOOST_LOG_TRIVIAL(info) << "New thread created with thread id: "
                                << clientThread->getThreadId();
        clientThread->setThread(currThread);

        // Wait for thread
        // TODO: Check whether necessary
        //pthread_exit(currThread, NULL);
    }
}

void MainFlow::performTask9(Driver *driver, int descriptor) {

    //pthread_mutex_t assignTripMtx;

    //pthread_mutex_lock(&assignTripMtx);

    // Move all the taxis one step
    this->getTaxiCenter()->moveOneStep(driver,
            *(this->getSocket()), this->getSerializer(), descriptor);

    // Check that all the trips that need to start are attached
    // to a driver
    this->getTaxiCenter()->assignTrip(driver, *this->getSocket(), this->getSerializer(),
                                      descriptor);

   // pthread_mutex_unlock(&assignTripMtx);
}

unsigned int MainFlow::getVacantPort() {
    return this->vacantPort;
}

void MainFlow::increaseVacantPort() {
    ++(this->vacantPort);
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

void MainFlow::sendClientNewPort(unsigned int newPort) {

    // Case newPort to string and send the new socket to client
    // this->getSocket()->sendData(boost::lexical_cast<string>(newPort));
}

Grid *MainFlow::getMap() const {
    return map;
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

pthread_mutex_t &MainFlow::getMutexReceiveDriver() {
    return receiveDriverMutex;
}

pthread_mutex_t &MainFlow::getSendCommandMutex()  {
    return sendCommandMutex;
}

void MainFlow::clockSleep() {

    int i = 0;
    while(i < this->getClientThreadVector().size()){

        if(this->getClientThreadVector()[i]->getThreadCommand() == 0){
            i++;
        }
    }

}
