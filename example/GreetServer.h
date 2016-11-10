#ifndef GREETSERVERINCLUDES
#define GREETSERVERINCLUDES
#include "../src/Server.h"

class GreetServer : public Server{
protected:
	void communicate(int clientFD, sockaddr_storage clientAddr, socklen_t acceptSize);
public:
	GreetServer(std::string port, int backlog = 10):Server(port,backlog){}
};
#endif

