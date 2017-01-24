
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
     * Check that the path is reaching the destination.
     */
    bool ValidatePath(Bfs &bfs);


    bool validateDriver(std::string *input);

    bool isNumber(std::string input);

    bool isAStatus(char status);

};


#endif //EX4_ERRORHANDLER_H
