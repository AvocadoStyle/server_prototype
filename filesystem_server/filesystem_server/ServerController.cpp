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

void whatVersion() {
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
}

int main() {
	//whatVersion();
	//while (true) {
	//	std::cout << "waiting for clients to connect.." << std::endl;
	//	std::thread client_thread(handle_request, accept(server->serversocket, NULL, NULL));
	//	client_thread.detach();
	//}
}