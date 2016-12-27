
#include "VehicleFactory.h"

Vehicle *VehicleFactory::makeVehicle(unsigned int id, unsigned int vehicleType,
                                     char manufacturer,
                                     char color) {


    if (vehicleType == 1) {

        return new StandardVehicle(id, manufacturer, color);
    } else if (vehicleType == 2) {

        return new LuxuryVehicle(id, manufacturer, color);
    }

    return 0;
}
