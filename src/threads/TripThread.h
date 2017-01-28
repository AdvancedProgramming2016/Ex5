
#ifndef EX4_TRIPTHREAD_H
#define EX4_TRIPTHREAD_H


#include <sys/types.h>
#include "../taxi/Trip.h"
#include "../control/MainFlow.h"

class MainFlow;

class Task;

/**
 * The class takes care of the trip thread calculation.
 * Performs the bfs algorithm.
 */
class TripThread {

private:

    Trip     *trip;
    MainFlow *mainFlow;
    Task     *task;
    bool     validTrip;
    bool     finished;

public:

    /*
    * Ctor
    */
    TripThread(MainFlow *mainFlow, Trip *trip);

    /*
     * Destructor.
     */
    virtual ~TripThread();

    /*
     * Gets mainFlow object.
     */
    MainFlow *getMainFlow() const;

    /*
     * Get trip object.
     */
    Trip *getTrip() const;

    /*
     * Function calculates shortest path to dest.
     */
    void *calculatePath();

    /*
     * Calls calculate path.
     */
    static void *callCalculatePath(void *param);

    /*
     * Returns tha task object.
     */
    Task *getTask();

    /*
     * Sets the task.
     */
    void setTask(Task *task);

    /*
     * Return is the trip valid.
     */
    bool isValidTrip() const;

    /*
     * Set is the trip valid.
     */
    void setValidTrip(bool isValidTrip);

    /*
    * Returns if the task was finished.
    */
    bool isFinished();

    /*
     * Sets the task as finished.
     */
    void setFinished();
};


#endif //EX4_TRIPTHREAD_H
