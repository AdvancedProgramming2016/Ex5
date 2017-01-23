
#include "ErrorHandler.h"

bool ErrorHandler::ValidatePath(Bfs &bfs) {

    try{

        bfs.getShortestPath().size();
    }
    catch (std::exception& e){

        return false;
    }

    return true;
}
