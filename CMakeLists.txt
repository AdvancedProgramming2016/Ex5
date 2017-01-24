cmake_minimum_required(VERSION 3.6)
project(Ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system log)
include_directories(${Boost_INCLUDE_DIR})
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(SOURCE_FILES src/taxi/VehicleFactory.cpp src/taxi/VehicleFactory.h src/graphs/Point.cpp src/graphs/Point.h src/graphs/Vertex.cpp src/graphs/Vertex.h
        src/graphs/Graph.cpp src/graphs/Graph.h src/graphs/Grid.cpp src/graphs/Grid.h src/algorithms/Bfs.cpp src/algorithms/Bfs.h src/taxi/Driver.cpp
        src/taxi/Driver.h src/taxi/Vehicle.cpp src/taxi/Vehicle.h src/taxi/LuxuryVehicle.cpp src/taxi/LuxuryVehicle.h
        src/taxi/StandardVehicle.cpp src/taxi/StandardVehicle.h src/observers/IObserver.h src/observers/ISubject.h src/control/MainFlow.cpp
        src/validation/ErrorHandler.cpp src/validation/ErrorHandler.h
        src/control/MainFlow.h src/taxi/Passenger.cpp src/taxi/Passenger.h src/control/Clock.cpp src/control/Clock.h
        src/taxi/Taxi.cpp src/taxi/Taxi.h src/control/TaxiCenter.cpp src/control/TaxiCenter.h src/taxi/Trip.cpp src/taxi/Trip.h src/control/Menu.cpp src/control/Menu.h
        src/threads/TripThread.cpp src/threads/TripThread.h src/parsers/BaseParser.h src/parsers/StringParser.cpp src/parsers/StringParser.h src/sockets/Socket.cpp
        src/sockets/Socket.h src/sockets/Udp.cpp src/sockets/Udp.h src/serializers/Serializer.cpp src/serializers/Serializer.h src/sockets/Tcp.cpp src/sockets/Tcp.h
        src/threads/ClientThread.cpp src/threads/ClientThread.h src/threads/Task.cpp src/threads/Task.h src/threads/ThreadPool.cpp src/threads/ThreadPool.h
        )

add_executable(client Client.cpp ${SOURCE_FILES})
add_executable(server Server.cpp ${SOURCE_FILES})
target_link_libraries(client pthread ${Boost_LIBRARIES})
target_link_libraries(server pthread ${Boost_LIBRARIES})