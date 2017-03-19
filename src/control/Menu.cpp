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
    this->GUIDescriptor = this->initializeGUI(*grid);
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

    try {

        userOption = stoi(buffer);

        if (userOption <= 0 || userOption == 5 || userOption == 6 ||
            userOption == 8 || userOption > 9 || strlen(buffer) > 1) {
            return -1;
        }

        return userOption;

    } catch (std::exception &e) {

        return -1;

    }

}

int Menu::initializeGUI(Grid &grid) {

    // Prepare the grid size.
    std::string gridSize = boost::lexical_cast<std::string>(grid.getWidth())
                           + ' ' +
                           boost::lexical_cast<std::string>(grid.getLength())
                           + "\n";

    Socket *skt = this->getMainFlow()->getSocket();

    // Wait for the GUI to connect to the server.
    int guiDescriptor = skt->callAccept();

    // Send GUIClient the grid size.
    skt->sendData(gridSize, guiDescriptor);

    // Prepare obstacles.
    std::string obstacles;
    int obstacleNum = grid.getObstacles().size();

    for (int i = 0; i < obstacleNum; i++) {

        obstacles += boost::lexical_cast<std::string>(
                grid.getObstacles().at(i).getXCoordinate()) + ',' +
                     boost::lexical_cast<std::string>(
                             grid.getObstacles().at(i).getYCoordinate()) + ' ';
    }

    obstacles += "\n";

    // Send obstacles location to GUI.
    skt->sendData(obstacles, guiDescriptor);

    return guiDescriptor;
}

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {
        userOption = this->validateUserOption();

        // If user input is invalid.
        if (userOption == -1) {
            this->getMainFlow()->getSocket()->sendData("error\n",
                                                       this->GUIDescriptor);
            continue;
        }

        switch (userOption) {

            // Create driver
            case 1: {
                int numOfDrivers = 0;
                numOfDrivers = this->validateNumOfDrivers();

                // If user input is invalid.
                if (numOfDrivers == -1) {
                    this->getMainFlow()->getSocket()->sendData("error\n",
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

                // If user input is invalid.
                if (tempTrip == 0) {
                    this->getMainFlow()->getSocket()->sendData("error\n",
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

                // If user input is invalid.
                if (tempVehicle == 0) {
                    this->getMainFlow()->getSocket()->sendData("error\n",
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

                // If user input is invalid.
                if (driverLocation == -1) {
                    this->getMainFlow()->getSocket()->sendData("error\n",
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
                        clientThreadVec = this->getMainFlow()->
                        getClientThreadVector();
                // Send each driver exit command
                this->wakeUpThreads(7);
                for (int i = 0; i < clientThreadVec.size(); i++) {
                    pthread_join(clientThreadVec.at(i)->getThread(), NULL);
                }

                // Signal the GUI to exit.
                this->getMainFlow()->getSocket()->sendData("close\n",
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

                // Create string with all the locations of the taxis.
                for (int i = 0; i <
                                getMainFlow()->getTaxiCenter()->getTaxis().size(); i++) {

                    // Concat the locations of all the taxis
                    taxiLocations += boost::lexical_cast<std::string>(
                            getMainFlow()->getTaxiCenter()->getTaxis().at(
                                    i)->getCurrentPosition().getXCoordinate())
                    +
                    ',' + boost::lexical_cast<std::string>(
                            getMainFlow()->getTaxiCenter()->getTaxis().at(
                                    i)->getCurrentPosition().getYCoordinate()) +
                    ' ';
                }

                taxiLocations += "\n";

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



