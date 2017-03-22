#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>


//服务器使用的端口号为5050
#define DEFAULT_PORT 5050
#define BUFFER_LENGTH 1024
int main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sListen,
		   sAccept;
	//客户地址长度
	int iLen;
	//发送的数据长度
	//int iSend;
	//接收数据的长度
	int iRecv,flag;
	flag = 1;
	//接收数据的缓冲区
	char recv_buf[BUFFER_LENGTH];
	char EXIT[]="exit";
	//要发送给客户的信息
	//char buf[]="I am a server.";
	//服务器和客户的地址
	struct sockaddr_in ser,
		cli;
	printf("-------------\n");
	printf("Server waiting\n");
	printf("-------------\n");
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return 0;
	}
	//创建服务器端套接口
	sListen=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//以下建立服务器端地址
	ser.sin_family=AF_INET;
	//htons()函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
	ser.sin_port=htons(iPort);
	//htonl()函数把一个四字节主机字节顺序的数转换为网络字节顺序的数
	//使用系统指定的IP地址INADDR_ANY
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//进入监听状态
	if(listen(sListen,5)==SOCKET_ERROR)
	{
		printf("listen()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//初始化客户地址长度参数
	iLen=sizeof(cli);
	//接收数据的缓冲区初始化
	memset(recv_buf,0,sizeof(recv_buf));
	//进入一个无限循环，等待客户的连接请求
	while(1)
	{
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		if(sAccept==INVALID_SOCKET)
		{
			printf("accept()Failed:%d\n",WSAGetLastError());
			break;
		}
        printf("Connect Succeed!\n");
        printf("*********************************\n");
		while(flag){
            iRecv=recv(sAccept,recv_buf,sizeof(recv_buf),0);
            flag=strcmpi(recv_buf,EXIT);
            if(iRecv==SOCKET_ERROR)
            {
                printf("recv()Failed:%d\n",WSAGetLastError());
                break;
            }
            else
            {
                printf("%s\n",recv_buf);
                printf("-------------\n");
            }
            if(!flag)
            printf("Client exit!\n");
		}
		flag = 1;
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
	return 0;
}


