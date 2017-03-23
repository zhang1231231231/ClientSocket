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
	SOCKET sockClient;//�ͻ���socket
	SOCKADDR_IN addrServer;
	SOCKET socketServer;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�½��ͻ���socket
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	//����Ҫ���ӵķ������˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	//��������
	char message[20] = "Hello Server!";
	send(sockClient, message, strlen(message) + 1, 0);
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	/*while (true)
	{*/
	try
	{
		Sleep(1000);
		//�������̣�ֱ���з�������������Ϊֹ
		//socketServer = accept(sockClient, (SOCKADDR*)&addrServer, &len);
		//���ղ���ӡ����������
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
		//�ر�socket
		closesocket(socketServer);
	}
	//}
	closesocket(sockClient);
	WSACleanup();
	return 0;
}

