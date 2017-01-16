

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include "MainFlow.h"
class MainFlow;

class ClientThread {

private:

    MainFlow *mainFlow;
    int threadCommand;
    unsigned int threadId;
    pthread_t thread;
    int descriptor;

public:
    int getThreadCommand() const;

    void setThreadCommand(int threadCommand);

public:

    ClientThread(MainFlow *mainFlow, unsigned int threadId);

    MainFlow *getMainFlow();

    /*
     * Listen to socket and receive driver.
     */
    void * listenToSocketForDriver();


    unsigned int getThreadId() const;

    /*
     * Recevies the mutex and thread and send to listenToSocketForDriver func.
     */
    static void *sendToListenToSocketForDriver(void *clientThread);

    pthread_t getThread() const;

    void setThread(pthread_t thread);

    void setDescriptor(int descriptor);

    int getDescriptor() const;


};


#endif //EX4_CLIENTTHREAD_H
