#include "Menu.h"
#include <cstdlib>
#include "src/sockets/Udp.h"
#include "Driver.h"

#include <iostream>
#include <unistd.h>
#include <boost/iostreams/device/array.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "src/Driver.h"
#include "sockets/Udp.h"
#include "src/StandardVehicle.h"

Menu::Menu(Socket &socket) {

    // Open server side socket on port 5555
    this->socket(1, 5555);
    this->socket.initialize();

}

Socket Menu::getSocket() {

    return this->socket;

}

MainFlow *Menu::getMainFlow() {

    return this->mainFlow;

}

int Menu::initializeGame() {

    Point location(0, 0);

    //Create Grid with obstacles.
    this->getMainFlow()->createMap(
            this->stringParser.parseGridInput());
    this->getMainFlow()->createTaxiCenter(&location);
}

void Menu::sendToSocket(Vehicle) {

    // TODO: Didn't understand what kind of vehicle we need to send back
    Vehicle *vehicle = new StandardVehicle(0, 'H', 'G');
    char buffer2[1024];
    std::string serial_vehicle;

    // Serialize vehicle
    boost::iostreams::back_insert_device <std::string> inserter(serial_vehicle);
    boost::iostreams::stream <boost::iostreams::back_insert_device<std::string>> s2(
            inserter);
    boost::archive::binary_oarchive oa(s2);

    oa << vehicle;
    s2.flush();
    this->getSocket().sendData(serial_vehicle);

}

Driver Menu::listenToSocket() {

    char buffer[1024];
    this->getSocket.reciveData(buffer, 1024);

    // Deserialize driver input from client side
    boost::iostreams::basic_array_source<char> device(buffer,
                                                      1024);
    boost::iostreams::stream <boost::iostreams::basic_array_source<char>> s(
            device);
    boost::archive::binary_iarchive ia(s);

    ia >> driver;
    return driver;

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

int Menu::runMenu() {

    int userOption = 0;

    while (userOption <= 9) {

        std::cin >> userOption;

        switch (userOption) {

            // Create driver
            case 1:
                int i = 0;
                int numOfDrivers = 0;

                // Receive from user num of drivers to create
                std::cin >> numOfDrivers;

                Driver driver;

                // Receive driver objects from client
                for (i = 0; i < numOfDrivers; i++) {

                    driver = this->listenToSocket();

                }

                // Create trip
            case 2:
                this->getMainFlow()->createTrip(
                        this->stringParser.parseTripInput());
                break;

                // Create vehicle
            case 3:
                this->getMainFlow()->createVehicle(
                        this->stringParser.parseVehicleInput());
                break;

                // Request for driver location
            case 4:
                this->getMainFlow()->getTaxiCenter()->requestDriverLocation(
                        this->stringParser.parseDriverLocation());
                break;

                /*
                // Start Driving
            case 6:
                this->getMainFlow()->startDriving();
                break;
                */
                //Exit system
            case 7:
                this->getMainFlow()->exitSystem();

                // Advance one step
            case 9:

                // Check that all the trips that need to start are attached
                // to a driver
                this->getMainFlow()->startDriving();

                // Move all the taxis one step
                this->getMainFlow()->getTaxiCenter()->moveOneStep();

                // Invalid input
            default:
                exit(1);

        }

    }

}

#pragma clang diagnostic pop
