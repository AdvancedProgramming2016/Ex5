#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

#include <vector>
#include "Driver.h"
#include "Vehicle.h"
#include "Taxi.h"
#include "ISubject.h"
#include "StringParser.h"
#include "../sockets/Socket.h"
#include "Serializer.h"
#include "Clock.h"

class Driver;

class Taxi;

class Point;

class Trip;

class Passenger;

/**
 * The class represents a taxi center, which manages all the taxis.
 * It receives passengers calls, and assigns drivers to vehicles.
 * Searches for the best route a taxi can take to complete a trip.
 */
class TaxiCenter : public IObserver {

private:
    std::vector<Driver *>  drivers;
    std::vector<Vehicle *> vehicles;
    std::vector<Taxi *>    taxis;
    std::vector<Trip *>    trips;
    Point                  *taxiCenterLocation;
    Clock                  *clock;

private:

    void addTaxi(Taxi *taxi);

public:

    /*
     * Constructor
     */
    TaxiCenter(Point *taxiCenterLocation);

    /*
     * Destructor
     */
    virtual ~TaxiCenter();

    /*
    * Creates a new taxi by connecting a driver with a vehicle.
    */
    void createTaxi(Driver *driver);

    /*
     * Move the taxis one step
     */
    void assignTrip(Socket &socket, Serializer serializer);

    void moveOneStep(Socket &socket, Serializer serializer);

    /*
     * Add a driver to the drivers the taxi center has.
     */
    void addDriver(Driver *driver);

    /*
     * Add a trip to the taxi center queue.
     */
    void addTrip(Trip *trip);

    /*
     * Adds a vehicle to the vehicles the taxi center has.
     */
    void addVehicle(Vehicle *vehicle);

    /*
     * Returns the taxi center location on the map.
     */
    Point *getTaxiCenterLocation();

    /*
     * Returns the drivers the taxi center has.
     */
    std::vector<Driver *> &getDrivers();

    /*
     * Returns the vehicles the taxi center has.
     */
    std::vector<Vehicle *> &getVehicles();

    /*
     * Returns the taxis the taxi center has.
     */
    std::vector<Taxi *> &getTaxis();

    /*
     * Returns the trips that are waiting for a taxi.
     */
    std::vector<Trip *> &getTrips();

    /*
     * Prints the requested driver's location.
     */
    void requestDriverLocation(int driverId);

    /*
     * Update according to the subject.
     */
    virtual void update(Taxi *taxi);

    Clock *getClock() const;
};


#endif //EX2_TAXICENTER_H