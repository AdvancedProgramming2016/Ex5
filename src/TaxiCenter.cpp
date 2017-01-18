//#include <boost/log/trivial.hpp>
#include "TaxiCenter.h"
#include "../sockets/Socket.h"
#include "Serializer.h"

TaxiCenter::TaxiCenter(Point *taxiCenterLocation) :
        taxiCenterLocation(taxiCenterLocation) {

    clock = new Clock;
}

TaxiCenter::~TaxiCenter() {

    // Delete all the trips.
    for (int tripsIndex = 0; tripsIndex < trips.size(); ++tripsIndex) {
        delete trips[tripsIndex];
    }

    // Delete all the taxis.
    for (int taxisIndex = 0; taxisIndex < taxis.size(); ++taxisIndex) {
        delete taxis[taxisIndex];
    }

    // Delete all the drivers.
    for (int driversIndex = 0; driversIndex < drivers.size(); ++driversIndex) {
        delete drivers[driversIndex];
    }

    // Delete all the vehicles.
    for (int vehiclesIndex = 0;
         vehiclesIndex < vehicles.size(); ++vehiclesIndex) {
        delete vehicles[vehiclesIndex];
    }

    // Delete all the trip threads.
    for (int tripThread = 0;
         tripThread < this->tripThreads.size(); tripThread++) {
        delete this->tripThreads[tripThread];
    }

    delete this->clock;

}

void
TaxiCenter::assignTrip(Driver *driver, Socket &socket, Serializer serializer,
                       int descriptor) {

    unsigned int i = 0;
    std::vector<Trip *> &tripVec = this->getTrips();
    std::vector<Taxi *> &taxiVec = this->getTaxis();
    Taxi *currTaxi = 0;

    int j = 0;
    for (j = 0; j < taxiVec.size(); j++) {

        if (taxiVec[j]->getDriver()->getDriverId() == driver->getDriverId()) {
            currTaxi = taxiVec[j];
            break;
        }
    }

    if (currTaxi != 0 && currTaxi->getTrip() == 0) {

        for (i = 0; i < this->getTrips().size(); i++) {

            // If trip vector is empty and there are not more trips
            if (tripVec.empty()) {
                return;
            }

            // Get current trip
            Trip *currTrip = tripVec.at(i);

            // Check that start time is valid
            if (currTrip->getTripStartTime() == this->clock->getTime() &&
                currTaxi->getCurrentPosition() == currTrip->getStartPoint()) {

                pthread_t threadToWait = findTripThread(currTrip)->getThread();
                //BOOST_LOG_TRIVIAL(info) << "waiting for trip thread:"
                //                        << threadToWait;
                pthread_join(threadToWait, NULL);
                //Update the current taxi with a trip
                currTaxi->setTrip(currTrip);

                // Send trip to client
                std::string serialTrip;
                serialTrip = serializer.serialize(currTrip);
                socket.sendData(serialTrip, descriptor);
                //BOOST_LOG_TRIVIAL(debug)
                //    << "TaxiCenter sends a trip to client:" << descriptor;

                //Remove the trip from the trips vector;
                tripVec.erase(tripVec.begin() + i);
            }
        }
    }
}

void
TaxiCenter::moveOneStep(Driver *driver, Socket &socket, Serializer serializer,
                        int descriptor) {

    std::vector<Taxi *> &taxiVec = this->getTaxis();
    int i = 0;
    Taxi *currTaxi;

    // Check which driver has trip
    for (i = 0; i < taxiVec.size(); i++) {

        // Gets current taxi
        if (taxiVec[i]->getDriver()->getDriverId() == driver->getDriverId()) {

            currTaxi = taxiVec.at(i);
            break;
        }

    }

    // If taxi has trip and hasn't ended yet, send him message
    // to move one step
    if (currTaxi != 0 && currTaxi->getTrip() != 0) {

        // Tell driver to advance one step
        std::string go = "go";
        socket.sendData(go, descriptor);
        //BOOST_LOG_TRIVIAL(debug)
        //    << "TaxiCenter sends move command to client:" << descriptor;

        // Wait for drivers answer
        char buffer[1024];
        Point *currPoint = 0;
        socket.receiveData(buffer, 1024, descriptor);
        serializer.deserialize(buffer, sizeof(buffer), currPoint);

        currTaxi->setCurrentPosition(*currPoint);

        // If driver didn't move one step and his trip ended
        if (*currPoint == currTaxi->getTrip()->getEndPoint()) {
            delete currTaxi->getTrip();
            currTaxi->setTrip(0);

            // Set trip to finish
            currTaxi->setTrip(0);
        }

        delete currPoint;
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
    this->createTaxi(driver);
}

void TaxiCenter::addVehicle(Vehicle *vehicle) {

    vehicles.push_back(vehicle);
}

TripThread *TaxiCenter::findTripThread(Trip *trip) {

    for (int i = 0; i < tripThreads.size(); ++i) {

        if (tripThreads[i]->getTrip()->getRideId() == trip->getRideId()) {

            return tripThreads[i];
        }
    }
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

vector<TripThread *> &TaxiCenter::getTripThreads() {
    return tripThreads;
}

Clock *TaxiCenter::getClock() const {
    return clock;
}

