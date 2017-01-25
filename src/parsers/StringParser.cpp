

#include <cstring>
#include "cstdlib"
#include <sstream>
#include "StringParser.h"

#include "../control/MainFlow.h"

Driver *StringParser::parseDriverInput() {

    int numOfParams = 5;
    int id = 0;
    int age = 1;
    int status = 2;
    int experience = 3;
    int vehicleId = 4;

    std::string inputArr[numOfParams];
    std::string userInput;

    try {

        std::cin >> userInput;

        if (this->splitByComma(inputArr, numOfParams, userInput)) {
            return NULL;
        }

        // If invalid input was given
        if (this->validateInputSize(inputArr, numOfParams) ||
            this->validateDriverInput(inputArr, numOfParams)) {
            return NULL;
        }

        return new Driver(atoi(inputArr[id].c_str()),
                          atoi(inputArr[age].c_str()),
                          inputArr[status][0],
                          atoi(inputArr[experience].c_str()),
                          atoi(inputArr[vehicleId].c_str()));

    } catch (exception &e) {
        return NULL;
    }

}

int StringParser::validateDriverInput(std::string inputArr[], int numOfParams) {

    int i = 0;

    for (i = 0; i < numOfParams; i++) {

        // Checks that all relevant input is positive and of type int
        if (i != 2) {
            if (atoi(inputArr[i].c_str()) < 0) {
                return 1;
            }
        } else {

            // If driver status not S, W, M or D return 1
            if (!(inputArr[i] == "S" || inputArr[i] == "M" ||
                  inputArr[i] == "W" || inputArr[i] == "D")) {
                return 1;
            }
        }
    }

    return 0;

}

int StringParser::validateInputSize(std::string *inputArr, int numOfParams) {

    int i = 0;
    for (i = 0; i < numOfParams; i++) {

        // Checks if not all expected params were given
        if (inputArr[i].empty()) {
            return 1;
        }
    }
    return 0;
}

int StringParser::checkIntValidity(bool canBeZero) {
    int num;
    std::cin >> num;
    if (std::cin.fail() || canBeZero || num < 0) {
        std::cin.clear();
        return -1;
    }
    else if(std::cin.fail() || num <= 0) {
        std::cin.clear();
        return -1;
    }
    return 0;
}

Grid *StringParser::parseGridInput() {

    int width = 0;
    int height = 0;
    int numOfObstacles = 0;
    int numOfParams = 2;
    int x = 0;
    int y = 1;

    try {

        height = this->checkIntValidity(false);
        if(height == -1) {
            return NULL;
        }

        width = this->checkIntValidity(false);
        if(width == -1) {
            return NULL;
        }

        numOfObstacles = this->checkIntValidity(true);
        if(numOfObstacles == -1) {
            return NULL;
        }

        std::vector<Point> obstacles;
        std::string inputArr[numOfParams];
        std::string userInput;

        for (int i = 0; i < numOfObstacles; ++i) {

            std::cin >> userInput;
            if (this->splitByComma(inputArr, numOfParams, userInput)) {
                return NULL;
            }

            // If input is invalid
            if (this->validateBasicInput(inputArr, numOfParams)) {
                return NULL;
            }

            obstacles.push_back(
                    Point(atoi(inputArr[x].c_str()),
                          atoi(inputArr[y].c_str())));
        }

        return new Grid(height, width, obstacles);
    } catch(exception &e) {
        return NULL;
    }

}

int StringParser::validateBasicInput(string *inputArr, int numOfParams) {

    int i = 0;
    bool isNotZeroFlag = false;

    // Check that all input is positive int
    for (i = 0; i < numOfParams; i++) {
        isNotZeroFlag = false;
        if (inputArr[i] != "0") {
            isNotZeroFlag = true;
        }
        // If negative number was given
        if (isNotZeroFlag && atoi(inputArr[i].c_str()) <= 0) {
            return 1;
        }
        else if(!isNotZeroFlag && atoi(inputArr[i].c_str()) < 0) {
            return 1;
        }
    }

    return 0;

}

