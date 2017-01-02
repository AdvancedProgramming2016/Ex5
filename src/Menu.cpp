#include "Menu.h"

Menu::Menu(Socket *socket) {

    this->socket = socket;
    this->socket->initialize();
    this->mainFlow = new MainFlow;

}

Menu::~Menu() {

    delete this->mainFlow;
    delete this->socket;

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

void Menu::sendToSocketVehicle(unsigned int vehicleId) {

    Vehicle     *vehicle = getDriverVehicle(vehicleId);
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    this->getSocket()->sendData(serialVehicle);

}

Driver *Menu::listenToSocketForDriver() {

    char buffer[1024];
    this->socket->reciveData(buffer, 1024);

    Driver *driver;
    this->serializer.deserialize(buffer, sizeof(buffer), driver);

    return driver;

}

Serializer Menu::getSerializer() {
    return this->serializer;
}

int Menu::runMenu() {

    int userOption = 0;
    int i          = 0;

    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1: {
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                Driver *driver;

                // Receive driver objects from client
                for (i = 0; i < numOfDrivers; i++) {

                    driver = this->listenToSocketForDriver();
                    this->getMainFlow()->getTaxiCenter()->addDriver(driver);

                    sendToSocketVehicle(driver->getVehicleId());
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

                // Send to eache driver exit command
                this->getSocket()->sendData("exit");
                this->getMainFlow()->exitSystem();

                // Advance one step
            case 9:

                // Check that all the trips that need to start are attached
                // to a driver
                this->getMainFlow()->getTaxiCenter()->assignTrip(
                        *(this->getSocket()), this->getSerializer());

                // Move all the taxis one step
                this->getMainFlow()->getTaxiCenter()->moveOneStep(
                        *(this->getSocket()), this->getSerializer());

                // Invalid input
                break;
        }
    }
}

Vehicle *Menu::getDriverVehicle(unsigned int vehicleId) {

    std::vector<Vehicle *> vehicles = this->getMainFlow()->getTaxiCenter()->
            getVehicles();
    for (int               i        = 0; i < vehicles.size(); ++i) {

        if (vehicles[i]->getVehicleId() == vehicleId) {

            return vehicles[i];
        }
    }
}

