
//#include <boost/log/trivial.hpp>
#include "ClientThread.h"
#include "../sockets/Tcp.h"

ClientThread::ClientThread(MainFlow *mainFlow, unsigned int threadId) {
    this->mainFlow      = mainFlow;
    this->threadId      = threadId;
    this->descriptor    = 0;
    this->threadCommand = 0;
    this->firstTimeFlag = true;
}

MainFlow *ClientThread::getMainFlow() {
    return this->mainFlow;
}

void *ClientThread::sendToListenToSocketForDriver(void *clientThread) {
    return (((ClientThread *) clientThread)->listenToSocketForDriver());
}

void *ClientThread::listenToSocketForDriver() {

    while(true){
        if(this->mainFlow->getStartOrder() != this->getThreadId()){
            continue;
        }
        this->mainFlow->setStartOrder(this->mainFlow->getStartOrder() + 1);
        break;
    }
    pthread_mutex_lock(&this->getMainFlow()->getMutexReceiveDriver());

    std::cout << "Thread:" << this->getThreadId()
                            << " Starting thread function\n";
    char buffer[1024];

    this->descriptor = this->mainFlow->getSocket()->callAccept();

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Starting thread function";


    this->getMainFlow()->getSocket()->receiveData(buffer, 1024,
                                                  this->getDescriptor());

    //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
    //                        << " Received driver";

    this->getMainFlow()->getSerializer().deserialize(buffer, sizeof(buffer),
                                                     this->driver);
    std::cout << "thread:" << this->getThreadId() << "has driver:" << this->driver->getDriverId() << std::endl;
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

            if (this->getThreadCommand() == 9 && this->mainFlow->getOrder() == this->getThreadId()) {

                pthread_mutex_lock(&this->getMainFlow()->getSendCommandMutex());
                std::cout << "Thread" << this->getThreadId() << " performing task 9\n";
                std::cout << "Time" << this->mainFlow->getTaxiCenter()->getClock()->getTime() << std::endl;

                //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
                //                        << " Performed task 9";

                //BOOST_LOG_TRIVIAL(debug) << "Program time: "
                //                       << this->mainFlow->getTaxiCenter()->getClock()->getTime();

                this->getMainFlow()->performTask9(this->driver,
                                                  this->getDescriptor());

                this->threadCommand = 0;
                this->mainFlow->setOrder(this->mainFlow->getOrder() + 1);

                if(this->mainFlow->getClientThreadVector().size() == this->mainFlow->getOrder()){
                    this->mainFlow->setOrder(0);
                }
                std::cout << "Thread" << this->getThreadId() << " finished performing task 9\n";
                std::cout << "Time" << this->mainFlow->getTaxiCenter()->getClock()->getTime() << std::endl;;
                pthread_mutex_unlock(
                        &this->getMainFlow()->getSendCommandMutex());

            } else if (this->getThreadCommand() == 7) {

                (this->mainFlow->getSocket())->sendData("exit",
                                                        this->getDescriptor());
                //BOOST_LOG_TRIVIAL(debug) << "Thread:" << this->getThreadId()
                //                        << " Exiting current thread.";
                this->mainFlow->setOrder(this->mainFlow->getOrder() + 1);
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
