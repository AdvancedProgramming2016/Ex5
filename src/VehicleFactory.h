
#ifndef EX3_VEHICLEFACTORY_H
#define EX3_VEHICLEFACTORY_H

#include "StandardVehicle.h"
#include "LuxuryVehicle.h"

/**
 * The class implements the factory design pattern which prodeuces vehicles,
 * depending on user input.
 */
class VehicleFactory {

public:
    /*
     * Creates the required vehicle according to the received type.
     */
    Vehicle* makeVehicle(unsigned int id, unsigned int vehicleType,
                        char manufacturer, char color);
};


#endif //EX3_VEHICLEFACTORY_H
