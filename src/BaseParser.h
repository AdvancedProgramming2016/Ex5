
#ifndef EX2_CHECK_BASEPARSER_H
#define EX2_CHECK_BASEPARSER_H

class Driver;
class Grid;
class Trip;
class Vehicle;

class BaseParser {

public:

    /*
     * Receives the user input for the grid.
     */
    virtual Grid *parseGridInput() = 0;

    /*
     * Receives the user input for the driver.
     */
    virtual Driver *parseDriverInput() = 0;

    /*
     * Receives the user input for the trip.
     */
    virtual Trip *parseTripInput() = 0;

    /*
     * Receives the user input for the
     */
    virtual Vehicle *parseVehicleInput() = 0;
};

#endif //EX2_CHECK_BASEPARSER_H
