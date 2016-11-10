a.out : Server.cpp Server.h GreetServer.cpp GreetServer.h 
	g++ -std=c++11 -pthread Server.cpp GreetServer.cpp
