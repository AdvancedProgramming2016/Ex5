

#ifndef EX2_CHECK_MENU_H
#define EX2_CHECK_MENU_H


#include "../taxi/Driver.h"
#include "../parsers/StringParser.h"
#include "MainFlow.h"
#include "TaxiCenter.h"
#include "../serializers/Serializer.h"

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


};


#endif //EX2_CHECK_MENU_H
