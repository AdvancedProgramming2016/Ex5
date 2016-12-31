#include "TaxiCenter.h"
#include "../sockets/Socket.h"
#include "Serializer.h"

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

void TaxiCenter::assignTrip(Socket &socket, Serializer serializer,
                            unsigned int currTime) {

    unsigned int i = 0;
    std::vector<Trip *> &tripVec = this->getTrips();
    std::vector<Taxi *> &taxiVec = this->getTaxis();

    int j = 0;
    for (j = 0; j < taxiVec.size(); j++) {

        if (taxiVec.at(j)->getTrip() == 0) {
            for (i = 0; i < this->getTrips().size(); i++) {

                // If trip vector is empty and there are not more trips
                if (tripVec.empty()) {
                    return;
                }

                // Get current trip
                Trip *currTrip = tripVec.at(i);

                // Check that start time is valid
                if (currTrip->getTripStartTime() == currTime) {

                    //Update the current taxi with a trip
                    taxiVec[j]->setTrip(currTrip);

                    // Send trip to client
                    std::string serialTrip;
                    serialTrip = serializer.serialize(currTrip);
                    socket.sendData(serialTrip);

                    tripVec.erase(tripVec.begin() + i);
                }
            }
        }
    }
}

void TaxiCenter::moveOneStep(Socket &socket, Serializer serializer) {

    std::vector<Taxi *> taxiVec = this->getTaxis();
    int i = 0;

    // Check which driver has trip
    for (i = 0; i < taxiVec.size(); i++) {

        // Gets current taxi
        Taxi *currTaxi = taxiVec.at(i);

        // If taxi has trip and hasn't ended yet, send him message to move one step
        if (currTaxi->getTrip() != 0) {

            // Tell driver to advance one step
            std::string go = "go";
            socket.sendData(go);

            // Wait for drivers answer
            char buffer[1024];
            Point *currPoint = 0;
            socket.reciveData(buffer, 1024);
            serializer.deserialize(buffer, sizeof(buffer), currPoint);

            std::cout << *currPoint << std::endl;

            currTaxi->setCurrentPosition(*currPoint);

            // If driver didn't move one step and his trip ended
            if (*currPoint == currTaxi->getTrip()->getEndPoint()) {
                delete currTaxi->getTrip();
                currTaxi->setTrip(0);
                // Driver *driver;
                //serializer.deserialize(buffer, sizeof(buffer), driver);

                // Set trip to finish
                currTaxi->setTrip(0);
            }
        }
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