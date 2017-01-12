

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include "MainFlow.h"
class MainFlow;

class ClientThread {

private:

    MainFlow *mainFlow;
    int threadCommand;
    Socket *socket;
    pthread_t thread;

public:
    int getThreadCommand() const;

    void setThreadCommand(int threadCommand);

public:

    ClientThread(MainFlow *mainFlow);

    MainFlow *getMainFlow();

    /*
     * Listen to socket and receive driver.
     */
    void * listenToSocketForDriver();

    /*
     * Recevies the mutex and thread and send to listenToSocketForDriver func.
     */
    static void *sendToListenToSocketForDriver(void *clientThread);

    pthread_t getThread() const;

    void setThread(pthread_t thread);


};


#endif //EX4_CLIENTTHREAD_H
