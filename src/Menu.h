

#ifndef EX2_CHECK_MENU_H
#define EX2_CHECK_MENU_H


#include "Driver.h"
#include "StringParser.h"
#include "../sockets/Udp.h"
#include "MainFlow.h"
#include "TaxiCenter.h"
#include "Serializer.h"

class Menu {

private:
    StringParser stringParser;
    MainFlow     *mainFlow;

public:

    /*
     * Ctor
     */
    Menu(Socket *socket);

    int *currentOperation;

    /*
     * Destructor
     */
    virtual ~Menu();

    void wakeUpThreads(int operationNumber);

    /*
     * Returns serializer
     */
    Serializer getSerializer();

    /*
     * Gets the socket object
     */
    //Socket *getSocket();

    /*
     * Initialize the grid with user input.
     */
    int initializeGame();

    /*
     * Run the option menu for the user.
     */
    int runMenu();

    /*
     * Return the mainFlow.
     */
    MainFlow *getMainFlow();

    Vehicle* getDriverVehicle(unsigned int vehicleId);

};


#endif //EX2_CHECK_MENU_H
