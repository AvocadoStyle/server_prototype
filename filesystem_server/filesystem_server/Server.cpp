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












//std::string ServerInit::__filetostring(const char* filename) {
//	std::ifstream in(filename);
//	std::stringstream ss;
//	ss << in.rdbuf();
//	return ss.str();
//}
















char* ServerInit::__save_handle_op(FileUtilities* fu, request_header* req_client_header, request_payload* req_client_payload) {
	std::string filename_str = fu->__char_to_string(req_client_header->filename);
	fu->file_write(filename_str, req_client_header->user_id, req_client_payload->payload);
	fu->set_list_info_content(req_client_header->user_id, filename_str);
	char* res = (char*)malloc(4);
	std::string res2 = fu->__char_to_string(res);
	res2 = "ok!";
	res = fu->__string_to_char(res2);
	return res;
}
char* ServerInit::__return_handle_op(FileUtilities* fu, request_header* req_client_header, request_payload* req_client_payload) {
	std::string filename_str = fu->__char_to_string(req_client_header->filename);
	std::string filename_str_path = REPOSITORY_PATH + "\\" + std::to_string(int(req_client_header->user_id)) + "\\" + filename_str;
	char* response_to_client_header_and_payload;
	char version = 1; //default
	char* filename_ch = fu->__string_to_char(filename_str);
	if (fu->is_file_exists(filename_str_path)) {
		std::string content = fu->file_read(filename_str, req_client_header->user_id);
		int status = SUCCESS_FILE_FOUND_NOTIFICATION;
		int size = int(content.length());
		int name_len = int(filename_str.length());
		response_to_client_header_and_payload = (char*)malloc(PREV_BYTE_VALUE_HP__ + name_len + size);
		char* content_payload = fu->__string_to_char(content); // payload
		response_to_client_header_and_payload[2] = '\0';
		response_to_client_header_and_payload[4] = '\0';
		response_to_client_header_and_payload[0] = version;
		response_to_client_header_and_payload[1] = status;
		response_to_client_header_and_payload[3] = name_len;
		for (int i = OP_STARTBYTE_H__; i < name_len + OP_STARTBYTE_H__; i++) {
			response_to_client_header_and_payload[i] = filename_ch[i];
		}
		for (int i = name_len + OP_STARTBYTE_H__; i < size + name_len + OP_STARTBYTE_H__; i++) {
			response_to_client_header_and_payload[i] = content_payload[i];
			if ((i + 1) == size + name_len + OP_STARTBYTE_H__) {
				response_to_client_header_and_payload[i + 1] = '\0';
			}
		}
	}else {
		int status = ERR_FILE_NOT_EXISTS;
		int name_len = int(filename_str.length());
		response_to_client_header_and_payload = (char*)malloc(OP_STARTBYTE_H__ + name_len);
		response_to_client_header_and_payload[2] = '\0';
		response_to_client_header_and_payload[4] = '\0';
		response_to_client_header_and_payload[0] = version;
		response_to_client_header_and_payload[1] = status;
		response_to_client_header_and_payload[3] = name_len;
		for (int i = OP_STARTBYTE_H__; i < name_len + OP_STARTBYTE_H__; i++) {
			response_to_client_header_and_payload[i] = filename_ch[i];
			if ((i+1) == name_len + OP_STARTBYTE_H__) {
				response_to_client_header_and_payload[i + 1] = '\0';
			}
		}
	}
	return response_to_client_header_and_payload;
}
char* ServerInit::__delete_handle_op(FileUtilities* fu, request_header* req_client_header, request_payload* req_client_payload) {
	char* err = fu->__string_to_char("error!");
	return err;
}
char* ServerInit::__alllist_handle_op(FileUtilities* fu, request_header* req_client_header, request_payload* req_client_payload) {
	char* err = fu->__string_to_char("error!");
	return err;
}





char* ServerInit::_request_op_handle(request_header* req_client_header, request_payload* req_client_payload) {
	int OP = req_client_header->op;
	FileUtilities* fu = new FileUtilities();
	if (OP == OP_SAVE) {
		return this->__save_handle_op(fu, req_client_header, req_client_payload);
	} else if(OP == OP_RET){
		//return the file with the content 
		return this->__return_handle_op(fu, req_client_header, req_client_payload);
	} else if(OP == OP_DEL){
		// delete the file and delete the file from the list of files too
		return this->__delete_handle_op(fu, req_client_header, req_client_payload);
	}
	else if (OP == OP_ALL_LIST) {
		// read the file of all of the files inside and return the string
		return this->__alllist_handle_op(fu, req_client_header, req_client_payload);
;
	} else {
		// error
		char* err = fu->__string_to_char("error!");
		return err;
	}
}









/*
* handles the message and getting it inside the struct for more convinient way to use the data.
*/
void ServerInit::_message_handle_main(char* clientmsg, char* header_bytes_reference, char* payload_bytes_reference,
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
	//std::cout << "client message is: " << clientmsg << std::endl;

	/* the Datastructure thats holding the message protocol */
	request_header req_client_header;
	request_payload req_client_payload;
	char* header_bytes_reference = reinterpret_cast<char*>(&req_client_header);
	char* payload_bytes_reference = reinterpret_cast<char*>(&req_client_payload);
	/* handle the message */
	this->_message_handle_main(clientmsg, header_bytes_reference, payload_bytes_reference, &req_client_header,
		&req_client_payload);
	/* handle request */
	char* response_to_client_header_and_payload;
	std::cout << "response to client: " << std::endl;
	response_to_client_header_and_payload = this->_request_op_handle(&req_client_header,
		&req_client_payload);

	FileUtilities* fu = new FileUtilities();
	std::string res = fu->__char_to_string(response_to_client_header_and_payload);
	std::cout << "response length is: " << sizeof(response_to_client_header_and_payload) << std::endl;
	std::cout << "response message is: " << response_to_client_header_and_payload << std::endl;
	//Sleep(10000);
	// 
	send(clientsocket, response_to_client_header_and_payload, sizeof(response_to_client_header_and_payload), 0);
	std::cout <<"client finish" << std::endl;
	closesocket(clientsocket); // closing the socket
}


ServerInit::~ServerInit() {
	WSACleanup();
}