

#ifndef EX4_CLIENTTHREAD_H
#define EX4_CLIENTTHREAD_H

#include "MainFlow.h"
class MainFlow;

class ClientThread {

private:

    MainFlow *mainFlow;
    pthread_mutex_t mutex;

public:

    ClientThread(pthread_mutex_t mutex, MainFlow *mainFlow);
    MainFlow *getMainFlow();
    pthread_mutex_t getMutex();

};


#endif //EX4_CLIENTTHREAD_H
