
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

/**
 * The class represents an abstract vehicle.
 */
class Vehicle {

private:
    unsigned vehicleId;
    unsigned kmPassed;
    char     carManufacturer;
    char     color;

protected:
    unsigned maxCapacity;
    double   coefficient;
    unsigned int speed;

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &archive, const unsigned int version) {
        archive & vehicleId;
        archive & kmPassed;
        archive & carManufacturer;
        archive & color;
        archive & maxCapacity;
        archive & coefficient;
        archive & speed;
    }

public:

    Vehicle(); //TODO delete if not necessary for serialization
    /*
     * Constructor
     */
    Vehicle(unsigned int vehicleId, char carManufacturer, char color);

    /*
     * Returns the vehicle id.
     */
    unsigned int getVehicleId() const;

    /*
     * Returns the speed of the car.
     */
    unsigned int getSpeed() const;

    /*
     * Returns the number of kilometers a vehicle has passed
     */
    unsigned int getKmPassed() const;

    /*
     * Returns the type(enum) of the car manufacturer
     */
    char getCarManufacturer() const;

    /*
     * Returns the color(enum) of the vehicle
     */
    char getColor() const;

    /*
     * Returns the number of the maximum passenger capacity a vehicle can hold.
     */
    unsigned int getMaxCapacity() const;

    /*
     * Returns the vehicle coefficient
     */
    double getCoefficient() const;

    /*
     * Increases the number of kilometers passed by the vehicle by one.
     */
    void increaseKmPassed();

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Vehicle);

#endif //EX2_VEHICLE_H
