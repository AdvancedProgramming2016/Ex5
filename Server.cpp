#include <iostream>
#include <unistd.h>
#include <boost/iostreams/device/array.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include "src/Driver.h"
#include "sockets/Tcp.h"
#include "src/StandardVehicle.h"
#include "src/Menu.h"

int main(int argc, char *argv[]){

    //Create the socket.
    Socket *socket = new Tcp(true, atoi(argv[1]));
    Menu menu(socket);

    //Initializes and runs the menu.
    menu.initializeGame();
    menu.runMenu();

}