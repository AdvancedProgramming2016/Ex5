
#include <boost/log/trivial.hpp>
#include "ClientThread.h"
#include "../sockets/Tcp.h"


ClientThread::ClientThread(MainFlow *mainFlow, unsigned int threadId)
        : threadCommand(0), threadId(threadId), descriptor(0) {
    this->mainFlow = mainFlow;
}

MainFlow *ClientThread::getMainFlow() {
    return this->mainFlow;
}


void *ClientThread::sendToListenToSocketForDriver(void *clientThread) {
    return (((ClientThread *) clientThread)->listenToSocketForDriver());
}

void *ClientThread::listenToSocketForDriver() {


    char   buffer[1024];
    Driver *driver;

    //put this under mutex
    this->descriptor = this->mainFlow->getSocket()->callAccept();
    //pthread_mutex_t addDriverMtx;

    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Starting thread function";

    pthread_mutex_lock(&this->getMainFlow()->getMutex());
    this->getMainFlow()->getSocket()->receiveData(buffer, 1024, this->getDescriptor());
    pthread_mutex_unlock(&this->getMainFlow()->getMutex());

    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Received driver";
    // Allow one thread to add driver at a time
    //pthread_mutex_lock(&addDriverMtx);

    pthread_mutex_lock(&this->getMainFlow()->getMutex());
    this->getMainFlow()->getSerializer().deserialize(buffer, sizeof(buffer),
                                                     driver);
    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Driver id:" << driver->getDriverId();

    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Desirialied driver";
    this->getMainFlow()->getTaxiCenter()->addDriver(driver);


    //BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
    //                        << " Sending port";
    // Send client new port to communicate with
    //int    newPort = this->getMainFlow()->getVacantPort();
    //this->getMainFlow()->getSocket()->sendData(
    //       boost::lexical_cast<string>(newPort));
    //delete this->getMainFlow()->getSocket();
//    Socket * s = this->getMainFlow()->getSocket();
//    s = new Tcp(1, 5555);
//    s->initialize();

    //char temp[1024];
    // Create new socket for new client
    //this->socket = new Tcp(1, 5555);

    //this->descriptor = this->mainFlow->getSocket()->callAccept();
   // this->getMainFlow()->insertClientSocket(
    //        this->socket); // Add new socket to vector.

//    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
//                            << " Initializing new port: "
//                            << this->getMainFlow()->getVacantPort();
//    this->getMainFlow()->increaseVacantPort();

    //pthread_mutex_unlock(&addDriverMtx);

    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Sending to client vehicle";
    getMainFlow()->sendToSocketVehicle(driver->getVehicleId(),
                                       descriptor);

    BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                            << " Waiting for first command from server.";

    pthread_mutex_unlock(&this->getMainFlow()->getMutex());

    while (true) {

        if (this->getThreadCommand() == 9) {

            pthread_mutex_lock(&this->getMainFlow()->getMutex());
            BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                                    << " Performed task 9";
            this->getMainFlow()->performTask9(this->getDescriptor());
            this->threadCommand = 0;
            pthread_mutex_unlock(&this->getMainFlow()->getMutex());

        } else if (this->getThreadCommand() == 7) {

            (this->mainFlow->getSocket())->sendData("exit", this->getDescriptor());
            BOOST_LOG_TRIVIAL(info) << "Thread:" << this->getThreadId()
                                    << " Exiting current thread.";
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

unsigned int ClientThread::getThreadId() const {
    return threadId;
}

void ClientThread::setDescriptor(int descriptor) {
    ClientThread::descriptor = descriptor;
}

int ClientThread::getDescriptor() const {
    return descriptor;
}
