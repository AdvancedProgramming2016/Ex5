
#ifndef EX2_MAINFLOW_H
#define EX2_MAINFLOW_H


#include "TaxiCenter.h"
#include "Grid.h"
#include "VehicleFactory.h"
#include "StringParser.h"
#include "Clock.h"
#include "ClientThread.h"

class ClientThread;

class BaseParser;

class Trip;

class TaxiCenter;

class clock;

class MainFlow {

private:

    TaxiCenter *taxiCenter;
    Grid       *map;
    std::vector<pthread_t> threads;
    std::vector<Socket *> socketVector;
    std::vector<ClientThread *> clientThreadVector;
    Socket       *socket;
    Serializer   serializer;
    int *operationNumber;
    unsigned int vacantPort;

public:

    /*
     * Ctor
     */
    MainFlow(Socket *socket, int operationNumber);

    /*
     * Dtor
     */
    ~MainFlow();

    /*
     * Creates a map with obstacles.
     */
    void createMap(Grid *grid);

    // Gets the next operation number
    int *getOperationNumber();

    std::vector<Socket *> getSocketVector();

    void addClientThread(ClientThread *clientThread);

    std::vector<ClientThread *> getClientThreadVector();

    void insertClientSocket(Socket *socket);

    // Gets a vacant port from the server
    unsigned int getVacantPort();

    // Increase the vacant port by one
    void increaseVacantPort();


    // TODO: change function names
    void performTask9(Socket *currSocket);

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
    void sendToSocketVehicle(unsigned int vehicleId, Socket *socket);

    /*
     * Sends the client the new port the servers is listening to.
     */
    void sendClientNewPort(unsigned int newPort);

    /*
     * Creates a taxi center.
     */
    void createTaxiCenter(Point *location);

    /*
     * Gets the vector of all the threads
     */
    std::vector<pthread_t> getThreadsVector();

    /*
     * Adds thread to the vector of threads
     */
    void addThreadToVector(pthread_t thread);

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

};


#endif //EX2_MAINFLOW_H
