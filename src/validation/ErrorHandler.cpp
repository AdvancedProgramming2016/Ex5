
//#include <boost/log/trivial.hpp>
#include <sstream>
#include <limits>
#include <algorithm>
#include "ErrorHandler.h"

bool ErrorHandler::validateDriver(std::string *input) {

    if (!(isNumber(input[0]) && atoi(input[0].c_str()) >= 0)) {

        //BOOST_LOG_TRIVIAL(info) << "Invalid id";
        return false;

    } else if (!(isNumber(input[1]) && atoi(input[1].c_str()) >= 0)) {

        //BOOST_LOG_TRIVIAL(info) << "Invalid age";
        return false;

    } else if (!(input[2].size() == 1 && isAStatus((input[2][0])))) {

        //BOOST_LOG_TRIVIAL(info) << "Invalid status";
        return false;

    } else if (!(isNumber(input[3]) && atoi(input[3].c_str()) >= 0)) {

        //BOOST_LOG_TRIVIAL(info) << "Invalid experience";
        return false;

    } else if (!(isNumber(input[4]) && atoi(input[4].c_str()) >= 0)) {

        //BOOST_LOG_TRIVIAL(info) << "Invalid vehicle id";
        return false;
    }

    return true;

}

bool ErrorHandler::isNumber(std::string input) {

    std::string::const_iterator it = input.begin();

    while (it != input.end() && std::isdigit(*it)) {

        ++it;
    }

    return !input.empty() && it == input.end();

}

bool ErrorHandler::isAStatus(char status) {

    bool retVal = false;

    switch (status) {
        case 'S':

            retVal = true;
            break;

        case 'M':

            retVal = true;
            break;

        case 'W':

            retVal = true;
            break;

        case 'D':

            retVal = true;
            break;

        default:

            retVal = false;
            break;
    }

    return retVal;
}


int ErrorHandler::validateInputSize(std::string *inputArr, int numOfParams) {

    int i = 0;
    for (i = 0; i < numOfParams; i++) {

        // Checks if not all expected params were given
        if (inputArr[i].empty()) {
            return 1;
        }
    }
    return 0;
}

int ErrorHandler::checkIntValidity(bool canBeZero) {
    int num;
    std::cin >> num;
    if (canBeZero && (std::cin.fail() || num < 0)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    } else if (!canBeZero && (std::cin.fail() || num <= 0)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return num;
}

int ErrorHandler::validateBasicInput(std::string *inputArr, int numOfParams) {

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
        } else if (!isNotZeroFlag && atoi(inputArr[i].c_str()) < 0) {
            return 1;
        }
    }

    return 0;

}

int
ErrorHandler::validateVehicleInput(std::string inputArr[], int numOfParams) {

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
            else if (i == 3 && !(inputArr[i] == "R" ||
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
            } else if (!isNotZeroFlag && atoi(inputArr[i].c_str()) < 0) {
                return 1;
            }
        }
    }
    return 0;
}

int ErrorHandler::splitByComma(std::string *inputArr, int size,
                               std::string userInput) {

    std::stringstream ss(userInput);

    int i = 0;

    // Checks if the string ends with a ',' or not ',' given
    if (!userInput.find(',') || userInput.at(userInput.length() - 1) == ',' ||
        std::count(userInput.begin(), userInput.end(), ',') >= size) {
        return 1;
    }

    // Split the input by commas
    for (i = 0; i < size; i++) {
        std::getline(ss, inputArr[i], ',');
    }

    return 0;

}
