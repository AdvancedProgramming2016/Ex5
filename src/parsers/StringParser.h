
#ifndef EX2_CHECK_STRINGPARSER_H
#define EX2_CHECK_STRINGPARSER_H

#include "../validation/ErrorHandler.h"
#include "BaseParser.h"
#include "../taxi/VehicleFactory.h"
#include <string>
#include "../serializers/Serializer.h"

class Graph;

class Driver;

class TaxiCenter;

class Serializer;

class StringParser : BaseParser {

private:

    VehicleFactory vehicleFactory;
    ErrorHandler errorHandler;
    Serializer serializer;

public:

    /*
     * Parses the grid input from the console.
     */
    virtual Grid *parseGridInput();

    /*
     * Parses the driver input from the console.
     */
    virtual Driver *parseDriverInput(std::string userInput);

    /*
     * Parses the trip input from the console.
     */
    virtual Trip *parseTripInput(std::vector<Trip *> &tripVec, Socket *skt,
                                 int guiDescriptor, int height, int width);

    /*
     * Parses the vehicle input from the console.
     */
    virtual Vehicle *
    parseVehicleInput(std::vector<Vehicle *> &vehicleVec, Socket *skt,
                      int guiDescriptor);

    /*
     * Parses the driver input from the console.
     */
    virtual unsigned int parseDriverLocation(std::vector<Driver *> &driverVec, Socket *skt, int guiDescriptor);

};

#endif //EX2_CHECK_STRINGPARSER_H
