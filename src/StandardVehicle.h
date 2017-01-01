
#ifndef EX2_STANDARDVEHICLE_H
#define EX2_STANDARDVEHICLE_H


#include <boost/serialization/base_object.hpp>
#include "Vehicle.h"

/**
 * The class inherits from the Vehicle class, and represents a standard kind of
 * vehicle.
 */
class StandardVehicle : public Vehicle {

public:

    /*
     * Constructor
     */
    StandardVehicle();

    /*
     * Constructor
     */
    StandardVehicle(unsigned int vehicleId, char carManufacturer, char color);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Vehicle>(*this);
    }

};


#endif //EX2_STANDARDVEHICLE_H
