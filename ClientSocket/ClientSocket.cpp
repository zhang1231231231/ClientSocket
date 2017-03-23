// ClientSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <cstdio>
#include <errno.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	int err = 0;
	WSADATA wsaData;
	SOCKET sockClient;//客户端socket
	SOCKADDR_IN addrServer;
	SOCKET socketServer;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//新建客户端socket
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	//定义要连接的服务器端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	//发送数据
	char message[20] = "Hello Server!";
	send(sockClient, message, strlen(message) + 1, 0);
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	/*while (true)
	{*/
	try
	{
		Sleep(1000);
		//阻塞进程，直到有服务器连接上来为止
		//socketServer = accept(sockClient, (SOCKADDR*)&addrServer, &len);
		//接收并打印服务器数据
		err = recv(sockClient, recvBuf, 100, 0);
		if (err == -1)
		{
			perror("recv");
			printf("recv error!");
		}
		else
		{
			printf("%s\n", recvBuf);
		}
	}
	catch (...)
	{
		//关闭socket
		closesocket(socketServer);
	}
	//}
	closesocket(sockClient);
	WSACleanup();
	return 0;
}

