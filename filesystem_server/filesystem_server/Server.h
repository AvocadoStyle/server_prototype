#ifndef __SERVER_H__
#define __SERVER_H__

/*multithread includes*/
#include <thread>

/*server includes*/
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

/*std libs*/
#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdint.h>

/*my libs*/
#include "MessageProtocol.h"

/*server dependencies*/
#define PORT									8085

/*my defines*/
/*BYTE SIZE*/
#define USER_ID_BYTESIZE_H__					4
#define VERSION_BYTESIZE_H__					1
#define OP_BYTESIZE_H__							1
#define NAME_LEN_BYTESIZE_H__					2
#define SIZE_PAYLOAD_BYTESIZE_P__				4
/*start BYTE*/
#define USER_ID_STARTBYTE_H__					0
#define VERSION_STARTBYTE_H__					4
#define OP_STARTBYTE_H__						5
#define NAME_LEN_STARTBYTE_H__					6
#define FILE_NAME_STARTBYTE_H__					8
#define PREV_BYTE_VALUE_HP__					9 //or 9
#define SIZE_PAYLOAD_STARTBYTE_P__				0 
#define PAYLOAD_PAYLOAD_STARTBYTE_P__			4 
/*requests*/
#define OP_SAVE									100
#define OP_RET									200
#define OP_DEL									201
#define OP_ALL_LIST								202
/*response*/
#define SUCCESS_FILE_FOUND_NOTIFICATION			210
#define SUCCESS_ALL_LIST_NOTIFICATION			211
#define ERR_FILE_NOT_EXISTS						1001
#define ERR_NO_FILES_FOR_CLIENT					1002
#define GENERAL_ERR								1003

/*global values*/
extern std::string REPOSITORY_PATH;


class ServerInit {
public:
	SOCKET clientsocket;
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sa = { 0 };

	ServerInit();
	~ServerInit();

	void handlerequest(SOCKET clientsocket);

private:
	/* client message handler */
	void __message_handle_main(char* clientmsg, char* header_bytes_reference, char* payload_bytes_reference,
		request_header* req_client_header, request_payload* req_client_payload);
	// for header and payload handlers
	void __message_handle_header(char* clientmsg, char* header_bytes_reference,
		request_header* req_client_header);
	void __message_handle_payload(char* clientmsg, char* payload_bytes_reference, char* header_bytes_reference,
		request_payload* req_client_payload, request_header* req_client_header);
	//utility that build the struct datatype for header and payload
	void __message_handle_utility_header(char* clientmsg, char* header_bytes_reference,
		request_header* req_client_header, int startbyte, int bytesize);
	void __message_handle_utility_payload(char* clientmsg, char* payload_bytes_reference,
		request_payload* req_client_payload, int startbyte, int bytesize);

	/*request handler*/
	int __request_op_handle(int operation);

	/*helper functions*/
	std::string __filetostring(const char* filename);




};


#endif
