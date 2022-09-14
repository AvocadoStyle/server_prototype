#include "ServerController.h"
/*
* initialize the ServerInit 
*/
ServerInit* server = new ServerInit();

/*
* client handle request with threads, it will receive the client request and handle it.
* used as initializer.
*/
void handle_request(SOCKET clientsocket) {
	server->handlerequest(clientsocket);
}

int main() {
	while (true) {
		std::cout << "waiting for clients to connect.." << std::endl;
		std::thread client_thread(handle_request, accept(server->serversocket, NULL, NULL));
		client_thread.detach();
	}
}