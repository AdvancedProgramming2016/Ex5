
#include "MainFlow.h"
#include <cstdlib>

void MainFlow::createMap(Grid *grid) {
    this->map = grid;
    this->clock = new Clock();
}

void MainFlow::createTaxiCenter(Point *location) {

    this->taxiCenter = new TaxiCenter(location);
}

void MainFlow::createDriver(Driver *driver) {

    taxiCenter->addDriver(driver);
    taxiCenter->createTaxi(driver);
}

void MainFlow::createVehicle(Vehicle *vehicle) {

    taxiCenter->addVehicle(vehicle);
}

void MainFlow::createTrip(Trip *trip) {

    Bfs *bfs = new Bfs(this->map, trip->getStartPoint(), trip->getEndPoint());

    // Calculate shortest route
    bfs->get_route();

    // Set trip route
    trip->setTripRoute(bfs->getShortestPath());

    // Push new trip to trip queue
    this->taxiCenter->addTrip(trip);

    delete bfs;
}

TaxiCenter *MainFlow::getTaxiCenter() const {
    return taxiCenter;
}

Grid *MainFlow::getMap() const {
    return map;
}

Clock *MainFlow::getClock() {
    return this->clock;
}

void MainFlow::startDriving() {

    unsigned int i = 0;
    std::vector<Taxi *> taxiVec = this->taxiCenter->getTaxis();
    std::queue<Trip *> &tripQueue = this->taxiCenter->getTrips();

    for (i = 0; i < taxiVec.size(); i++) {

        Trip *currTrip = tripQueue.front();
        Taxi *currTaxi = taxiVec.at(i);

        // If trip queue is empty and there are not more trips
        if (tripQueue.empty()) {
            break;
        }

            // If current taxi already has a trip, or the taxi is not at the
            // trip start point.
        else if (currTaxi->getTrip() != 0 ||
                 currTaxi->getCurrentPosition() != currTrip->getStartPoint()) {
            continue;
        } else {

            // Calculate new coefficient according to vehicle type
            currTrip->setTariff(currTrip->getTariff()
                                * currTaxi->getVehicle()->getCoefficient());

            // Assign trip to taxi
            currTaxi->setTrip(currTrip);

            // Set the new taxi's current location to end point
            currTaxi->setCurrentPosition(currTrip->getEndPoint());
            currTaxi->notifyObservers();

            delete currTrip;
            tripQueue.pop();

            //Make the driver available to take another trip.
            currTaxi->setTrip(0);

        }
    }
}

void MainFlow::exitSystem() {

    delete this->taxiCenter;
    delete this->map;
    delete this->clock;

    //exit the system
    exit(0);
}





