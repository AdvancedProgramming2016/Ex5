

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include <queue>
#include "MainFlow.h"
class MainFlow;

class ClientThread {

private:

    MainFlow *mainFlow;
    Driver *driver;
    int threadCommand;
    bool firstTimeFlag;
    unsigned int threadId;
    pthread_t thread;
    int descriptor;

public:
    int getThreadCommand() const;

    void setThreadCommand(int threadCommand);

public:

    ClientThread(MainFlow *mainFlow, unsigned int threadId);

    /*
     * Return mainflow object
     */
    MainFlow *getMainFlow();

    /*
     * Listen to socket and receive driver.
     */
    void * listenToSocketForDriver();

    /*
     * Returns thread id
     */
    unsigned int getThreadId() const;

    /*
     * Recevies the receiveDriverMutex and thread and send to listenToSocketForDriver func.
     */
    static void *sendToListenToSocketForDriver(void *clientThread);

    /*
     * Returns thread
     */
    pthread_t getThread() const;

    /*
     * Sets the thread member
     */
    void setThread(pthread_t thread);

    /*
     * Sets the socket descriptor
     */
    void setDescriptor(int descriptor);

    /*
     * Gets the socket descriptor
     */
    int getDescriptor() const;

};


#endif //EX4_CLIENTTHREAD_H
