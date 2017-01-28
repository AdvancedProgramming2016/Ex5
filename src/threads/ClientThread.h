

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include <queue>
#include "../control/MainFlow.h"
class MainFlow;

/**
 * The class handles an individual client which connects to the server.
 * Runs its own thread.
 */
class ClientThread {

private:

    MainFlow *mainFlow;
    Driver *driver;
    int threadCommand;
    unsigned int threadId;
    pthread_t thread;
    int descriptor;

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

    /*
     * Returns thread command.
     */
    int getThreadCommand() const;

    /*
     * Sets thread command.
     */
    void setThreadCommand(int threadCommand);

};


#endif //EX4_CLIENTTHREAD_H
