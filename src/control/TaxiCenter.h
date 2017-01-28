#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

#include <vector>
#include "../taxi/Driver.h"
#include "../taxi/Vehicle.h"
#include "../taxi/Taxi.h"
#include "../observers/ISubject.h"
#include "../parsers/StringParser.h"
#include "../sockets/Socket.h"
#include "../serializers/Serializer.h"
#include "Clock.h"
#include "../threads/TripThread.h"

class Driver;

class Taxi;

class Point;

class Trip;

class Passenger;

class TripThread;

/**
 * The class represents a taxi center, which manages all the taxis.
 * It receives passengers calls, and assigns drivers to vehicles.
 * Searches for the best route a taxi can take to complete a trip.
 */
class TaxiCenter : public IObserver {

private:
    std::vector<Driver *> drivers;
    std::vector<Vehicle *> vehicles;
    std::vector<Taxi *> taxis;
    std::vector<Trip *> trips;
    Point *taxiCenterLocation;
    std::vector<TripThread *> tripThreads;
    Clock *clock;

private:

    /*
     * Adds a taxi to the taxis list.
     */
    void addTaxi(Taxi *taxi);

    /*
     * Find the TripThread with the given Trip instance.
     */
    TripThread *findTripThread(Trip *trip);

    /*
     * Wait for the TripThread's task to be finished.
     */
    void waitForCalcToFinish(TripThread *tripThread);

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
     * Assigns the free taxis with trips.
     */
    void assignTrip(Driver *driver, Socket &socket, Serializer serializer,
                    int descriptor);

    /*
     * Moves all the taxis with trips to their next point on the map.
     */
    void moveOneStep(Driver *driver, Socket &socket, Serializer serializer,
                     int descriptor);

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

    vector<TripThread *> &getTripThreads();

    /*
     * Returns the clock.
     */
    Clock *getClock() const;
};


#endif //EX2_TAXICENTER_H