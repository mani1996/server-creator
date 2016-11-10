#include "GreetServer.h"

void GreetServer::communicate(int clientFD, sockaddr_storage clientAddr, socklen_t acceptSize){
	int msgLength,sendStatus;
	char *buf = new char[1024];

	while(true){
		if((msgLength = recv(clientFD, buf, 1024, 0))==-1){
			printError("recv function call");
			close(clientFD);
			return ;
		}

		if(msgLength==0){
			printf("Connection closed by client\n");
			close(clientFD);
			return ;
		}

		buf[msgLength] = '\0';

		std::string greeting = "Hello, " + std::string(buf);

		if((sendStatus = send(clientFD, greeting.c_str(), greeting.length(), 0)) == -1){
			printError("send function call");
			close(clientFD);
			return ;
		}
	}
	
	printf("Sending out greeting..\n");
	close(clientFD);
}

int main(){
	Server* greeter = new GreetServer("8132");
	greeter->listenAndAccept();
}