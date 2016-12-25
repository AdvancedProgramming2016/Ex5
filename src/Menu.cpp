
#include "Menu.h"
#include <cstdlib>
#include "Driver.h"

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

int Menu::runMenu() {

    int userOption = 0;

    while (userOption < 7) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1:
                this->getMainFlow()->createDriver(
                        this->stringParser.parseDriverInput());
                break;

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

                // Invalid input
            default:
                exit(1);

        }

    }

}
