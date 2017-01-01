
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

    /*
     * Splits the string by commas.
     */
    void splitByComma(std::string *inputArr, int size, std::string userInput);

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

};

#endif //EX2_CHECK_STRINGPARSER_H
