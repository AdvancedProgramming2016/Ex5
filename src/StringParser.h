
#ifndef EX2_CHECK_STRINGPARSER_H
#define EX2_CHECK_STRINGPARSER_H

#include "BaseParser.h"
#include "VehicleFactory.h"
#include <string>

class Graph;

class Driver;

class TaxiCenter;

class StringParser : BaseParser {

private:

    VehicleFactory vehicleFactory;


public:

    int validateInputSize(std::string inputArr[], int numOfParams);

    int validateBasicInput(std::string *inputArr, int numOfParams);

    int validateDriverInput(std::string inputArr[], int numOfParams);

    /*
     * Splits the string by commas.
     */
    int splitByComma(std::string *inputArr, int size, std::string userInput);

    int validatePoint(std::string inputArr[], int numOfParams);

    /*
     * Parses the grid input from the console.
     */
    virtual Grid *parseGridInput();

    /*
     * Parses the driver input from the console.
     */
    virtual Driver *parseDriverInput();

    /*
     * Parses the trip input from the console.
     */
    virtual Trip *parseTripInput();

    /*
     * Parses the vehicle input from the console.
     */
    virtual Vehicle *parseVehicleInput();

    /*
     * Parses the driver input from the console.
     */
    virtual unsigned int parseDriverLocation();

    int validateVehicleInput(std::string *inputArr, int numOfParams);

    int checkIntValidity(bool canBeZero);
};

#endif //EX2_CHECK_STRINGPARSER_H
