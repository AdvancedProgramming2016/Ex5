
#ifndef EX4_ERRORHANDLER_H
#define EX4_ERRORHANDLER_H

#include "../algorithms/Bfs.h"

/**
 * The class handles error in the program.
 * Deals with user input validation, and program exceptions.
 */
class ErrorHandler {

public:

    /*
    * Splits the string by commas.
    */
    int splitByComma(std::string *inputArr, int size, std::string userInput);

    /*
     * Validate the driver.
     */
    bool validateDriver(std::string *input);

    /*
     * Check if the input is a number.
     */
    bool isNumber(std::string input);

    /*
     * Check if it's a valid status.
     */
    bool isAStatus(char status);

    /*
     * Validate the input size.
     */
    int validateInputSize(std::string inputArr[], int numOfParams);

    /*
     * Validate that the input is in the right format.
     */
    int validateBasicInput(std::string *inputArr, int numOfParams);

    /*
     * Validate the vehicle input.
     */
    int validateVehicleInput(std::string *inputArr, int numOfParams);

    /*
     * Check that the int is at the legal bounds.
     */
    int checkIntValidity(bool canBeZero);


};


#endif //EX4_ERRORHANDLER_H
