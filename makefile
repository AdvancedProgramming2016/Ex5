all: server.out client.out 

server.out: Server.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o

	 g++ -o server.out Server.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o -lboost_serialization -lpthread

client.out: Client.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o

	 g++ -o client.out Client.o VehicleFactory.o Point.o Vertex.o Graph.o Grid.o Bfs.o Driver.o Vehicle.o LuxuryVehicle.o StandardVehicle.o MainFlow.o Passenger.o Clock.o Taxi.o TaxiCenter.o Trip.o Menu.o StringParser.o Socket.o Tcp.o Serializer.o TripThread.o ClientThread.o -lboost_serialization -lpthread

Server.o: Server.cpp
	g++ -c Server.cpp

Client.o: Client.cpp
	g++ -c Client.cpp

ClientThread.o: src/ClientThread.cpp src/ClientThread.h
	g++ -c -std=c++0x src/ClientThread.cpp

TripThread.o: src/TripThread.cpp src/TripThread.h
	g++ -c -std=c++0x src/TripThread.cpp

MainFlow.o: src/MainFlow.cpp src/MainFlow.h
	g++ -c -std=c++0x src/MainFlow.cpp

Point.o: src/Point.cpp src/Point.h
	g++ -c -std=c++0x src/Point.cpp

VehicleFactory.o: src/VehicleFactory.cpp src/VehicleFactory.h
	g++ -c -std=c++0x src/VehicleFactory.cpp

Driver.o: src/Driver.cpp src/Driver.h
	g++ -c -std=c++0x src/Driver.cpp

Vehicle.o: src/Vehicle.cpp src/Vehicle.h
	g++ -c -std=c++0x src/Vehicle.cpp

LuxuryVehicle.o: src/LuxuryVehicle.cpp src/LuxuryVehicle.h
	g++ -c -std=c++0x src/LuxuryVehicle.cpp

StandardVehicle.o: src/StandardVehicle.cpp src/StandardVehicle.h
	g++ -c -std=c++0x src/StandardVehicle.cpp

Passenger.o: src/Passenger.cpp src/Passenger.h
	g++ -c -std=c++0x src/Passenger.cpp

Taxi.o: src/Taxi.cpp src/Taxi.h
	g++ -c -std=c++0x src/Taxi.cpp

TaxiCenter.o: src/TaxiCenter.cpp src/TaxiCenter.h
	g++ -c -std=c++0x src/TaxiCenter.cpp

Trip.o: src/Trip.cpp src/Trip.h
	g++ -c -std=c++0x src/Trip.cpp

Menu.o: src/Menu.cpp src/Menu.h
	g++ -c -std=c++0x src/Menu.cpp

StringParser.o: src/StringParser.cpp src/StringParser.h
	g++ -c -std=c++0x src/StringParser.cpp

Vertex.o: src/Vertex.cpp src/Vertex.h
	g++ -c -std=c++0x src/Vertex.cpp

Graph.o: src/Graph.cpp src/Graph.h
	g++ -c -std=c++0x src/Graph.cpp

Grid.o: src/Grid.cpp src/Grid.h
	g++ -c -std=c++0x src/Grid.cpp

Bfs.o: src/Bfs.cpp src/Bfs.h
	g++ -c -std=c++0x src/Bfs.cpp

Clock.o: src/Clock.cpp src/Clock.h
	g++ -c -std=c++0x src/Clock.cpp

Serializer.o: src/Serializer.cpp src/Serializer.h
	g++ -c -std=c++0x src/Serializer.cpp

Socket.o: sockets/Socket.h sockets/Socket.cpp
	g++ -c sockets/Socket.cpp

Tcp.o: sockets/Tcp.h sockets/Tcp.cpp sockets/Socket.h sockets/Socket.cpp
	g++ -c sockets/Tcp.cpp

clean:
	rm -f *.o a.out

unzip:
	unzip ex5.zip

