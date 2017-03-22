#include<Winsock2.h>
#include<stdio.h>
//服务器端口号为5050
#define DEFAULT_PORT 7070
#define DATA_BUFFER 1024
int main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET  sClient;
	int     iPort = DEFAULT_PORT;

	int iLen;
	int iSend;
	int iRecv;
	char  send_buf[]="Hello!I am a client.";

	char recv_buf[DATA_BUFFER];

	struct sockaddr_in ser;
	//判断输入的参数是否正确
	if(argc<2)
	{
		//提示在命令行中输入服务器IP地址
		printf("Usage:client [server IP address]\n");
		return 0;
	}
	//接收数据的缓冲区初始化
	memset(recv_buf,0,sizeof(recv_buf));
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return 0;
	}
	//填写要连接的服务器地址信息
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	//inet_addr()函数将命令行的点分IP地址转化为用二进制表示的网络字节顺序的IP地址
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	//建立客户端流式套接口
	sClient = socket(AF_INET,SOCK_DGRAM,0);
	if(sClient == INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	iLen = sizeof(ser);
	iSend = sendto(sClient,send_buf,sizeof(send_buf),0,(struct sockaddr*)&ser,iLen);
	if(iSend == SOCKET_ERROR)
    {
        printf("sendto()Failed:%d\n",WSAGetLastError());
        return 0;
    }


	else if(iSend == 0)

        return 0;

    else printf("sendto()succeeded.\n");



    /*从服务器接受数据*/
    iRecv = recvfrom(sClient,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser,&iLen);

    if(iRecv == SOCKET_ERROR)
    {
        printf("recvfrom()Failed.:%d\n",WSAGetLastError());
        return 0 ;
    }

    else if(iRecv == 0)
        return 0 ;
    else
    {
        printf("recfrom():%s\n",recv_buf);
        return 0;
    }
	closesocket(sClient);
	WSACleanup();
	return 0;
}

