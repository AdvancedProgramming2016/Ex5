
#include <boost/log/trivial.hpp>
#include "ClientThread.h"
#include "../sockets/Tcp.h"


ClientThread::ClientThread(MainFlow *mainFlow)
        : threadCommand(0) {
    this->mainFlow = mainFlow;
}

MainFlow *ClientThread::getMainFlow() {
    return this->mainFlow;
}


void *ClientThread::sendToListenToSocketForDriver(void *clientThread) {
    return (((ClientThread *) clientThread)->listenToSocketForDriver());
}

void *ClientThread::listenToSocketForDriver() {

    char buffer[1024];
    Driver *driver;
    pthread_mutex_t addDriverMtx;

    BOOST_LOG_TRIVIAL(info) << "Starting thread function";

    this->getMainFlow()->getSocket()->reciveData(buffer, 1024);

    BOOST_LOG_TRIVIAL(info) << "Received driver";
    // Allow one thread to add driver at a time
    pthread_mutex_lock(&addDriverMtx);

    this->getMainFlow()->getSerializer().deserialize(buffer, sizeof(buffer),
                                                     driver);

    BOOST_LOG_TRIVIAL(info) << "Desirialied driver";
    this->getMainFlow()->getTaxiCenter()->addDriver(driver);


    BOOST_LOG_TRIVIAL(info) << "Sending port";
    // Send client new port to communicate with
    int newPort = this->getMainFlow()->getVacantPort();
    this->getMainFlow()->getSocket()->sendData(
            boost::lexical_cast<string>(newPort));

    //char temp[1024];
    // Create new socket for new client
    this->socket = new Tcp(true, newPort);
    this->socket->initialize();
    this->getMainFlow()->insertClientSocket(
            this->socket); // Add new socket to vector.
    BOOST_LOG_TRIVIAL(info) << "Initializing new port: "
                            << this->getMainFlow()->getVacantPort();

    this->getMainFlow()->increaseVacantPort();

    pthread_mutex_unlock(&addDriverMtx);

    BOOST_LOG_TRIVIAL(info) << "Sending to client vehicle";
    getMainFlow()->sendToSocketVehicle(driver->getVehicleId(), this->socket);

    BOOST_LOG_TRIVIAL(info) << "Waiting for first command from server.";

    while(true) {


        if (this->getThreadCommand() == 9) {

            BOOST_LOG_TRIVIAL(info) << "Performed task 9";
            this->getMainFlow()->performTask9(this->socket);
            this->threadCommand = 0;
        } else if (this->getThreadCommand() == 7) {

            this->socket->sendData("exit");
            BOOST_LOG_TRIVIAL(info) << "Exiting current thread.";
            pthread_exit(NULL);
        }

    }
}

int ClientThread::getThreadCommand() const {
    return threadCommand;
}

void ClientThread::setThreadCommand(int threadCommand) {
    ClientThread::threadCommand = threadCommand;
}

pthread_t ClientThread::getThread() const {
    return thread;
}

void ClientThread::setThread(pthread_t thread) {
    ClientThread::thread = thread;
}
