

#include "LuxuryVehicle.h"

LuxuryVehicle::LuxuryVehicle(unsigned int vehicleId,
                             char carManufacturer, char color)
        : Vehicle(vehicleId, carManufacturer, color) {
    coefficient = 2;
}
