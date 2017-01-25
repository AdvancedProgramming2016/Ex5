
#include "Vehicle.h"

Vehicle::Vehicle(){

}

Vehicle::Vehicle(unsigned int vehicleId, char carManufacturer,
                 char color) : vehicleId(vehicleId),
                                carManufacturer(carManufacturer),
                                color(color), kmPassed(0) {}


unsigned int Vehicle::getVehicleId() const {
    return vehicleId;
}

unsigned int Vehicle::getKmPassed() const {
    return kmPassed;
}

unsigned int Vehicle::getSpeed() const {
    return this->speed;
}

char Vehicle::getCarManufacturer() const {
    return carManufacturer;
}

char Vehicle::getColor() const {
    return color;
}

unsigned int Vehicle::getMaxCapacity() const {
    return maxCapacity;
}

double Vehicle::getCoefficient() const {
    return coefficient;
}

void Vehicle::increaseKmPassed() {
    kmPassed++;
}



