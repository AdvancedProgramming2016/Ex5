
#include "TaxiCenter.h"
#include "../sockets/Socket.h"

TaxiCenter::TaxiCenter(Point *taxiCenterLocation) :
        taxiCenterLocation(taxiCenterLocation) {}

TaxiCenter::~TaxiCenter() {

    Trip *tempTrip = 0;

    //delete all the trips
    for (int tripsIndex = 0; tripsIndex < trips.size(); ++tripsIndex) {
        delete trips[tripsIndex];
    }

    //delete all the taxis.
    for (int taxisIndex = 0; taxisIndex < taxis.size(); ++taxisIndex) {
        delete taxis[taxisIndex];
    }

    for (int driversIndex = 0; driversIndex < drivers.size(); ++driversIndex) {
        delete drivers[driversIndex];
    }

    //delete all the vehicles.
    for (int vehiclesIndex = 0;
         vehiclesIndex < vehicles.size(); ++vehiclesIndex) {
        delete vehicles[vehiclesIndex];
    }

}

void TaxiCenter::assignTrip(Socket &socket) {

    unsigned int i = 0;
    std::vector<Taxi *> taxiVec = this->getTaxis();
    std::queue<Trip *> &tripQueue = this->getTrips();

    for (i = 0; i < taxiVec.size(); i++) {

        // If trip queue is empty and there are not more trips
        if (tripQueue.empty()) {
            break;
        }

        Trip *currTrip = tripQueue.front();
        Taxi *currTaxi = taxiVec.at(i);

        // If current taxi already has a trip, or the taxi is not at the
        // trip start point.
        if (currTaxi->getTrip() != 0) {
            continue;
        } else {

            // Calculate new coefficient according to vehicle type
            currTrip->setTariff(currTrip->getTariff()
                                * currTaxi->getVehicle()->getCoefficient());

            // Assign trip to taxi
            currTaxi->setTrip(currTrip);

            // Set the new taxi's current location to end point
            currTaxi->notifyObservers();

            delete currTrip;
            tripQueue.pop();

            this->getSocket
        }
    }
}

void TaxiCenter::moveOneStep() {

    std::vector<Taxi *> taxiVec = this->getTaxis();
    int i = 0;

    // Update location of all taxis
    for (i = 0; i < taxiVec.size(); i++) {

        // Gets current taxi
        Taxi *currTaxi = taxiVec[i];
        Point *currPoint;

        int j = 0;
        for (j = 0; j < currTaxi->getVehicle()->getSpeed(); j++) {

            // If the driver already reached his destination
            if (currTaxi->getTrip()->getTripRoute().size() == 0) {
                break;
            }

            // Get next point to advance to
             *currPoint = currTaxi->getTrip()->getTripRoute()[0];

            // Remove point from trip route
            currTaxi->getTrip()->getTripRoute().erase
                    (currTaxi->getTrip()->getTripRoute().begin());

        }

        // Set new position
        currTaxi->setCurrentPosition(*currPoint);
    }

}

std::vector<Driver *> &TaxiCenter::getDrivers() {
    return drivers;
}

std::vector<Vehicle *> &TaxiCenter::getVehicles() {
    return vehicles;
}

std::vector<Trip *> &TaxiCenter::getTrips() {
    return trips;
}

std::vector<Taxi *> &TaxiCenter::getTaxis() {
    return taxis;
}

Point *TaxiCenter::getTaxiCenterLocation() {
    return taxiCenterLocation;
}

void TaxiCenter::addDriver(Driver *driver) {

    drivers.push_back(driver);
}

void TaxiCenter::addVehicle(Vehicle *vehicle) {

    vehicles.push_back(vehicle);
}

void TaxiCenter::createTaxi(Driver *driver) {

    for (int i = 0; i < vehicles.size(); ++i) {

        if (driver->getVehicleId() == vehicles[i]->getVehicleId()) {

            Taxi *taxi = new Taxi(driver, vehicles[i], Point(0, 0));
            addTaxi(taxi);

            taxi->registerObserver(this);
        }
    }
}

void TaxiCenter::addTaxi(Taxi *taxi) {

    taxis.push_back(taxi);
}

void TaxiCenter::addTrip(Trip *trip) {
    this->trips.push_back(trip);
}

void TaxiCenter::requestDriverLocation(int driverId) {

    for (int i = 0; i < taxis.size(); ++i) {

        if (taxis[i]->getDriver()->getDriverId() == driverId) {

            std::cout << taxis[i]->getCurrentPosition() << std::endl;
        }
    }
}

void TaxiCenter::update(Taxi *taxi) {

    for (int i = 0; i < taxis.size(); ++i) {

        if (taxis[i]->getDriver()->getDriverId() ==
            taxi->getDriver()->getDriverId())
            taxis[i] = taxi;
    }
}
