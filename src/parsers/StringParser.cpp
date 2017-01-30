

#include <cstring>
#include "cstdlib"
#include <sstream>
#include "StringParser.h"

#include "../control/MainFlow.h"

Driver *StringParser::parseDriverInput() {

    int  numOfParams  = 5;
    int  id           = 0;
    int  age          = 1;
    int  status       = 2;
    int  experience   = 3;
    int  vehicleId    = 4;
    bool isValidInput = false;

    std::string inputArr[numOfParams];
    std::string userInput;

    std::cin >> userInput;

    this->errorHandler.splitByComma(inputArr, numOfParams, userInput);

    //Check that the user input has the proper format.
    this->errorHandler.validateInputSize(inputArr, numOfParams);

    //Validate user input.
    isValidInput = this->errorHandler.validateDriver(inputArr);

    //If the user input was valid, return a driver instance.
    if (isValidInput) {

        return new Driver(atoi(inputArr[id].c_str()),
                          atoi(inputArr[age].c_str()),
                          inputArr[status][0],
                          atoi(inputArr[experience].c_str()),
                          atoi(inputArr[vehicleId].c_str()));
    }

    return 0;


}


Grid *StringParser::parseGridInput() {

    int width          = 0;
    int height         = 0;
    int numOfObstacles = 0;
    int numOfParams    = 2;
    int x              = 0;
    int y              = 1;

    try {

        height = this->errorHandler.checkIntValidity(false);
        if (height == -1) {
            return 0;
        }

        width = this->errorHandler.checkIntValidity(false);
        if (width == -1) {
            return 0;
        }

        numOfObstacles = this->errorHandler.checkIntValidity(true);
        if (numOfObstacles == -1) {
            return 0;
        }

        std::vector<Point> obstacles;
        std::string        inputArr[numOfParams];
        std::string        userInput;

        // Gets obstacles location
        for (int i = 0; i < numOfObstacles; ++i) {

            std::cin >> userInput;
            if (this->errorHandler.splitByComma(inputArr, numOfParams,
                                                userInput)) {
                return 0;
            }

            if (atoi(inputArr[x].c_str()) >= height ||
                atoi(inputArr[y].c_str()) >= width) {
                return 0;
            }

            // If input is invalid
            if (this->errorHandler.validateBasicInput(inputArr, numOfParams)) {
                return 0;
            }

            obstacles.push_back(
                    Point(atoi(inputArr[x].c_str()),
                          atoi(inputArr[y].c_str())));
        }

        return new Grid(height, width, obstacles);
    } catch (exception &e) {
        return 0;
    }

}

Trip *StringParser::parseTripInput(std::vector<Trip *> &tripVec) {

    int         numOfParams     = 8;
    int         id              = 0;
    int         startX          = 1;
    int         startY          = 2;
    int         endX            = 3;
    int         endY            = 4;
    int         numOfPassengers = 5;
    int         tariff          = 6;
    int         time            = 7;
    std::string userInput;
    std::string inputArr[numOfParams];

    try {

        std::cin >> userInput;

        if (this->errorHandler.splitByComma(inputArr, numOfParams, userInput)) {
            return 0;
        }

        if (this->errorHandler.validateInputSize(inputArr, numOfParams) ||
            this->errorHandler.validateBasicInput(inputArr, numOfParams) ||
            !this->errorHandler.isUniqueTrip(atoi(inputArr[id].c_str()),
                                             tripVec)) {
            return 0;
        }

        Point sPoint(atoi(inputArr[startX].c_str()),
                     atoi(inputArr[startY].c_str()));
        Point ePoint(atoi(inputArr[endX].c_str()),
                     atoi(inputArr[endY].c_str()));

        if (atoi(inputArr[numOfPassengers].c_str()) < 1 ||
            atoi(inputArr[time].c_str()) < 1) {
            return 0;
        }

        return new Trip(atoi(inputArr[id].c_str()), sPoint, ePoint,
                        atoi(inputArr[numOfPassengers].c_str()),
                        atof(inputArr[tariff].c_str()),
                        atoi(inputArr[time].c_str()));
    } catch (exception &e) {
        return 0;
    }
}


Vehicle *StringParser::parseVehicleInput(std::vector<Vehicle *> &vehicleVec) {

    int         numOfInputs  = 4;
    int         id           = 0;
    int         taxiType     = 1;
    int         manufacturer = 2;
    int         color        = 3;
    std::string inputArr[numOfInputs];
    std::string userInput;

    try {
        std::cin >> userInput;

        // Splits the user input by commas and returns array of inputs
        if (this->errorHandler.splitByComma(inputArr, numOfInputs, userInput)) {
            return 0;
        }

        if (this->errorHandler.validateInputSize(inputArr, numOfInputs) ||
            this->errorHandler.validateVehicleInput(inputArr, numOfInputs) ||
            !this->errorHandler.isUniqueVehicle(
                    atoi(inputArr[id].c_str()), vehicleVec)) {
            return 0;
        }

        return this->vehicleFactory.makeVehicle(atoi(inputArr[id].c_str()),
                                                atoi(inputArr[taxiType].c_str()),
                                                inputArr[manufacturer][0],
                                                inputArr[color][0]);
    } catch (exception &e) {
        return 0;
    }
}

unsigned int
StringParser::parseDriverLocation(std::vector<Driver *> &driverVec) {

    int  driverId, i, driverVecSize;
    bool isDriverInVec = false;

    try {

        std::cin >> driverId;
        if (std::cin.fail() || driverId < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }
        driverVecSize = driverVec.size();
        for (i        = 0; i < driverVecSize; i++) {
            if (driverVec[i]->getDriverId() == driverId) {
                isDriverInVec = true;
            }
        }
        if (isDriverInVec) {
            return driverId;
        } else {
            return -1;
        }

    } catch (exception &e) {
        return -1;
    }

}


