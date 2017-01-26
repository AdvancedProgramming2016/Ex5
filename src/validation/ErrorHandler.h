
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

    bool validateDriver(std::string *input);

    bool isNumber(std::string input);

    bool isAStatus(char status);

    int validateInputSize(std::string inputArr[], int numOfParams);

    int validateBasicInput(std::string *inputArr, int numOfParams);

    int validateDriverInput(std::string inputArr[], int numOfParams);

    int validateVehicleInput(std::string *inputArr, int numOfParams);

    int checkIntValidity(bool canBeZero);


};


#endif //EX4_ERRORHANDLER_H
