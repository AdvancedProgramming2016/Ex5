#include <iostream>
#include <unistd.h>
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