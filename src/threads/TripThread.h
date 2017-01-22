
#ifndef EX4_TRIPTHREAD_H
#define EX4_TRIPTHREAD_H


#include <sys/types.h>
#include "../taxi/Trip.h"
#include "../control/MainFlow.h"
class MainFlow;

class TripThread {

private:

    Trip *trip;
    MainFlow *mainFlow;
    pthread_t thread;

public:

    /*
     * Gets mainflow object.
     */
    MainFlow *getMainFlow() const;

    /*
     * Ctor
     */
    TripThread(MainFlow *mainFlow, Trip *trip);

    /*
     * Add thread.
     */
    void setThread(pthread_t thread);

    /*
     * Get trip object.
     */
    Trip *getTrip() const;

    /*
     * Get thread object.
     */
    pthread_t getThread() const;

    /*
     * Function calculates shortest path to dest.
     */
    void *calculatePath();

    /*
     * Calls calculate path.
     */
    static void *callCalculatePath(void *param);
};


#endif //EX4_TRIPTHREAD_H
