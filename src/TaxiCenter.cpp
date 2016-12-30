
#include "TaxiCenter.h"

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
