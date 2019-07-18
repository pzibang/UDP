#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 100

int main()
{
	char revBuffer[BUF_SIZE] = {0};
	char sendBuffer[BUF_SIZE] = {0};
	int strLen = 0;
	WSADATA wsaData;
	WORD wsVersion = MAKEWORD(2, 2);
	if(WSAStartup(wsVersion,&wsaData) !=0 )
	{
		printf("WSAStartup failed\n");
		return -1;
	}

	SOCKET servSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);	//创建套接字
	sockaddr_in servAddr;	//声明服务器地址信息结构体
	memset(&servAddr, 0, sizeof(servAddr));

	//填写服务器地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(69);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);
	while(1)
	{
		printf("input a string \n");
		gets(sendBuffer);

		sendto(servSock, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));

		strLen = recvfrom(servSock, revBuffer,  BUF_SIZE, 0, &fromAddr, &addrLen);
		revBuffer[strLen] = '\0';
		puts(revBuffer);
		shutdown(servSock, SD_BOTH);
	}

	closesocket(servSock);
	WSACleanup();

	return 0;
}
