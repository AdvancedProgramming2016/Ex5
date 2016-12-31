
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

void MainFlow::exitSystem() {

    delete this->taxiCenter;
    delete this->map;
    delete this->clock;

    //exit the system
    exit(0);
}





