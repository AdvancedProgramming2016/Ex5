
#include <iostream>
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
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "src/taxi/Driver.h"
#include "src/serializers/Serializer.h"
#include "src/parsers/StringParser.h"
#include "src/taxi/StandardVehicle.h"
#include "src/taxi/LuxuryVehicle.h"
#include "src/sockets/Tcp.h"
#include <cstdlib>
//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
#include <fstream>

//#include <boost/log/trivial.hpp>

BOOST_CLASS_EXPORT_GUID(StandardVehicle, "StandardVehicle")
BOOST_CLASS_EXPORT_GUID(LuxuryVehicle, "LuxuryVehicle")

/*
 * Closes the client.
 */
void closeClient(Taxi *taxi, Driver *driver, Vehicle *vehicle, Socket *socket);

int main(int argc, char *argv[]) {

    //Print only logging warning or higher level
    //boost::log::core::get()->set_filter(
    //boost::log::trivial::severity >= boost::log::trivial::warning);

    //The socket connecting between the client and the server.
    Socket *socket;
    //Serializer used for serializing and deserializing objects.
    Serializer   serializer;
    //Will handle parsing the user input.
    StringParser stringParser;
    Driver       *driver    = 0;
    Vehicle      *vehicle   = 0;
    Taxi         *taxi      = 0;
    Trip         *trip      = 0;
    bool         exitCalled = false;

    //Validate driver input.
    driver = stringParser.parseDriverInput(argv[3]);

    //If the driver input is invalid, exit the program.
//    if (!driver) {
//
//        exit(1);
//    }

    //Connect to server.
    socket = new Tcp(0, argv[1], atoi(argv[2]));
    socket->initialize();

    //Serializes the driver into a string.
    std::string serialDriver = serializer.serialize(driver);

    //Sends the string to the server
    //BOOST_LOG_TRIVIAL(info) << "Sending driver object to server";
    socket->sendData(serialDriver, socket->getSocketDescriptor());

    char buffer[1024];

    //Receives data from the server.
    socket->receiveData(buffer, sizeof(buffer), socket->getSocketDescriptor());
    //BOOST_LOG_TRIVIAL(info) << "Receiving serialized vehicle.";

    //Deserializes the data received from the server into a vehicle object.
    serializer.deserialize(buffer, sizeof(buffer), vehicle);
    //BOOST_LOG_TRIVIAL(info) << "Desirialized vehicle, vehicle id:"
    //                        << vehicle->getVehicleId();

    taxi         = new Taxi(driver, vehicle, Point(0, 0));
    serialDriver = "";
    //BOOST_LOG_TRIVIAL(info) << "Waiting for command.";

    //Take input from the server while it's not an exit command.
    while (!exitCalled) {

        char communicationBuffer[16384];

        socket->receiveData(communicationBuffer, sizeof(communicationBuffer),
                            socket->getSocketDescriptor());
        //BOOST_LOG_TRIVIAL(info) << "Received command.";

        //If received "exit", close the client.
        if (strcmp(communicationBuffer, "exit") == 0) {

            exitCalled = true;
        }

            //If received "go", move the taxi towards its destination.
        else if (strcmp(communicationBuffer, "go") == 0) {

            taxi->move();
            std::string serial = serializer.serialize(
                    &taxi->getCurrentPosition());
            socket->sendData(serial, socket->getSocketDescriptor());
//            BOOST_LOG_TRIVIAL(info) << "Driver " << driver->getDriverId()
//                                   << " moved to "
//                                 << taxi->getCurrentPosition();
        } else {

            if (trip != 0) {
                delete trip;
                trip = 0;
            }

            //Set the received trip from the server in the taxi.
            serializer.deserialize(communicationBuffer,
                                   sizeof(communicationBuffer), trip);
            taxi->setTrip(trip);
          //  BOOST_LOG_TRIVIAL(info) << "Received the trip, trip id:"
            //                        << trip->getRideId();

        }
    }

    //Close the client process.
    closeClient(taxi, driver, vehicle, socket);
}

void closeClient(Taxi *taxi, Driver *driver, Vehicle *vehicle, Socket *socket) {
    delete taxi;
    delete driver;
    delete vehicle;
    delete socket;
    exit(0);

}
