#include "Server.h"
#include <vector>

/* global values*/
std::string REPOSITORY_PATH = "C:\\backupsvr"; // name of the server main directory


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

std::string ServerInit::__filetostring(const char* filename) {
	std::ifstream in(filename);
	std::stringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

int ServerInit::__request_op_handle(int OP) {
	if (OP == OP_SAVE) {
		// save to fs
		return 1;


	} else if(OP == OP_RET){
		// return from fs
		return 1;


	} else if(OP == OP_DEL){
		// delete from fs
		return SUCCESS_FILE_FOUND_NOTIFICATION;


	}
	else if (OP == OP_ALL_LIST) {
		// return the name of the files of the user fs
		return SUCCESS_ALL_LIST_NOTIFICATION;

	} else {
		// error handle
		return GENERAL_ERR;
	}
}

void ServerInit::handlerequest(SOCKET clientsocket) {
	// receive the message from the client max len 1024.
	std::cout << "client connected!" << std::endl;
	char clientmsg[1024] = { 0 };
	recv(clientsocket, clientmsg, 1024, 0);
	std::cout << "client sent:" << std::endl;
	std::cout << clientmsg << std::endl;

	//req_client_header.user_id = clientmsg[0]
	//std::cout << "client message is: " << unsigned int(clientmsg[]) << std::endl;

	std::cout << "client message is: " << clientmsg << std::endl;


	//std::stringstream ss;
	//std::string a = clientmsg;
	//int len = a.length();


	request_header req_client_header;
	char* my_s_bytes = reinterpret_cast<char*>(&req_client_header);
	my_s_bytes[0] = (int)clientmsg[0];
	my_s_bytes[1] = (int)clientmsg[1];
	my_s_bytes[2] = (int)clientmsg[2];
	my_s_bytes[3] = (int)clientmsg[3];
	std::cout << "user_id: " << req_client_header.user_id << std::endl;
	my_s_bytes[4] = (int)clientmsg[4];
	std::cout << "version: " << req_client_header.version << std::endl;
	my_s_bytes[5] = (int)clientmsg[5];
	std::cout << "OP: " << req_client_header.op << std::endl;
	my_s_bytes[7] = (int)clientmsg[7];
	std::cout << "name_len: " << req_client_header.name_len << std::endl;
	for (int i = 8; i < sizeof(clientmsg); i++) {
		my_s_bytes[i] = (int)clientmsg[i];
	my_s_bytes[6] = (int)clientmsg[6];
	}
	std::cout << "file_name: " << req_client_header.filename << std::endl;


	Sleep(10000);
	//send(clientsocket, msg.c_str(), msg.length(), 0);
	std::cout << req_client_header.filename <<"client finish" << std::endl;
	closesocket(clientsocket); // closing the socket
}


ServerInit::~ServerInit() {
	WSACleanup();
}