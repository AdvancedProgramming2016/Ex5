
#include <iostream>
#include "sockets/Udp.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "src/Driver.h"
#include "src/Serializer.h"
#include "src/StringParser.h"
#include <cstdlib>

int main(int argc, char *argv[]){

    //The socket connecting between the client and the server.
    Socket *socket = new Udp(0, atoi(argv[1]), argv[2]);

    //Serializer used for serializing and deserializing objects.
    Serializer serializer;
    //Will handle parsing the user input.
    StringParser stringParser;

    socket->initialize();

    //Creates a driver from a given user input.
    Driver * driver = stringParser.parseDriverInput();

    //Serializes the driver into a string.
    std::string serialDriver = serializer.serialize(driver);

    std::cout << serialDriver << std::endl;

    //Sends the string to the server
    socket->sendData(serialDriver);

    Vehicle * vehicle;
    char buffer[1024];

    //Receives data from the server.
    socket->reciveData(buffer, sizeof(buffer));
    std::cout<< buffer << endl;

    //Deserializes the data received from the server into a vehicle object.
    serializer.deserialize(buffer, sizeof(buffer), vehicle);

    std:: cout << vehicle->getCoefficient() << std::endl;


}