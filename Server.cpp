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

void check(){

    Driver *driver;
    std::cout<< "Server is on" << endl;

    Udp udp(1, 5555, "127.0.0.1");
    udp.initialize();

    char buffer[1024];
    udp.reciveData(buffer, 1024);
    std::cout<< buffer << endl;
    boost::iostreams::basic_array_source<char> device(buffer, 1024);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    boost::archive::binary_iarchive ia(s);

    ia >> driver;
    std:: cout << driver->getDriverId() << std::endl;

    Vehicle * vehicle = new StandardVehicle(0, 'H', 'G');
    char buffer2[1024];
    std::string serial_vehicle;

    boost::iostreams::back_insert_device<std::string> inserter(serial_vehicle);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s2(inserter);
    boost::archive::binary_oarchive oa(s2);
    oa << vehicle;
    s2.flush();

    std::cout << serial_vehicle << std::endl;

    udp.sendData(serial_vehicle);

}
int main(){


    check();
    return  0;

}