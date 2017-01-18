
#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <boost/serialization/access.hpp>
#include "Taxi.h"

/**
 * The class represents a driver of a taxi vehicle.
 *
 */
class Driver {

private:

    unsigned driverId;
    unsigned age;
    unsigned yearsOfExperience;
    unsigned vehicleId;
    unsigned avgSatisfaction;
    unsigned counterOfCustomers;
    char     maritalStatus;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &archive, const unsigned int version) {
        archive & driverId;
        archive & age;
        archive & yearsOfExperience;
        archive & vehicleId;
        archive & avgSatisfaction;
        archive & counterOfCustomers;
        archive & maritalStatus;
    }

public:

    /*
    * Constructor.
    */
    Driver(unsigned int driverId, unsigned int age,
           char maritalStatus, unsigned int yearsOfExperience,
           unsigned int vehicleId);

    /*
     * Constructor
     */
    Driver();

    /*
    * Returns the driver id.
    */
    unsigned int getDriverId() const;


    /*
    * Returns the driver's years of experience.
    */
    unsigned int getYearsOfExperience() const;

    /*
    * Returns the counter of customers.
    */
    unsigned int getCounterOfCustomers() const;

    /*
    * Increases the driver's years of experience by one.
    */
    void increaseExperience();

    /*
    * Sets the counter of customers to the received number.
    */
    void setCounterOfCustomers(unsigned int counterOfCustomers);

    /*
     * Returns the average driver satisfaction.
     */
    unsigned int getAvgSatisfaction() const;

    /*
     * Sets the average satisfaction.
     */
    void setAvgSatisfaction(unsigned int newAvg);

    /*
     * Returns the driver's vehicle's id number.
     */
    unsigned int getVehicleId() const;

};


#endif //EX2_DRIVER_H
