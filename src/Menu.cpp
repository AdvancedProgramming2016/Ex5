#include "Menu.h"

Menu::Menu(Socket *socket) {

    // Open server side socket on port 5555
    this->socket = new Udp(1, 5555, "127.0.0.1");
    this->socket->initialize();

}

Socket *Menu::getSocket() {

    return this->socket;

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

void Menu::sendToSocket(Vehicle) {

    // TODO: Didn't understand what kind of vehicle we need to send back
    Vehicle     *vehicle = new StandardVehicle(0, 'H', 'G');
    char        buffer2[1024];
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    this->getSocket()->sendData(serialVehicle);

}

Driver *Menu::listenToSocket() {

    char buffer[1024];
    this->socket->reciveData(buffer, 1024);

    Driver *driver;
    this->serializer.deserialize(buffer, sizeof(buffer), driver);

    return driver;

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1: {
                int i            = 0;
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                Driver *driver;

                // Receive driver objects from client
                for (i = 0; i < numOfDrivers; i++) {

                    driver = this->listenToSocket();

                }
            }

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

                /*
                // Start Driving
            case 6:
                this->getMainFlow()->startDriving();
                break;
                */
                //Exit system
            case 7:
                this->getMainFlow()->exitSystem();

                // Advance one step
            case 9:

                // Check that all the trips that need to start are attached
                // to a driver
                this->getMainFlow()->startDriving();

                // Move all the taxis one step
                this->getMainFlow()->getTaxiCenter()->moveOneStep();

                // Invalid input
            default:
                exit(1);

        }

    }

}

#pragma clang diagnostic pop
