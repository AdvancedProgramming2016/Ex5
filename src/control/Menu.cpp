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
}

int Menu::validateNumOfDrivers() {

    int numOfDrivers = 0;

    // Receive from user num of drivers to create
    std::cin >> numOfDrivers;

    if (numOfDrivers < 0 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }
    return numOfDrivers;

}

int Menu::validateUserOption() {

    int userOption = 0;

    std::cin >> userOption;

    if (userOption < 0 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return userOption;
}

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        userOption = this->validateUserOption();

        if (userOption == -1) {
            std::cout << "-1" << std::endl;
            continue;
        }

        switch (userOption) {

            // Create driver
            case 1: {
                int numOfDrivers = 0;
                numOfDrivers = this->validateNumOfDrivers();

                if (numOfDrivers == 1) {
                    std::cout << "-1" << std::endl;
                    continue;
                }

                this->getMainFlow()->selectDrivers(numOfDrivers);
                break;
            }
                // Create trip
            case 2: {
                Trip *tempTrip = this->stringParser.parseTripInput();
                if (tempTrip == NULL) {
                    std::cout << "-1" << std::endl;
                    continue;
                }
                this->getMainFlow()->createTrip(tempTrip);
                break;
            }
                // Create vehicle
            case 3: {
                Vehicle *tempVehicle;
                tempVehicle = this->stringParser.parseVehicleInput();
                if (tempVehicle == NULL) {
                    std::cout << "-1" << std::endl;
                    continue;
                }
                this->getMainFlow()->createVehicle(tempVehicle);
                break;
            }

                // Request driver location
            case 4: {

                unsigned int driverLocation;
                driverLocation = this->stringParser.parseDriverLocation();
                if (driverLocation == NULL) {
                    std::cout << "-1" << std::endl;
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

                std::vector<ClientThread *> clientThreadVec = this->getMainFlow()->getClientThreadVector();
                // Send each driver exit command
                this->wakeUpThreads(7);
                for (int i = 0; i < clientThreadVec.size(); i++) {
                    pthread_join(clientThreadVec.at(i)->getThread(), NULL);
                }
                this->getMainFlow()->exitSystem();
            }

                // Advance one step
            case 9:

                //BOOST_LOG_TRIVIAL(debug) << "Program time:"
                //                         << this->mainFlow->getTaxiCenter()->getClock()->getTime();
                this->wakeUpThreads(9);
                this->getMainFlow()->clockSleep();
                this->mainFlow->getTaxiCenter()->getClock()->increaseTime();
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



