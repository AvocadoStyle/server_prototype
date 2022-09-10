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
	//std::cout << "client connected!" << std::endl;
}

void ServerInit::__handlerequest(SOCKET clientsocket) {
	// receive the message from the client max len 1024.
	std::cout << "client connected!" << std::endl;

	char clientmsg[1024] = { 0 };
	recv(clientsocket, clientmsg, 1024, 0); 
	std::cout << "client sent:" << std::endl;
	std::cout << clientmsg << std::endl;
	std::cout << "debug1" << std::endl;
	// the server will send echo to the client that the message have been recieved.
	std::string msg;
	std::string html_msg;
	std::string plaintext_msg;
	msg = "HTTP/1.1 200 OK\n\n";
	html_msg = msg + "<html><body>Kaki!<h1></h1></body></html>";
	plaintext_msg = msg + "Kaki Gadol!";
	send(clientsocket, plaintext_msg.c_str(), plaintext_msg.length(), 0);
	std::cout << "debug2" << std::endl;
	Sleep(10000);

	closesocket(clientsocket); // closing the socket
}

void ServerInit::handleclient() {
	this->__userConnect();
	SOCKET clientsocket = accept(s, NULL, NULL);
	std::thread ct(__handlerequest, clientsocket);
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