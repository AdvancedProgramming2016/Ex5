
#ifndef EX2_MAINFLOW_H
#define EX2_MAINFLOW_H

#define THREAD_POOL_SIZE 5

#include "TaxiCenter.h"
#include "../graphs/Grid.h"
#include "../taxi/VehicleFactory.h"
#include "../parsers/StringParser.h"
#include "Clock.h"
#include "../threads/ClientThread.h"
#include "../threads/ThreadPool.h"

class ClientThread;

class BaseParser;

class Trip;

class TaxiCenter;

class clock;

class MainFlow {

    friend class TripThread;

private:

    TaxiCenter *taxiCenter;
    Grid       *map;
    std::vector<ClientThread *> clientThreadVector;
    Socket       *socket;
    std::queue<int> *threadIdQueue;
    Serializer   serializer;
    int *operationNumber;
    unsigned int vacantPort;
    pthread_mutex_t receiveDriverMutex;
    pthread_mutex_t sendCommandMutex;
    pthread_mutex_t threadMutex;
    pthread_mutex_t bfsMutex;
    int order;
    int startOrder;
    unsigned int numOfDrivers;
    ThreadPool *threadPool;
    std::vector<Task*> tasks;
public:
    ThreadPool *getThreadPool() const;

public:

    /*
     * Ctor
     */
    MainFlow(Socket *socket, int operationNumber);

    /*
     * Dtor
     */
    ~MainFlow();

    void addClientId(int threadId);

    /*
     * Creates a map with obstacles.
     */
    void createMap(Grid *grid);

    /*
     * Gets the next operation number
     */
    int *getOperationNumber();

    /*
     * Adds the client thread to vector
     */
    void addClientThread(ClientThread *clientThread);

    /*
     * Makes the main thread wait for remaining threads to finish executing
     * command
     */
    void clockSleep();

    /*
     * Returns the client thread vector.
     */
    std::vector<ClientThread *> getClientThreadVector();

    // Gets a vacant port from the server
    unsigned int getVacantPort();

    // Increase the vacant port by one
    void increaseVacantPort();

    /*
     * Performs task number 9 - assign trip and move one step
     */
    void performTask9(Driver *driver, int descriptor);

    /*
     * Return serializer object
     */
    Serializer getSerializer();

    /*
     * Select drivers option from menu
     */
    void selectDrivers(int numOfDrivers);

    /*
     * Send vehicle to socket.
     */
    void sendToSocketVehicle(unsigned int vehicleId, int descriptor);

    /*
     * Sends the client the new port the servers is listening to.
     */
    void sendClientNewPort(unsigned int newPort);

    /*
     * Creates a taxi center.
     */
    void createTaxiCenter(Point *location);

    /*
     * Return socket
     */
    Socket *getSocket();

    /*
     * Returns the driver by to vehicle id
     */
    Vehicle *getDriverVehicle(unsigned int vehicleId);

    /*
     * Creates a new driver.
     */
    void createDriver(Driver *driver);

    /*
     * Creates a new vehicle.
     */
    void createVehicle(Vehicle *vehicle);

    /*
     * Create a new trip.
     */
    void createTrip(Trip *trip);

    /*
     * Returns the taxi center.
     */
    TaxiCenter *getTaxiCenter() const;

    /*
     * Returns the map.
     */
    Grid *getMap() const;

    /*
     * Exits the taxiCenter system by deleting all the instances and exiting.
     */
    void exitSystem();

    /*
     * Cleans the map for the next iteration.
     */
    void cleanGrid();

    /*
     * Returns receiveDriverMutex
     */
    pthread_mutex_t &getMutexReceiveDriver() ;

    /*
     * Gets send command mutex
     */
    pthread_mutex_t &getSendCommandMutex();

    /*
     * Returns the thread mutex.
     */
    pthread_mutex_t &getThreadMutex();

    /*
     * Returns the starting order/
     */
    int getStartOrder() const;

    /*
     * Sets the starting order.
     */
    void setStartOrder(int startOrder);

    /*
     * Returns the order.
     */
    int getOrder() const;

    /*
     * Sets the order.
     */
    void setOrder(int order);

};


#endif //EX2_MAINFLOW_H
