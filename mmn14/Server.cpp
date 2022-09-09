#include "Server.h"
#include "MessageProtocol.h"


ServerInit::ServerInit() {

	// bind the PORT to the socket and listening on the socket PORT
	std::cout << "start the server..." << std::endl;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	bind(s, (struct sockaddr*)&sa, sizeof(sa));
	listen(s, SOMAXCONN);
	std::cout << "listening on port " << PORT << std::endl;
}

void ServerInit::__userConnect() {
	// accept() - blocking, waiting for client to connect the server.
	std::cout << "waiting for clients to connect.." << std::endl;
	this->clientsocket = accept(s, NULL, NULL);
	std::cout << "client connected!" << std::endl;
}

void ServerInit::__handlerequest(SOCKET clientsocket) {
	// receive the message from the client max len 1024.
	char clientmsg[1024] = { 0 };
	recv(clientsocket, clientmsg, 1024, 0); 
	std::cout << "client sent:" << std::endl;
	std::cout << clientmsg << std::endl;

	// the server will send echo to the client that the message have been recieved.
	send(clientsocket, "Hello from server!", 18, 0);

	Sleep(10000);

	closesocket(clientsocket); // closing the socket
}

void ServerInit::handleclient() {
	this->__userConnect();
	std::thread ct(__handlerequest, this->clientsocket);
	ct.detach();
}


ServerInit::~ServerInit() {
	WSACleanup();
}



int main() {
	ServerInit *server;
	server = new ServerInit();

	while (true) {
		server->handleclient();
	}


	return 0;
}