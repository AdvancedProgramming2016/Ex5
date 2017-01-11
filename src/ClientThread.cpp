//
// Created by commanderx on 10/01/17.
//

#include "ClientThread.h"


ClientThread::ClientThread(pthread_mutex_t mutex, MainFlow *mainFlow) {
    this->mutex = mutex;
}

MainFlow *ClientThread::getMainFlow() {
    return this->mainFlow;
}

pthread_mutex_t ClientThread::getMutex() {
    return this->mutex;
}
