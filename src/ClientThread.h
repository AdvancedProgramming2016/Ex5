

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include "MainFlow.h"
class MainFlow;

class ClientThread {

private:

    MainFlow *mainFlow;
    pthread_mutex_t mutex;
    int threadCommand;
    Socket *socket;
    pthread_t thread;

public:
    int getThreadCommand() const;

    void setThreadCommand(int threadCommand);

public:

    ClientThread(pthread_mutex_t mutex, MainFlow *mainFlow);
    MainFlow *getMainFlow();
    pthread_mutex_t getMutex();
    /*
     * Listen to socket and receive driver.
     */
    void * listenToSocketForDriver(pthread_mutex_t mtx);

    /*
     * Recevies the mutex and thread and send to listenToSocketForDriver func.
     */
    static void *sendToListenToSocketForDriver(void *clientThread);

    pthread_t getThread() const;

    void setThread(pthread_t thread);


};


#endif //EX4_CLIENTTHREAD_H
