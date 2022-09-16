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
	request_header* req_client_header, request_payload* req_client_payload) {
	this->__message_handle_header(clientmsg, header_bytes_reference, req_client_header);
	this->__message_handle_payload(clientmsg, payload_bytes_reference, header_bytes_reference,
		req_client_payload, req_client_header);
}
void ServerInit::__message_handle_header(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header) {

	this->__message_handle_utility_header(clientmsg, header_bytes_reference, req_client_header, USER_ID_STARTBYTE_H__,
		USER_ID_BYTESIZE_H__);
	this->__message_handle_utility_header(clientmsg, header_bytes_reference, req_client_header, VERSION_STARTBYTE_H__,
		VERSION_BYTESIZE_H__);
	this->__message_handle_utility_header(clientmsg, header_bytes_reference, req_client_header, OP_STARTBYTE_H__,
		OP_BYTESIZE_H__);
	this->__message_handle_utility_header(clientmsg, header_bytes_reference, req_client_header, NAME_LEN_STARTBYTE_H__,
		NAME_LEN_BYTESIZE_H__);
	int file_name_length = int(req_client_header->name_len);
	this->__message_handle_utility_header(clientmsg, header_bytes_reference, req_client_header, FILE_NAME_STARTBYTE_H__,
		file_name_length);
	req_client_header->filename[file_name_length] = '\0';
	std::cout << "user_id: " << int(req_client_header->user_id) << std::endl;
	std::cout << "version: " << int(req_client_header->version) << std::endl;
	std::cout << "op: " << int(req_client_header->op) << std::endl;
	std::cout << "name_len: " << int(req_client_header->name_len) << std::endl;
	std::cout << "file_name: " << (req_client_header->filename) << std::endl;
}

void ServerInit::__message_handle_payload(char* clientmsg, char* payload_bytes_reference, char* header_bytes_reference,
	request_payload* req_client_payload, request_header* req_client_header) {
	char* new_client_msg_without_prev = clientmsg + (int(req_client_header->name_len) + PREV_BYTE_VALUE_HP__);
	this->__message_handle_utility_payload(new_client_msg_without_prev, payload_bytes_reference, req_client_payload, SIZE_PAYLOAD_STARTBYTE_P__,
		SIZE_PAYLOAD_BYTESIZE_P__);
	int payload_length = int(req_client_payload->size);
	this->__message_handle_utility_payload(new_client_msg_without_prev, payload_bytes_reference, req_client_payload, PAYLOAD_PAYLOAD_STARTBYTE_P__,
		payload_length);
	req_client_payload->payload[payload_length] = '\0';
	std::cout << "size: " << int(req_client_payload->size) << std::endl;
	std::cout << "payload: " << (req_client_payload->payload) << std::endl;
}

void ServerInit::__message_handle_utility_header(char* clientmsg, char* header_bytes_reference,
	request_header* req_client_header, int startbyte, int bytesize) {
	for (int i = startbyte; i < startbyte + bytesize; i++) {
		header_bytes_reference[i] = (int)clientmsg[i];
	}
}
void ServerInit::__message_handle_utility_payload(char* clientmsg, char* payload_bytes_reference,
	request_payload* req_client_payload, int startbyte, int bytesize) {
	for (int i = startbyte; i < startbyte + bytesize; i++) {
		payload_bytes_reference[i] = (int)clientmsg[i];
	}
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

	this->__message_handle_main(clientmsg, header_bytes_reference, payload_bytes_reference, &req_client_header,
		&req_client_payload);

	//Sleep(10000);
	//send(clientsocket, msg.c_str(), msg.length(), 0);
	std::cout <<"client finish" << std::endl;
	closesocket(clientsocket); // closing the socket
}


ServerInit::~ServerInit() {
	WSACleanup();
}