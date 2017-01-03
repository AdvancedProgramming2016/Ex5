
#include "MainFlow.h"
#include <cstdlib>

void MainFlow::createMap(Grid *grid) {
    this->map   = grid;
}

void MainFlow::createTaxiCenter(Point *location) {

    this->taxiCenter = new TaxiCenter(location);
}

void MainFlow::createDriver(Driver *driver) {

    taxiCenter->addDriver(driver);
}

void MainFlow::createVehicle(Vehicle *vehicle) {

    taxiCenter->addVehicle(vehicle);
}

void MainFlow::createTrip(Trip *trip) {

    Bfs bfs(this->map, trip->getStartPoint(), trip->getEndPoint());

    // Calculate shortest route
    bfs.get_route();
    cleanGrid();

    // Set trip route
    trip->setTripRoute(bfs.getShortestPath());

    // Push new trip to trip queue
    this->taxiCenter->addTrip(trip);

}

TaxiCenter *MainFlow::getTaxiCenter() const {
    return taxiCenter;
}

Grid *MainFlow::getMap() const {
    return map;
}

void MainFlow::exitSystem() {

    delete this->taxiCenter;
    delete this->map;

    //exit the system
    exit(0);
}

void MainFlow::cleanGrid() {

    Vertex *v;

    for (int i = 0; i < this->map->get_edges().size(); ++i) {

        v = this->map->get_vertex(map->get_edges()[i].getM_point());

        if(!this->getMap()->isObstacle(v->getM_point())){

            v->set_unvisited();
        }

        v->setFather(0);
    }
}





