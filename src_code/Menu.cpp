
#include "Menu.h"
#include <cstdlib>
#include "src/sockets/Udp.h"
#include "Driver.h"

Menu::Menu() {

    // Open server side socket on port 5555
    this->udp(1, 5555);
    this->udp.initialize();

}

Udp Menu::getUdp() {

    return this->udp;

}

MainFlow *Menu::getMainFlow() {

    return this->mainFlow;

}

int Menu::initializeGame() {

    Point location(0,0);

    //Create Grid with obstacles.
    this->getMainFlow()->createMap(
            this->stringParser.parseGridInput());
    this->getMainFlow()->createTaxiCenter(&location);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1:
                int i = 0;
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                // Receive driver objects from client
                for (i = 0; i < numOfDrivers; i++) {

                    // Wait for client request
                    char buffer[1024];
                    this->getUdp().reciveData(buffer, sizeof(buffer));

                    // Create a driver from
                    this->getMainFlow()->createDriver
                            (this->stringParser.parseDriverInput());

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

            // Request for driver location
            case 4:
                this->getMainFlow()->getTaxiCenter()->requestDriverLocation(
                        this->stringParser.parseDriverLocation());
                break;

            // Start Driving
            case 6:
                this->getMainFlow()->startDriving();
                break;

            //Exit system
            case 7:
                this->getMainFlow()->exitSystem();

            // Advance one step
            case 9:
                this->getMainFlow()->getTaxiCenter()->moveOneStep();

            // Invalid input
            default:
                exit(1);

        }

    }

}
#pragma clang diagnostic pop
