#include "Server.h"
#include <iostream>

Server::Server(std::string port, int backlog = 10){
	_port = port;
	_addrParams = NULL;
	_backlog = backlog;
	init();
}


Server::~Server(){
	for(int i=0; i<threadsDispatched.size(); i++){
		threadsDispatched[i].join();
	}
}


void Server::printError(){
	perror("Error");
}


/* 
	Traverse the list of addresses and bind with the first address 
	that allows socket creation + binding
*/
void Server::findAndBind(addrinfo* addrNode){
	int yes = 1;

	while(addrNode!=NULL){
		if((_socketFD = socket(addrNode->ai_family, addrNode->ai_socktype, addrNode->ai_protocol))
				== -1){
			printError();
			addrNode = addrNode->ai_next;
			continue;
		}

		if(setsockopt(_socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
			printError();
			return ;
		}

		if(bind(_socketFD, addrNode->ai_addr, addrNode->ai_addrlen) == -1){
			printError();
			close(_socketFD);
			addrNode = addrNode->ai_next;
			continue;
		}

		_addrParams = addrNode;
		printf("Server started at port %s\n", _port.c_str());
		return ; 
	}

	return ;
}


void Server::listenAndAccept(){
	if(!isSet()){
		printError();
		return ;
	}

	if(listen(_socketFD, _backlog) == -1){
		printError();
		return ;
	}

	sockaddr_storage clientAddr;
	socklen_t acceptSize;
	int clientFD;

	while(true){
		acceptSize = sizeof(sockaddr_storage);
		clientFD = accept(_socketFD, (sockaddr*) &clientAddr, &acceptSize);

		if(clientFD != -1){
			printf("New client - FD : %d\n", clientFD);
			//communicate(clientFD, clientAddr, acceptSize);
			std::thread t1(&Server::communicate, this, clientFD, clientAddr, acceptSize);
			threadsDispatched.push_back(std::move(t1));
		}
		else{
			printError();
		}	
	}	
}


void Server::init(){
	int status;
	addrinfo hints, *servInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(NULL, _port.c_str(), &hints, &servInfo))!=0){
		printError();
		return ;
	}

	findAndBind(servInfo);
	freeaddrinfo(servInfo);
}


bool Server::isSet() const{
	return _addrParams!=NULL;
}