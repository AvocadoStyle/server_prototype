#include "Server.h"
#include "MessageProtocol.h"





ServerInit::ServerInit() {

	// bind the PORT to the socket and listening on the socket PORT
	std::cout << "start the server..." << std::endl;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	bind(serversocket, (struct sockaddr*)&sa, sizeof(sa));
	listen(serversocket, SOMAXCONN);
	std::cout << "listening on port " << PORT << std::endl;
}

void ServerInit::_userConnect() {
	// accept() - blocking, waiting for client to connect the server.
	std::cout << "waiting for clients to connect.." << std::endl;
	//std::cout << "client connected!" << std::endl;
}

std::string ServerInit::__filetostring(const char* filename) {
	std::ifstream in(filename);
	std::stringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

void ServerInit::_handlerequest(SOCKET clientsocket) {
	// receive the message from the client max len 1024.
	std::cout << "client connected!" << std::endl;

	char clientmsg[1024] = { 0 };
	recv(clientsocket, clientmsg, 1024, 0);
	std::cout << "client sent:" << std::endl;
	std::cout << clientmsg << std::endl;

	std::string recv_msg = clientmsg;
	size_t spos = recv_msg.find("GET /");
	size_t epos = recv_msg.find("HTTP", spos + 5);
	std::string reqfile = recv_msg.substr(spos + 5, epos - 6);
	std::cout << "Requested file: " << reqfile << "|" << std::endl;

	//the server will send echo to the client that the message have been recieved
	std::string msg;
	msg = "HTTP/1.1 200 OK\n\n";

	if (reqfile.empty()) {
		//index.html ->>>> msg+= filetostring("index.html") >>>> make index.html to string.
		msg += __filetostring("index.html");
	}
	else {
		//load reqfile ->>>> msg+= filetostring(reqfile.c_str()); >>>> file requested if inside the server
		msg += __filetostring(reqfile.c_str());
	}




	send(clientsocket, msg.c_str(), msg.length(), 0);

	closesocket(clientsocket); // closing the socket
}

void ServerInit::handleclient() {
	this->_userConnect();
	SOCKET clientsocket = accept(serversocket, NULL, NULL);
	std::thread ct(_handlerequest, clientsocket);
	ct.detach();
}


ServerInit::~ServerInit() {
	WSACleanup();
}



int main() {
	ServerInit* server;
	server = new ServerInit();

	while (true) {
		server->handleclient();
	}


	return 0;
}
