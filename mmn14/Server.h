#ifndef __SERVER_H__
#define __SERVER_H__
#include <thread>

#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

#include <iostream>

#include <stdint.h>

#define PORT 8085





class ServerInit {
public:
	SOCKET clientsocket;
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sa = { 0 };
	ServerInit();
	~ServerInit();

	void handleclient();
private:
	void __userConnect();
	static void __handlerequest(SOCKET clientsocket);
};
 


#endif