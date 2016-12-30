
#include "Trip.h"

Trip::Trip(unsigned int rideId, Point &startPoint,
           Point &endPoint, unsigned int numOfPassengers,
           double tariff, unsigned tripStartTime): endPoint(endPoint), startPoint(startPoint){
    this->rideId = rideId;
    this->numOfPassengers = numOfPassengers;
    this->tariff = tariff;
    this->totalMetersPassed = 0;
    this->tripStartTime = tripStartTime;

}

std::vector<Point> Trip::getTripRoute() {
    return this->tripRoute;
}

void Trip::setTripRoute(std::vector<Point> &tripRoute) {
    this->tripRoute = tripRoute;
}

unsigned int Trip::getRideId() const {
    return rideId;
}

unsigned int Trip::getTotalMetersPassed() const {
    return totalMetersPassed;
}

unsigned int Trip::getNumOfPassengers() const {
    return numOfPassengers;
}

void Trip::setTariff(double newTariff) {
    this->tariff = newTariff;
}

double Trip::getTariff() const {
    return tariff;
}

const Point &Trip::getStartPoint() const {
    return startPoint;
}

const Point &Trip::getEndPoint() const {
    return endPoint;
}



