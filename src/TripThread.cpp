
//#include <boost/log/trivial.hpp>
#include "TripThread.h"

TripThread::TripThread(MainFlow *mainFlow, Trip *trip)
        : mainFlow(mainFlow), trip(trip) {
}

pthread_t TripThread::getThread() const {
    return thread;
}

Trip *TripThread::getTrip() const {
    return trip;
}

void *TripThread::calculatePath() {

    pthread_mutex_lock(&this->mainFlow->bfsMutex);

    Bfs bfs(*this->mainFlow->map, trip->getStartPoint(), trip->getEndPoint()); //TODO not generic because it takes Grid, and bot Graph

    std::cout << "Starting to calculate trip:" << this->trip->getRideId() << std::endl;
    bfs.get_route();
    std::cout << "Finished to calculate trip:" << this->trip->getRideId() << std::endl;

    //BOOST_LOG_TRIVIAL(trace) << "Finished calculating path.";

    //BOOST_LOG_TRIVIAL(trace) << "Finished cleaning path.";

    trip->setTripRoute(bfs.getShortestPath());

    pthread_mutex_unlock(&this->mainFlow->bfsMutex);

    //BOOST_LOG_TRIVIAL(trace) << "Exiting trip thread.";

    pthread_exit(NULL);
}

void *TripThread::callCalculatePath(void *param) {
    //BOOST_LOG_TRIVIAL(trace) << "Calculating path.";
    return ((TripThread *) param)->calculatePath();
}

MainFlow *TripThread::getMainFlow() const {
    return mainFlow;
}

void TripThread::setThread(pthread_t thread) {
    TripThread::thread = thread;
}