Trip *StringParser::parseTripInput() {

    int numOfParams = 8;
    int id = 0;
    int startX = 1;
    int startY = 2;
    int endX = 3;
    int endY = 4;
    int numOfPassengers = 5;
    int tariff = 6;
    int time = 7;
    std::string userInput;
    std::string inputArr[numOfParams];

    try {

        std::cin >> userInput;

        if (this->splitByComma(inputArr, numOfParams, userInput)) {
            return NULL;
        }

        if (this->validateInputSize(inputArr, numOfParams) ||
                this->validateBasicInput(inputArr, numOfParams)) {
            return NULL;
        }

        Point sPoint(atoi(inputArr[startX].c_str()),
                     atoi(inputArr[startY].c_str()));
        Point ePoint(atoi(inputArr[endX].c_str()),
                     atoi(inputArr[endY].c_str()));

        return new Trip(atoi(inputArr[id].c_str()), sPoint, ePoint,
                        atoi(inputArr[numOfPassengers].c_str()),
                        atof(inputArr[tariff].c_str()),
                        atoi(inputArr[time].c_str()));
    } catch (exception &e) {
        return NULL;
    }
}

int
StringParser::validateVehicleInput(std::string inputArr[], int numOfParams) {

    int i = 0;
    bool isNotZeroFlag = false;

    for (i = 0; i < numOfParams; i++) {
        if (i > 1) {

            // Check if manufacturer input is valid
            if (i == 2 &&
                !(inputArr[i] == "H" || inputArr[i] == "S" ||
                  inputArr[i] == "F" || inputArr[i] == "T")) {
                return 1;
            }
                // Check if Color input is valid
            else if (i == 3 && !(inputArr[i]  == "R" ||
                       inputArr[i] == "P" ||
                       inputArr[i] == "B" ||
                       inputArr[i] == "G" ||
                       inputArr[i] == "W")) {
                return 1;
            }
        } else {

            if (inputArr[i] != "0") {
                isNotZeroFlag = true;
            }
            // If negative number was given
            if (isNotZeroFlag && atoi(inputArr[i].c_str()) <= 0) {
                return 1;
            }
            else if(!isNotZeroFlag && atoi(inputArr[i].c_str()) < 0) {
                return 1;
            }
        }
    }
    return 0;
}

Vehicle *StringParser::parseVehicleInput() {

    int numOfInputs = 4;
    int id = 0;
    int taxiType = 1;
    int manufacturer = 2;
    int color = 3;
    std::string inputArr[numOfInputs];
    std::string userInput;

    try {
        std::cin >> userInput;

        // Splits the user input by commas and returns array of inputs
        if (this->splitByComma(inputArr, numOfInputs, userInput)) {
            return NULL;
        }

        if (this->validateInputSize(inputArr, numOfInputs) ||
            this->validateVehicleInput(inputArr, numOfInputs)) {
            return NULL;
        }

        return this->vehicleFactory.makeVehicle(atoi(inputArr[id].c_str()),
                                                atoi(inputArr[taxiType].c_str()),
                                                inputArr[manufacturer][0],
                                                inputArr[color][0]);
    } catch (exception &e) {
        return NULL;
    }
}

unsigned int StringParser::parseDriverLocation() {

    int driverId;

    try {

        std::cin >> driverId;
        if (std::cin.fail() || driverId < 0) {
            std::cin.clear();
            return NULL;
        }
        return driverId;
    } catch (exception &e) {
        return NULL;
    }

}

int StringParser::splitByComma(std::string *inputArr, int size,
                                std::string userInput) {

    std::stringstream ss(userInput);

    int i = 0;

    if (!userInput.find(',')) {
        return 1;
    }

    // Split the input by commas
    for (i = 0; i < size; i++) {
        std::getline(ss, inputArr[i], ',');
    }
    return 0;

}

