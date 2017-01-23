
#include <boost/log/trivial.hpp>
#include "TripThread.h"

TripThread::TripThread(MainFlow *mainFlow, Trip *trip)
        : mainFlow(mainFlow), trip(trip) {
}

Trip *TripThread::getTrip() const {
    return trip;
}

void *TripThread::calculatePath() {

    pthread_mutex_lock(&this->mainFlow->bfsMutex);

    Bfs bfs(*this->mainFlow->map, trip->getStartPoint(), trip->getEndPoint());

    bfs.get_route();

    trip->setTripRoute(bfs.getShortestPath());

    BOOST_LOG_TRIVIAL(trace) << "Finished calculating path.";

    pthread_mutex_unlock(&this->mainFlow->bfsMutex);

    //BOOST_LOG_TRIVIAL(trace) << "Exiting trip thread.";

    //pthread_mutex_lock(&this->getMainFlow()->getThreadPool()->getTaskCounterMutex());
    //this->getMainFlow()->getThreadPool()->decreaseTaskCounter();
    //pthread_mutex_unlock(&this->getMainFlow()->getThreadPool()->getTaskCounterMutex());
}

void *TripThread::callCalculatePath(void *param) {
    //BOOST_LOG_TRIVIAL(trace) << "Calculating path.";
    return ((TripThread *) param)->calculatePath();
}

MainFlow *TripThread::getMainFlow() const {
    return mainFlow;
}

Task *TripThread::getTask() {
    return task;
}

void TripThread::setTask(Task *task) {
    TripThread::task = task;
}

TripThread::~TripThread() {

    delete this->task;
}
