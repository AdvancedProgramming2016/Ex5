
#ifndef EX2_CHECK_STRINGPARSER_H
#define EX2_CHECK_STRINGPARSER_H

#include "../validation/ErrorHandler.h"
#include "BaseParser.h"
#include "../taxi/VehicleFactory.h"
#include <string>

class Graph;

class Driver;

class TaxiCenter;

class StringParser : BaseParser {

private:

    VehicleFactory vehicleFactory;
    ErrorHandler errorHandler;

public:

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
    virtual Trip *parseTripInput(std::vector<Trip *> &tripVec);

    /*
     * Parses the vehicle input from the console.
     */
    virtual Vehicle *parseVehicleInput(std::vector<Vehicle *> &vehicleVec);

    /*
     * Parses the driver input from the console.
     */
    virtual unsigned int parseDriverLocation(std::vector<Driver *> &driverVec);

};

#endif //EX2_CHECK_STRINGPARSER_H
