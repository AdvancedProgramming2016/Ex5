
//#include <boost/log/trivial.hpp>
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

    this->descriptor = this->mainFlow->getSocket()->callAccept();

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Starting thread function";

    pthread_mutex_lock(&this->getMainFlow()->getMutexReceiveDriver());
    this->getMainFlow()->getSocket()->receiveData(buffer, 1024,
                                                  this->getDescriptor());

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Received driver";

    this->getMainFlow()->getSerializer().deserialize(buffer, sizeof(buffer),
                                                     this->driver);
    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Driver id:" << driver->getDriverId();

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Desirialied driver";

    this->getMainFlow()->getTaxiCenter()->addDriver(this->driver);

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Sending to client vehicle";
    getMainFlow()->sendToSocketVehicle(driver->getVehicleId(),
                                       descriptor);

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Waiting for first command from server.";

    pthread_mutex_unlock(&this->getMainFlow()->getMutexReceiveDriver());

    while (true) {

        if (this->getThreadCommand() == 9) {

            pthread_mutex_lock(&this->getMainFlow()->getSendCommandMutex());

            //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
            //                        << " Performed task 9";

            //BOOST_LOG_TRIVIAL(debug) << "Program time: "
            //                       << this->mainFlow->getTaxiCenter()->getClock()->getTime();

            this->getMainFlow()->performTask9(this->driver, this->getDescriptor());

            this->threadCommand = 0;

            pthread_mutex_unlock(&this->getMainFlow()->getSendCommandMutex());

        } else if (this->getThreadCommand() == 7) {

            (this->mainFlow->getSocket())->sendData("exit",
                                                    this->getDescriptor());
            //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
            //                        << " Exiting current thread.";
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
