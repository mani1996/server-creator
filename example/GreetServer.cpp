#include "GreetServer.h"

void GreetServer::addClient(int clientFD, sockaddr_storage clientAddr, socklen_t acceptSize){
	liveSockets.insert(clientFD);
	FD_SET(clientFD, &_masterSet);
}


void GreetServer::communicate(){
	int msgLength,sendStatus,selectStatus,currentSocket;
	char *buf = new char[1024];

	/*
		This is an infinite loop which keeps polling for data sent by clients
		using select(). If data is received from client, greeting is sent back
	*/

	while(true){
		if(!liveSockets.empty()){
			_readSet = _masterSet;
			selectStatus = select(1024, &_readSet, NULL, NULL, &pollWaitingTime); // nearly non-blocking stmt

			if(selectStatus == -1){
				printError("select function call");
			}
			else if(selectStatus > 0){
				std::set<int>::iterator sockIter = liveSockets.begin();

				while(sockIter != liveSockets.end()){
					currentSocket = *(sockIter);

					if(FD_ISSET(currentSocket, &_readSet)){
						msgLength = recv(currentSocket, buf, 1024, 0);

						if(msgLength == -1){
							printError("recv function call");
							delClient(*(sockIter++));
						}
						else if(msgLength == 0){
							printf("Connection closed by client\n");
							delClient(*(sockIter++));
						}
						else{
							buf[msgLength] = '\0';
							std::string greeting = "Hello, " + std::string(buf);
							sendStatus = send(currentSocket, greeting.c_str(), greeting.length(), 0);
							if(sendStatus == -1){
								printError("send function call");
								delClient(*(sockIter++));
							}
							else{
								printf("Sending out greeting..\n");
								sockIter++;
							}
						}
					}
					else{
						sockIter++;
					}

				}
			}

		}
	}

	return ;
}

int main(){
	Server* greeter = new GreetServer("8132");
	greeter->listenAndAccept();
}