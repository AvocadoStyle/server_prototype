#ifndef __SERVER_H__
#define __SERVER_H__
#include <thread>

#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>

#include <stdint.h>

#include <thread>

#include <string>
#include <fstream>
#include <sstream>

#include <stdint.h>
#include "MessageProtocol.h"

#define PORT 8085

int OP_SAVE = 100;
int OP_RET = 200;
int OP_DEL = 201;
int OP_ALL_LIST = 202;

int SUCCESS_FILE_FOUND_NOTIFICATION = 210;
int SUCCESS_ALL_LIST_NOTIFICATION = 211;
int ERR_FILE_NOT_EXISTS = 1001;
int ERR_NO_FILES_FOR_CLIENT = 1002;
int GENERAL_ERR = 1003;

std::string REPOSITORY_PATH = "C:\\backupsvr";

request_header req_client_header;

class ServerInit {
public:
	SOCKET clientsocket;
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sa = { 0 };
	ServerInit();
	~ServerInit();

	void handleclient();
protected:
	void _userConnect();
	static void _handlerequest(SOCKET clientsocket);

private:
	static std::string __filetostring(const char* filename);
	static int __request_op_handle(int OP);
};



#endif
