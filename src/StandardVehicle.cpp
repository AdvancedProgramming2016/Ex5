
#include "StandardVehicle.h"

StandardVehicle::StandardVehicle(unsigned int vehicleId,
                                 char carManufacturer, char color)
        : Vehicle(vehicleId, carManufacturer, color) {
    coefficient = 1;
}
