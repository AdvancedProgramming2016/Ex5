
#include <boost/log/trivial.hpp>
#include "ErrorHandler.h"

bool ErrorHandler::ValidatePath(Bfs &bfs) {

    try {

        bfs.getShortestPath().size();
    }
    catch (std::exception &e) {

        return false;
    }

    return true;
}

bool ErrorHandler::validateDriver(std::string *input) {

    if (!(isNumber(input[0]) && atoi(input[0].c_str()) >= 0)) {

        BOOST_LOG_TRIVIAL(info) << "Invalid id";
        return false;

    } else if (!(isNumber(input[1]) && atoi(input[1].c_str()) >= 0)) {

        BOOST_LOG_TRIVIAL(info) << "Invalid age";
        return false;

    } else if (!(input[2].size() == 1 && isAStatus((input[2][0])))) {

        BOOST_LOG_TRIVIAL(info) << "Invalid status";
        return false;

    } else if (!(isNumber(input[3]) && atoi(input[3].c_str()) >= 0)) {

        BOOST_LOG_TRIVIAL(info) << "Invalid experience";
        return false;

    } else if (!(isNumber(input[4]) && atoi(input[4].c_str()) >= 0)) {

        BOOST_LOG_TRIVIAL(info) << "Invalid vehicle id";
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
