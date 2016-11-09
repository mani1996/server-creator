#ifndef SERVERINCLUDES
#define SERVERINCLUDES

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <thread>
#include <vector>

class Server{
protected:
	std::string _port;
	addrinfo* _addrParams;
	int _socketFD;
	int _backlog;
	std::vector<std::thread> threadsDispatched;

	void printError();
	virtual void communicate(int clientFD, sockaddr_storage clientAddr, socklen_t acceptSize);
	void findAndBind(addrinfo* addrNode);
	void init();	

public:
	Server(std::string port, int backlog);
	~Server();
	void listenAndAccept();
	bool isSet() const;
};

#endif