
#include "Driver.h"

Driver::Driver(unsigned int driverId, unsigned int age,
               char maritalStatus, unsigned int yearsOfExperience,
               unsigned int vehicleId)
        : driverId(driverId), age(age),
          yearsOfExperience(yearsOfExperience),
          avgSatisfaction(0),
          counterOfCustomers(0),
          maritalStatus(maritalStatus),
          vehicleId(vehicleId) {}

unsigned int Driver::getDriverId() const {
    return driverId;
}

unsigned int Driver::getYearsOfExperience() const {
    return yearsOfExperience;
}

unsigned int Driver::getCounterOfCustomers() const {
    return counterOfCustomers;
}

void Driver::increaseExperience() {

    yearsOfExperience++;
}

void Driver::setCounterOfCustomers(unsigned int counterOfCustomers) {
    Driver::counterOfCustomers = counterOfCustomers;
}

unsigned int Driver::getAvgSatisfaction() const {
    return avgSatisfaction;
}

unsigned int Driver::getVehicleId() const {
    return vehicleId;
}

void Driver::setAvgSatisfaction(unsigned int newAvg) {
    avgSatisfaction = newAvg;
}
