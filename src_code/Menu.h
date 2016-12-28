

#ifndef EX2_CHECK_MENU_H
#define EX2_CHECK_MENU_H


#include "Driver.h"
#include "StringParser.h"
#include "src/sockets/Udp.h"
#include "MainFlow.h"
#include "TaxiCenter.h"

class Menu {

private:
    StringParser stringParser;
    MainFlow     *mainFlow;
    Socket socket;

public:

    /*
     * Ctor
     */
    Menu(Socket &socket);

    /*
     * Listen to socket and receive driver.
     */
    Driver listenToSocket();

    /*
     * Send vehicle to socket.
     */
    void sendToSocket(Vehicle);

    /*
     * Gets the udp object
     */
    Socket getSocket();

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

};


#endif //EX2_CHECK_MENU_H
