#include <iostream>
#include <unistd.h>
#include "src/Driver.h"
#include "sockets/Tcp.h"
#include "src/StandardVehicle.h"
#include "src/Menu.h"
//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>

int main(int argc, char *argv[]) {

    //Print only logging warning or higher level
    //boost::log::core::get()->set_filter(
    //boost::log::trivial::severity >= boost::log::trivial::warning);
    //Create the socket.
    Socket *socket = new Tcp(true, atoi(argv[1]));
    Menu   menu(socket);

    //Initializes and runs the menu.
    menu.initializeGame();
    menu.runMenu();

}