
#ifndef EX4_TRIPTHREAD_H
#define EX4_TRIPTHREAD_H


#include <sys/types.h>
#include "Trip.h"
#include "MainFlow.h"
class MainFlow;

class TripThread {

private:

    Trip *trip;
    MainFlow *mainFlow;
    pthread_t thread;

public:

    MainFlow *getMainFlow() const;

    TripThread(MainFlow *mainFlow, Trip *trip);

    void setThread(pthread_t thread);

    Trip *getTrip() const;

    pthread_t getThread() const;

    void *calculatePath();
    
    static void *callCalculatePath(void *param);
};


#endif //EX4_TRIPTHREAD_H
