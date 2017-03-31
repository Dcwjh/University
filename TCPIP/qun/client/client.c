#include<Winsock2.h>
#include<stdio.h>
#include<time.h>

#define DEFAULT_PORT 7070
#define DATA_BUFFER 1024
int main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET  sClient;
	int     iPort = DEFAULT_PORT;
    int flag = 1;
    time_t t;
	int iLen;
	int iSend;
	int iRecv;
	char buf_send[100] = "-----------------------------------\nClient online\n-----------------------------------";
	char EXIT[] = "exit";
	//char  recv_buf[DATA_BUFFER];

	struct sockaddr_in ser,serl;
	//判断输入的参数是否正确

	//接收数据的缓冲区初始化
	//memset(recv_buf,0,sizeof(recv_buf));
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


	sClient = socket(AF_INET,SOCK_DGRAM,0);
	if(sClient == INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	iSend = sendto(sClient,buf_send,sizeof(buf_send),0,(struct sockaddr*)&ser,sizeof(ser));
    if(iSend == SOCKET_ERROR)
    {
        printf("sendto()Failed:%d\n",WSAGetLastError());
        return 0;
    }
    //char buf_name[1024];
    //printf("Please enter you name:\n");
    //scanf("%s",&buf_name);
    //int len = strlen(buf_name);
    char buf_name[1024] = "汪建海:";
    //int len = 6;//strlen(buf_name);
    //buf_name[len] = ':';
    //buf_name[len + 1] = '\0';
    printf("Enter message:\n");
	while(flag){
        printf("*   *   *   *   *   *   *   *   \n");
        time(&t);
        printf("%s",ctime(&t));
        scanf("%s",&buf_send);
        flag = strcmpi(buf_send,EXIT);
        if(!flag){
            iSend = sendto(sClient,buf_send,sizeof(buf_send),0,(struct sockaddr*)&ser,sizeof(ser));
            if(iSend == SOCKET_ERROR)
            {
                printf("sendto()Failed:%d\n",WSAGetLastError());
                return 0;
            }
            else if(iSend == 0)
                return 0;
            else{
                printf("Client Exit!\n");
            }
        }
        else {
            strcat(buf_name,buf_send);
            iSend = sendto(sClient,buf_name,sizeof(buf_name),0,(struct sockaddr*)&ser,sizeof(ser));
            if(iSend == SOCKET_ERROR)
            {
                printf("sendto()Failed:%d\n",WSAGetLastError());
                return 0;
            }
            else if(iSend == 0)
                return 0;
            else{
                buf_name[7] = '\0';
               // buf_name[len + 1] = '\0';
            }

        }
	}
   // iRecv = recvfrom(sClient,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser,&iLen);

   // if(iRecv == SOCKET_ERROR)
   // {
   //     printf("recvfrom()Failed.:%d\n",WSAGetLastError());
   //     return 0 ;
   // }

   // else if(iRecv == 0)
   //     return 0 ;
   // else
   // {
   //     printf("recfrom():%s\n",recv_buf);
   //     return 0;
   // }


	closesocket(sClient);
	WSACleanup();
	return 0;
}

