all: server.out client.out 

server.out: Server.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o ThreadPool.o Task.o

	 g++ -o server.out Server.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o ThreadPool.o Task.o -lboost_serialization -lpthread

client.out: Client.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o ThreadPool.o Task.o

	 g++ -o client.out Client.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o ThreadPool.o Task.o -lboost_serialization -lpthread

Server.o: Server.cpp
	g++ -c Server.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

ClientThread.o: src/threads/ClientThread.cpp src/threads/ClientThread.h
	g++ -c -std=c++0x src/threads/ClientThread.cpp

TripThread.o: src/threads/TripThread.cpp src/threads/TripThread.h
	g++ -c -std=c++0x src/threads/TripThread.cpp

ThreadPool.o: src/threads/ThreadPool.cpp src/threads/ThreadPool.h
	g++ -c -std=c++0x src/threads/ThreadPool.cpp

Task.o: src/threads/Task.cpp src/threads/Task.h
	g++ -c -std=c++0x src/threads/Task.cpp

ErrorHandler.o: src/validation/ErrorHandler.cpp src/validation/ErrorHandler.h
	g++ -c -std=c++0x src/validation/ErrorHandler.cpp

MainFlow.o: src/control/MainFlow.cpp src/control/MainFlow.h
	g++ -c -std=c++0x src/control/MainFlow.cpp

Point.o: src/graphs/Point.cpp src/graphs/Point.h
	g++ -c -std=c++0x ssrc/graphs/Point.cpp

VehicleFactory.o: src/taxi/VehicleFactory.cpp src/taxi/VehicleFactory.h
	g++ -c -std=c++0x src/taxi/VehicleFactory.cpp

Driver.o: src/taxi/Driver.cpp src/taxi/Driver.h
	g++ -c -std=c++0x src/taxi/Driver.cpp

Vehicle.o: src/taxi/Vehicle.cpp src/taxi/Vehicle.h
	g++ -c -std=c++0x src/taxi/Vehicle.cpp

LuxuryVehicle.o: src/taxi/LuxuryVehicle.cpp src/taxi/LuxuryVehicle.h
	g++ -c -std=c++0x src/taxi/LuxuryVehicle.cpp

StandardVehicle.o: src/taxi/StandardVehicle.cpp src/taxi/StandardVehicle.h
	g++ -c -std=c++0x src/taxi/StandardVehicle.cpp

Passenger.o: src/taxi/Passenger.cpp src/taxi/Passenger.h
	g++ -c -std=c++0x src/taxi/Passenger.cpp

Taxi.o: src/taxi/Taxi.cpp src/taxi/Taxi.h
	g++ -c -std=c++0x src/taxi/Taxi.cpp

TaxiCenter.o: src/control/TaxiCenter.cpp src/control/TaxiCenter.h
	g++ -c -std=c++0x src/control/TaxiCenter.cpp

Trip.o: src/taxi/Trip.cpp src/taxi/Trip.h
	g++ -c -std=c++0x src/taxi/Trip.cpp

Menu.o: src/control/Menu.cpp src/control/Menu.h
	g++ -c -std=c++0x src/control/Menu.cpp

StringParser.o: src/parsers/StringParser.cpp src/parsers/StringParser.h
	g++ -c -std=c++0x src/parsers/StringParser.cpp

Vertex.o: src/graphs/Vertex.cpp src/graphs/Vertex.h
	g++ -c -std=c++0x src/graphs/Vertex.cpp

Graph.o: src/graphs/Graph.cpp src/graphs/Graph.h
	g++ -c -std=c++0x src/graphs/Graph.cpp

Grid.o: src/graphs/Grid.cpp src/graphs/Grid.h
	g++ -c -std=c++0x src/graphs/Grid.cpp

Bfs.o: src/algorithms/Bfs.cpp src/algorithms/Bfs.h
	g++ -c -std=c++0x src/algorithms/Bfs.cpp

Clock.o: src/control/Clock.cpp src/control/Clock.h
	g++ -c -std=c++0x src/control/Clock.cpp

Serializer.o: src/serializers/Serializer.cpp src/serializers/Serializer.h
	g++ -c -std=c++0x src/serializers/Serializer.cpp

Socket.o: src/sockets/Socket.h src/sockets/Socket.cpp
	g++ -c src/sockets/Socket.cpp

Tcp.o: src/sockets/Tcp.h sockets/Tcp.cpp src/sockets/Socket.h src/sockets/Socket.cpp
	g++ -c src/sockets/Tcp.cpp

clean:
	rm -f *.o a.out

unzip:
	unzip ex6.zip

