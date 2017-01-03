
#ifndef EX2_TRIP_H
#define EX2_TRIP_H


#include "Taxi.h"
#include "Bfs.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>


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
    unsigned tripStartTime;
    double   tariff;
    Point    startPoint;
    Point    endPoint;
    std::vector<Point> tripRoute; // Vector with all the points of the trip

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &archive, const unsigned int version) {
        archive & rideId;
        archive & totalMetersPassed;
        archive & numOfPassengers;
        archive & tripStartTime;
        archive & tariff;
        archive & startPoint;
        archive & endPoint;
        archive & tripRoute;
    }

public:

    /*
     * Constructor.
     */
    Trip(unsigned int rideId, Point &startPoint,
         Point &endPoint, unsigned int numOfPassengers,
         double tariff, unsigned int tripStartTime);

    /*
     * Constructor.
     */
    Trip();
    /*
     * Returns the route of the trip
     */
    std::vector<Point>& getTripRoute();

    /*
     * Set the trip route
     */
    void setTripRoute(std::vector<Point> &tripRoute);

    /*
     * Returns the starting time of the trip.
     */
    unsigned int getTripStartTime();

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
