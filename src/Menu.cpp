#include "Menu.h"

Menu::Menu(Socket *socket) {

    // Open server side socket on port 5555
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

    // TODO: Didn't understand what kind of vehicle we need to send back
    Vehicle *vehicle = getDriverVehicle(vehicleId);
    char buffer2[1024];
    std::string serialVehicle;
    serialVehicle = this->serializer.serialize(vehicle);

    this->getSocket()->sendData(serialVehicle);

}

Driver *Menu::listenToSocketForDriver() {

    char buffer[1024];
    this->socket->reciveData(buffer, 1024);

    std::cout << buffer << std::endl;
    Driver *driver;
    this->serializer.deserialize(buffer, sizeof(buffer), driver);

    return driver;

}

Serializer Menu::getSerializer() {
    return this->serializer;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

int Menu::runMenu() {

    int userOption = 0;
    int i = 0;
    
    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1:{
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                Driver *driver;
                //Vehicle *vehicle;

                // Receive driver objects from client
                for (i = 0; i < numOfDrivers; i++) {

                    std::cout << "waiting for client" << std::endl;
                    driver = this->listenToSocketForDriver();
                   // vehicle =  getDriverVehicle(driver->getVehicleId());
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

               // std::string exit = "exit";
                // Send to eache driver exit command
                this->getSocket()->sendData("exit");
                this->getMainFlow()->exitSystem();

                // Advance one step
            case 9:

                // Move all the taxis one step
                this->getMainFlow()->getTaxiCenter()->moveOneStep(
                        *(this->getSocket()), this->getSerializer());

                // Check that all the trips that need to start are attached
                // to a driver
                this->getMainFlow()->getTaxiCenter()->assignTrip(
                        *(this->getSocket()), this->getSerializer());

                // Invalid input
                break;
           // default:
                // Will be used in the next exercise.
                /*
                // Notify all taxis to exit program
                for (i = 0; i <
                            this->getMainFlow()->getTaxiCenter()->getTaxis().size(); i++) {
                    std::string exit = "exit";
                    // Send to eache driver exit command
                    this->getSocket()->sendData(exit);
                }
                exit(1);
                 */
        }
    }
}

Vehicle *Menu::getDriverVehicle(unsigned int vehicleId) {

    std::vector<Vehicle*> vehicles = this->getMainFlow()->getTaxiCenter()->getVehicles();
    for (int i = 0; i < vehicles.size(); ++i) {

        if(vehicles[i]->getVehicleId() == vehicleId){

            return vehicles[i];
        }
    }
}



#pragma clang diagnostic pop
