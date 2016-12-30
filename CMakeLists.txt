cmake_minimum_required(VERSION 3.6)
project(Ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES src/VehicleFactory.cpp src/VehicleFactory.h src/Point.cpp src/Point.h src/Vertex.cpp src/Vertex.h
        src/Graph.cpp src/Graph.h src/Grid.cpp src/Grid.h src/Bfs.cpp src/Bfs.h src/Driver.cpp
        src/Driver.h src/Vehicle.cpp src/Vehicle.h src/LuxuryVehicle.cpp src/LuxuryVehicle.h
        src/StandardVehicle.cpp src/StandardVehicle.h src/IObserver.h src/ISubject.h src/MainFlow.cpp
        src/MainFlow.h src/Passenger.cpp src/Passenger.h src/Clock.cpp src/Clock.h
        src/Taxi.cpp src/Taxi.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h src/Menu.cpp src/Menu.h
        src/BaseParser.h src/StringParser.cpp src/StringParser.h sockets/Socket.cpp sockets/Socket.h sockets/Udp.cpp sockets/Udp.h src/Serializer.cpp src/Serializer.h main.cpp)

add_executable(client Client.cpp ${SOURCE_FILES})
add_executable(server Server.cpp ${SOURCE_FILES})
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server ${Boost_LIBRARIES})