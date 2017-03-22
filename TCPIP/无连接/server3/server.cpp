#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define DEFAULT_PORT 8080
#define BUFFER_LENGTH 1024

int main() {

	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	//客户地址长度
	int iLen;
	//发送的数据长度
	int iSend, iSend1;
	int iRecv;
	//接收数据的缓冲
	char buf[BUFFER_LENGTH];
	char *add[2] = { "112.23.67.118","112.23.83.110" };
    char *fExit[1] = {"exit"};
	//要发送给客户的信息
	//char mes[100];
	//服务器和客户的地址
	struct sockaddr_in ser, cli, cli1;
	cli1.sin_family = AF_INET;
	cli1.sin_port = htons(iPort);
	//cli1.sin_addr.s_addr = inet_addr("192.168.220.128");

	printf("-----------------\n");
	printf("Server waiting\n");
	printf("-----------------\n");

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n");
		return 0;
	}

	//创建服务器端套接口
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		printf("socket() Failed:%d\n", WSAGetLastError());
		return 0;
	}

	//以下建立服务器端地址
	ser.sin_family = AF_INET;
	//htons()函数把一个双字节主机字节顺序的数转化为网络字节顺序的数
	ser.sin_port = htons(iPort);
	//htonl()函数把一个四字节主机字节顺序的数转化为网络字节顺序的数
	//使用系统制定的IP地址INADDR_ANY
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind() Failed: %d\n", WSAGetLastError());
		return 0;
	}

	//初始化客户地址长度参数
	iLen = sizeof(cli);
	memset(buf, 0, sizeof(buf));
	//进入一个无限循环等待用户的连接请求
	while (1)
	{
		//从客户端接收数据
            int cnt1 = 10;
		while (1) {
			iRecv = recvfrom(sSocket, buf, BUFFER_LENGTH, 0, (SOCKADDR*)&cli, &iLen);
			if (iRecv == 0)
				return 0;
			else if (iRecv == SOCKET_ERROR)
			{
				printf("recv() Failed: %d\n", WSAGetLastError());
				return 0;
			}
			else {
                    if(!strcmp(fExit[0],(char*)(buf)))
                       {
                           printf("Client [%s] Exit!\n",inet_ntoa(cli.sin_addr));
                            memset(buf, 0, sizeof(buf));
                           continue;
                       }
				time_t timep;
				time(&timep);
				printf("%s\n", ctime(&timep));
				if(!strcmp(inet_ntoa(cli.sin_addr),add[0])){printf("汪建海[%s]: %s\n", inet_ntoa(cli.sin_addr), buf);}
				else if(!strcmp(inet_ntoa(cli.sin_addr),add[1])) {printf("鄢东子[%s]: %s\n", inet_ntoa(cli.sin_addr), buf);}
				printf("-------------------------\n");
			}

			//给连接的客户发送信息
			iSend = sendto(sSocket, buf, sizeof(buf), 0, (SOCKADDR*)&cli, sizeof(cli));
			if (iSend == SOCKET_ERROR)
			{
				printf("sendto() Failed:%d\n", WSAGetLastError());
				printf("-------------------------\n");
				break;
			}
			else if (iSend == 0)
				break;
			iSend1 = sendto(sSocket, buf, sizeof(buf), 0, (SOCKADDR*)&cli1, sizeof(cli1));
			if (iSend1 == SOCKET_ERROR)
			{
				printf("sendto() Failed:%d\n", WSAGetLastError());
				printf("-------------------------\n");
				break;
			}
			else if (iSend1 == 0)
				break;
		}



	}
	closesocket(sSocket);
	WSACleanup();
	return 0;
}

