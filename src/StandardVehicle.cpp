
#include "StandardVehicle.h"

StandardVehicle::StandardVehicle(unsigned int vehicleId,
                                 char carManufacturer, char color)
        : Vehicle(vehicleId, carManufacturer, color) {
    this->coefficient = 1;
    this->speed = 1;
}

StandardVehicle::StandardVehicle() {

}

BOOST_CLASS_EXPORT(StandardVehicle);
