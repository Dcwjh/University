#include<Winsock2.h>
#include<stdio.h>

#define DEFAULT_PORT 5050
#define DATA_BUFFER 1024
int main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = DEFAULT_PORT;
	int iLen,iSend,flag;
	flag = 1;
	char buf[DATA_BUFFER] ="I am WangJianhai,this is my client";
	char EXIT[] = "exit";
	struct sockaddr_in ser;
	if(argc <2)
	{
		printf("Usage:client[server IP address]\n");
		return 0;
	}
	memset(buf,0,sizeof(buf));
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return 0;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	sClient = socket(AF_INET,SOCK_STREAM,0);
	if(sClient==INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	if(connect(sClient,(struct sockaddr*)&ser,sizeof(ser))== INVALID_SOCKET)
	{
		printf("connect() Failed:%d\n",WSAGetLastError());
		return 0;
	}
	else
	{

        char buf_send1[30];
        printf("Please enter you name:\n");
        scanf("%s",&buf_send1);
        char buf_send2[1000];
        int len = strlen(buf_send1);
        buf_send1[len] = ':';
        buf_send1[len + 1] = '\0';
        printf("Enter messages:\n");
		while(flag){
			scanf("%s",&buf_send2);
			strcat(buf_send1,buf_send2);
			iSend = send(sClient,buf_send1,sizeof(buf_send1),0);
			if(iSend == SOCKET_ERROR)
            {
                printf("send1()Failed.%d\n",WSAGetLastError());
                break;
            }
            else if(iSend == 0)
                break;
            else
            {
                printf("---------------------------------\n");
                buf_send1[len + 1] = '\0';
                flag = strcmpi(buf_send2,EXIT);
                if(!flag){
                    iSend = send(sClient,buf_send2,sizeof(buf_send2),0);
                    if(iSend == SOCKET_ERROR)
                    {
                        printf("send2()Failed.%d\n",WSAGetLastError());
                        break;
                    }
                }
            }
		}
	}
	closesocket(sClient);
	WSACleanup();
}
