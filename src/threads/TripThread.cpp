
//#include <boost/log/trivial.hpp>
#include "TripThread.h"

TripThread::TripThread(MainFlow *mainFlow, Trip *trip)
        : mainFlow(mainFlow), trip(trip), validTrip(false), finished(false) {
}

Trip *TripThread::getTrip() const {
    return trip;
}

void *TripThread::calculatePath() {

    int isValidTrip = 0;
    pthread_mutex_lock(&this->mainFlow->bfsMutex);

    Bfs bfs(*this->mainFlow->map, trip->getStartPoint(), trip->getEndPoint());

    isValidTrip = bfs.get_route();

    //validTrip = this->getMainFlow()->getErrorHandler().ValidatePath(bfs);

    if (isValidTrip == 1) {

        trip->setTripRoute(bfs.getShortestPath());
        this->setValidTrip(true);
       // BOOST_LOG_TRIVIAL(trace) << "Finished calculating path.";

    } else {

        this->setValidTrip(false);
       // BOOST_LOG_TRIVIAL(trace) << "Path is invalid";

    }

    this->setFinished();
   // BOOST_LOG_TRIVIAL(trace) << "Set as finished";
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
    this->task = task;
}

TripThread::~TripThread() {

    delete this->task;
}

bool TripThread::isValidTrip() const {
    return validTrip;
}

void TripThread::setValidTrip(bool isValidTrip) {
    TripThread::validTrip = isValidTrip;
}

bool TripThread::isFinished() {

    return this->finished;
}

void TripThread::setFinished() {

    this->finished = true;
}
