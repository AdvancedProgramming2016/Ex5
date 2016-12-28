

#include "LuxuryVehicle.h"

LuxuryVehicle::LuxuryVehicle(unsigned int vehicleId,
                             char carManufacturer, char color)
        : Vehicle(vehicleId, carManufacturer, color) {
    this->coefficient = 2;
    this->speed = 2;
}
