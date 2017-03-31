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
	int iLen;
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
	char send_buf[BUFFER_LENGTH];
	//要发送给客户的信息
	//char buf[]="I am a server.";
	//服务器和客户的地址
	struct sockaddr_in ser,ser1,ser2,
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
	ser1.sin_family=AF_INET;
	ser1.sin_port=htons(iPort);
	ser1.sin_addr.s_addr = inet_addr ("192.168.1.102");
	ser2.sin_family=AF_INET;
	ser2.sin_port=htons(iPort);
	ser2.sin_addr.s_addr = inet_addr ("112.23.81.126");
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
        iRecv = recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
        flag = strcmpi(recv_buf,EXIT);
        if(!flag){
            time(&t);
            printf("%s",ctime(&t));
            printf("IP:[%s]\n",inet_ntoa(cli.sin_addr));
            printf("Client exit!\n");
            printf("------------------------------------------------\n");
            iSend = sendto(sSocket,inet_ntoa(cli.sin_addr),16,0,(struct sockaddr*)&ser1,sizeof(ser1));
            iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser1,sizeof(ser1));
            iSend = sendto(sSocket,inet_ntoa(cli.sin_addr),16,0,(struct sockaddr*)&ser2,sizeof(ser2));
            iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser2,sizeof(ser2));
            flag = 1;
            continue;
        }
		if(iRecv == SOCKET_ERROR)
		{
			printf("recvfrom()Failed:%d\n",WSAGetLastError());
			break;
		}
        else if(iRecv == 0)
            break;
        else{
            time(&t);
            printf("%s",ctime(&t));
            //printf("IP:[%s]\n",inet_ntoa(cli.sin_addr));
            printf("IP:[%s]\n",inet_ntoa(cli.sin_addr));
            printf("%s\n\n",recv_buf);
           // send_buf = inet_ntoa(cli.sin_addr);

            //printf("Accept client IP:[%s],port:[%d]\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
            iSend = sendto(sSocket,inet_ntoa(cli.sin_addr),16,0,(struct sockaddr*)&ser1,sizeof(ser1));
            iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser1,sizeof(ser1));
            iSend = sendto(sSocket,inet_ntoa(cli.sin_addr),16,0,(struct sockaddr*)&ser2,sizeof(ser2));
            iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser2,sizeof(ser2));
        }
        //iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser1,sizeof(ser1));
        //if(iSend == SOCKET_ERROR)
         //   {
            //    printf("sendto()Failed:%d\n",WSAGetLastError());
             //   return 0;
           // }
           // else if(iSend == 0)
            //    return 0;
             //    iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser2,sizeof(ser2));
           // if(iSend == SOCKET_ERROR)
          //  {
            //    printf("sendto()Failed:%d\n",WSAGetLastError());
              //  return 0;
           // }
          //  else if(iSend == 0)
            //    return 0;
       //iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser1,sizeof(ser1));
      // if(iSend == SOCKET_ERROR)
       // {
        //    printf("sendto()Failed:%d\n",WSAGetLastError());
        //    return 0;
      //  }
       // else if(iSend == 0)
       //     return 0;
      // iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser2,sizeof(ser2));
      // if(iSend == SOCKET_ERROR)
       // {
        //    printf("sendto()Failed:%d\n",WSAGetLastError());
        //    return 0;
        //}
        //else if(iSend == 0)
           // return 0;
	}
	closesocket(sSocket);
	WSACleanup();
	return 0;
}




