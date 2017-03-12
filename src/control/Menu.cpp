#include "Menu.h"
#include <pthread.h>
//#include <boost/log/trivial.hpp>

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
    Grid *grid = NULL;

    while (grid == NULL) {
        grid = this->stringParser.parseGridInput();
        if (grid == NULL) {
            std::cout << "-1" << std::endl;
        }
    }

    //Create Grid with obstacles.
    this->getMainFlow()->createMap(grid);
    this->getMainFlow()->createTaxiCenter(&location);
    this->GUIDescriptor = this->initializeGUI(grid->getWidth(),
                                              grid->getLength());
}

int Menu::validateNumOfDrivers() {

    int numOfDrivers;
    char buffer[1024];

    // Wait for gui to send num of drivers
    this->getMainFlow()->getSocket()->receiveData(buffer, 1024,
                                                  this->GUIDescriptor);

    numOfDrivers = stoi(buffer);

    if (numOfDrivers < 0) {
        return -1;
    }

    return numOfDrivers;

}

int Menu::validateUserOption() {

    int userOption;
    char buffer[1024];

    // Wait for gui to send next step
    this->getMainFlow()->getSocket()->receiveData(buffer, 1024,
                                                  this->GUIDescriptor);

    userOption = stoi(buffer);

    if (userOption <= 0 || userOption == 5 || userOption == 6 ||
        userOption == 8 || userOption > 9) {
        return -1;
    }

    return userOption;
}

int Menu::initializeGUI(int gridWidth, int gridLength) {

    std::string gridSize = boost::lexical_cast<std::string>(gridWidth)
                           + ' ' + boost::lexical_cast<std::string>(gridLength);

    Socket *skt = this->getMainFlow()->getSocket();

    // Wait for the GUI to connect to the server.
    int guiDescriptor = skt->callAccept();

    // Send GUIClient the grid size.
    skt->sendData(gridSize, guiDescriptor);

    return guiDescriptor;
}

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        userOption = this->validateUserOption();

        if (userOption == -1) {
            this->getMainFlow()->getSocket()->sendData("Error",
                                                       this->GUIDescriptor);
            continue;
        }

        switch (userOption) {

            // Create driver
            case 1: {
                int numOfDrivers = 0;
                numOfDrivers = this->validateNumOfDrivers();

                if (numOfDrivers == -1) {
                    this->getMainFlow()->getSocket()->sendData("Error",
                                                               this->GUIDescriptor);
                    continue;
                }

                this->getMainFlow()->selectDrivers(numOfDrivers,
                                                   this->GUIDescriptor);
                break;
            }
                // Create trip
            case 2: {
                Trip *tempTrip = this->stringParser.parseTripInput(
                        this->getMainFlow()->getTaxiCenter()->getTrips(),
                        this->getMainFlow()->getSocket(), this->GUIDescriptor);

                if (tempTrip == 0) {
                    this->getMainFlow()->getSocket()->sendData("Error",
                                                               this->GUIDescriptor);
                    continue;
                }
                if (tempTrip->getStartPoint() == tempTrip->getEndPoint()) {
                    continue;
                }
                this->getMainFlow()->createTrip(tempTrip);
                break;
            }
                // Create vehicle
            case 3: {
                Vehicle *tempVehicle;
                tempVehicle = this->stringParser.parseVehicleInput(
                        this->getMainFlow()->getTaxiCenter()->getVehicles(),
                        this->getMainFlow()->getSocket(), this->GUIDescriptor);

                if (tempVehicle == 0) {
                    this->getMainFlow()->getSocket()->sendData("Error",
                                                               this->GUIDescriptor);
                    continue;
                }
                this->getMainFlow()->createVehicle(tempVehicle);
                break;
            }

                // Request driver location
            case 4: {

                unsigned int driverLocation;
                driverLocation = this->stringParser.parseDriverLocation(
                        this->getMainFlow()->getTaxiCenter()->getDrivers(),
                        this->getMainFlow()->getSocket(), this->GUIDescriptor);

                if (driverLocation == -1) {
                    this->getMainFlow()->getSocket()->sendData("Error",
                                                               this->GUIDescriptor);
                    continue;
                }

                this->getMainFlow()->getTaxiCenter()->requestDriverLocation(
                        driverLocation);
                break;
            }
                /*
                // Start Driving
            case 6:
                this->getMainFlow()->startDriving();
                break;
                */
                //Exit system
            case 7: {

                std::vector<ClientThread *>
                        clientThreadVec = this->getMainFlow()->getClientThreadVector();
                // Send each driver exit command
                this->wakeUpThreads(7);
                for (int i = 0; i < clientThreadVec.size(); i++) {
                    pthread_join(clientThreadVec.at(i)->getThread(), NULL);
                }

                // Signal the GUI to exit.
                this->getMainFlow()->getSocket()->sendData("exit",
                                                           this->GUIDescriptor);

                this->getMainFlow()->exitSystem();
            }

                // Advance one step
            case 9:

                //BOOST_LOG_TRIVIAL(debug) << "Program time:"
                //                         << this->mainFlow->getTaxiCenter()->getClock()->getTime();
                this->wakeUpThreads(9);
                this->getMainFlow()->clockSleep();
                this->mainFlow->getTaxiCenter()->getClock()->increaseTime();
                std::string taxiLocations = "";

                // TODO: find why the casting doesn't work
                // Create string with all the locations of the taxis.
                for (int i = 0; i <
                                getMainFlow()->getTaxiCenter()->getTaxis().size(); i++) {

                    taxiLocations + boost::lexical_cast<std::string>(
                            getMainFlow()->getTaxiCenter()->getTaxis().at(
                                    i)->getCurrentPosition().getXCoordinate())
                    +
                            ',' + boost::lexical_cast<std::string>(
                            getMainFlow()->getTaxiCenter()->getTaxis().at(
                                    i)->getCurrentPosition().getYCoordinate()) +
                    ' ';
                }

                // Send the locations of the taxis to the GUI.
                this->getMainFlow()->getSocket()->sendData(taxiLocations,
                                                           this->GUIDescriptor);

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



