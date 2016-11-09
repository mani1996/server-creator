a.out : Server.cpp GreetServer.cpp
	g++ -std=c++11 -pthread Server.cpp GreetServer.cpp
