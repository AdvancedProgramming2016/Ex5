

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

    //TODO make sure it's in the right format first
    //check()

    this->splitByComma(inputArr, numOfParams, userInput);

    isValidInput = this->errorHandler.validateDriver(inputArr);

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

    unsigned width          = 0;
    unsigned height         = 0;
    int      numOfObstacles = 0;
    int      numOfParams    = 2;
    int      x              = 0;
    int      y              = 1;

    // Receive input from the user
    std::cin >> height;
    std::cin >> width;
    std::cin >> numOfObstacles;

    std::vector<Point> obstacles;
    std::string        inputArr[numOfParams];
    std::string        userInput;

    for (int i = 0; i < numOfObstacles; ++i) {

        std::cin >> userInput;
        this->splitByComma(inputArr, numOfParams, userInput);
        obstacles.push_back(
                Point(atoi(inputArr[x].c_str()), atoi(inputArr[y].c_str())));
    }

    return new Grid(height, width, obstacles);

}

Trip *StringParser::parseTripInput() {

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

    std::cin >> userInput;

    this->splitByComma(inputArr, numOfParams, userInput);

    Point sPoint(atoi(inputArr[startX].c_str()),
                 atoi(inputArr[startY].c_str()));
    Point ePoint(atoi(inputArr[endX].c_str()), atoi(inputArr[endY].c_str()));

    return new Trip(atoi(inputArr[id].c_str()), sPoint, ePoint,
                    atoi(inputArr[numOfPassengers].c_str()),
                    atof(inputArr[tariff].c_str()),
                    atoi(inputArr[time].c_str()));

}

Vehicle *StringParser::parseVehicleInput() {

    int         numOfInputs  = 4;
    int         id           = 0;
    int         taxiType     = 1;
    int         manufacturer = 2;
    int         color        = 3;
    std::string inputArr[numOfInputs];
    std::string userInput;

    std::cin >> userInput;

    // Splits the user input by commas and returns array of inputs
    this->splitByComma(inputArr, numOfInputs, userInput);

    return this->vehicleFactory.makeVehicle(atoi(inputArr[id].c_str()),
                                            atoi(inputArr[taxiType].c_str()),
                                            inputArr[manufacturer][0],
                                            inputArr[color][0]);
}

unsigned int StringParser::parseDriverLocation() {

    unsigned int driverId;

    std::cin >> driverId;

    return driverId;
}

void StringParser::splitByComma(std::string *inputArr, int size,
                                std::string userInput) {

    std::stringstream ss(userInput);

    int i = 0;
    // Split the input by commas
    for (i = 0; i < size; i++) {
        std::getline(ss, inputArr[i], ',');
    }

}
