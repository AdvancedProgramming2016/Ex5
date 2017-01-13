#include "Menu.h"
#include <pthread.h>

Menu::Menu(Socket *socket) {

    this->mainFlow = new MainFlow(socket, 0);

}

Menu::~Menu() {

    delete this->mainFlow;

}

MainFlow *Menu::getMainFlow() {

    return this->mainFlow;

}

int Menu::initializeGame() {

    Point location(0, 0);

    //Create Grid with obstacles.
    this->getMainFlow()->createMap(
            this->stringParser.parseGridInput());
    this->getMainFlow()->createTaxiCenter(&location);
}

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1: {
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                this->getMainFlow()->selectDrivers(numOfDrivers);
                break;
            }
                // Create trip
            case 2:
                this->getMainFlow()->createTrip(
                        this->stringParser.parseTripInput());
                break;

                // Create vehicle
            case 3:
                this->getMainFlow()->createVehicle(
                        this->stringParser.parseVehicleInput());
                break;

                // Request driver location
            case 4:

                this->getMainFlow()->getTaxiCenter()->requestDriverLocation(
                        this->stringParser.parseDriverLocation());
                break;

                /*
                // Start Driving
            case 6:
                this->getMainFlow()->startDriving();
                break;
                */
                //Exit system
            case 7:

                // Send each driver exit command
                this->wakeUpThreads(7);  //TODO in order to exit we need to join the threads first
                this->getMainFlow()->exitSystem();


                // Advance one step
            case 9:

                this->wakeUpThreads(9);
                break;
        }
    }
}

void Menu::wakeUpThreads(int operationNumber) {
    std::vector<ClientThread *> clientThreadVec = this->getMainFlow()->getClientThreadVector();
    int numberOfThreads = clientThreadVec.size();
    for (int i = 0; i < numberOfThreads; i++) {
        clientThreadVec.at(i)->setThreadCommand(operationNumber);
        //pthread_join(clientThreadVec.at(i)->getThread(), NULL);
    }

}



