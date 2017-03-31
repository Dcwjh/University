#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//服务器使用的端口号为5050
#define DEFAULT_PORT 7070
#define BUFFER_LENGTH 1024
int main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	//客户地址长度
	int iLen,count =0;
	int flag = 1;
	time_t t;
	//time(&t); //取得当前时间 printf("%s\n",ctime(&t));//
	//发送的数据长度
	//int iSend;
	//接收数据的长度
	int iSend,iRecv;
	//接收数据的缓冲区
	char EXIT[] = "exit";
	char recv_buf[BUFFER_LENGTH];
	//要发送给客户的信息
	//char buf[]="I am a server.";
	//服务器和客户的地址
	struct sockaddr_in ser,
		cli;
	printf("------------------\n");
	printf("Server waiting\n");
	printf("------------------\n");
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return 0;
	}
	//创建服务器端套接口
	sSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(sSocket==INVALID_SOCKET)
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
	if(bind(sSocket,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//初始化客户地址长度参数
	iLen=sizeof(cli);
	//接收数据的缓冲区初始化
	memset(recv_buf,0,sizeof(recv_buf));
	//进入一个无限循环，等待客户的连接请求
	while(flag)
	{
        iRecv=recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
        flag = strcmpi(recv_buf,EXIT);
        if(flag)
        {
            if(count%2 == 0){
                printf("\n");
                time(&t);
                printf("%s",ctime(&t));
                printf("IP:[");
                printf("%s",recv_buf);
                printf("]\n");
            }
            else{
                printf("%s\n",recv_buf);
            }
            count++;
       }
       else{
            printf("Client exit!\n");
            printf("-----------------------------------------------\n");
            count = 0;
            flag = 1;
            continue;
       }

	}
	closesocket(sSocket);
	WSACleanup();
	return 0;
}



