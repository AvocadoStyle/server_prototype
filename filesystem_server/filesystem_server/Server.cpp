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

void ServerInit::__message_handle_main(char* clientmsg, char* header_bytes_reference, char* payload_bytes_reference,
	request_header* req_client_header) {
	this->__message_handle_header(clientmsg, header_bytes_reference, req_client_header);

}
void ServerInit::__message_handle_header(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {
	this->__message_handle_userid(clientmsg, header_bytes_reference, req_client_header);
	this->__message_handle_version(clientmsg, header_bytes_reference, req_client_header);
	this->__message_handle_op(clientmsg, header_bytes_reference, req_client_header);
	this->__message_handle_name_len_and_file_name(clientmsg, header_bytes_reference, req_client_header);
}
void ServerInit::__message_handle_userid(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {
	for (int i = USER_ID_STARTBYTE_H__; i < USER_ID_BYTESIZE_H__; i++) {
		header_bytes_reference[i] = (int)clientmsg[i];
	}
	std::cout << "user_id: " << req_client_header->user_id << std::endl;
}
void ServerInit::__message_handle_version(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {
	header_bytes_reference[VERSION_STARTBYTE_H__] = (int)clientmsg[VERSION_STARTBYTE_H__];
	std::cout << "version: " << req_client_header->version<< std::endl;
}
void ServerInit::__message_handle_op(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {
	header_bytes_reference[OP_STARTBYTE_H__] = (int)clientmsg[OP_STARTBYTE_H__];
	std::cout << "op: " << req_client_header->op << std::endl;
}
void ServerInit::__message_handle_name_len_and_file_name(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {
	for (int i = NAME_LEN_STARTBYTE_H__; i < (NAME_LEN_STARTBYTE_H__+NAME_LEN_BYTESIZE_H__); i++) {
		header_bytes_reference[i] = (int)clientmsg[i];
	}
	std::cout << "name_len: " << req_client_header->name_len << std::endl;
}

void ServerInit::handlerequest(SOCKET clientsocket) {
	// receive the message from the client max len 1024.
	std::cout << "client connected!" << std::endl;
	char clientmsg[1024] = { 0 };
	recv(clientsocket, clientmsg, 1024, 0);
	std::cout << "client sent:" << std::endl;
	std::cout << "client message is: " << clientmsg << std::endl;

	request_header req_client_header;
	request_payload req_client_payload;
	char* header_bytes_reference = reinterpret_cast<char*>(&req_client_header);
	char* payload_bytes_reference = reinterpret_cast<char*>(&req_client_payload);

	this->__message_handle_main(clientmsg, header_bytes_reference, payload_bytes_reference, &req_client_header);

	//Sleep(10000);
	//send(clientsocket, msg.c_str(), msg.length(), 0);
	std::cout <<"client finish" << std::endl;
	closesocket(clientsocket); // closing the socket
}


ServerInit::~ServerInit() {
	WSACleanup();
}