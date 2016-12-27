
#ifndef EX2_TRIP_H
#define EX2_TRIP_H


#include "Taxi.h"
#include "Bfs.h"

/**
 * The class represents a trip, which a taxi takes along the map, from one point to another.
 */
class Point;
class Bfs;

class Trip {

private:

    unsigned rideId;
    unsigned totalMetersPassed;
    unsigned numOfPassengers;
    double   tariff;
    Point    startPoint;
    Point    endPoint;
    std::vector<Point> tripRoute; // Vector with all the points of the trip

public:


    /*
     * Constructor.
     */
    Trip(unsigned int rideId, Point &startPoint,
         Point &endPoint, unsigned int numOfPassengers,
         double tariff);

    /*
     * Returns the route of the trip
     */
    std::vector<Point> getTripRoute();

    /*
     * Set the trip route
     */
    void setTripRoute(std::vector<Point> &tripRoute);

    /*
     * Returns the ride id.
     */
    unsigned int getRideId() const;

    /*
     * Returns the total number of meters passed from the beginning of the trip.
     */
    unsigned int getTotalMetersPassed() const;

    /*
     * Returns the number of passengers taking the trip.
     */
    unsigned int getNumOfPassengers() const;

    /*
     * Returns the trip coefficient
     */
    double getTariff() const;

    /*
     * Set the new trip coefficient
     */
    void setTariff(double newTariff);

    /*
     * Returns the starting point of the trip.
     */
    const Point &getStartPoint() const;

    /*
     * Returns the ending point of the trip.
     */
    const Point &getEndPoint() const;
};


#endif //EX2_TRIP_H
