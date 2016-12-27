
#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H


#include "Point.h"

/**
 * The class represents a passenger, which takes a ride in a taxi.
 */
class Passenger {

private:
    Point sourcePoint;
    Point destinationPoint;

public:

    /*
     * Constructor
     */
    Passenger(const Point &sourcePoint, const Point &destinationPoint);

    /*
     * Returns the passenger's source point.
     */
    const Point &getSourcePoint() const;

    /*
     * Returns the passenger's destination point.
     */
    const Point &getDestinationPoint() const;

    /*
     * Returns a random satisfaction number from 1 to 5, for the taxi.
     */
    unsigned generateSatisfaction();
};


#endif //EX2_PASSENGER_H
