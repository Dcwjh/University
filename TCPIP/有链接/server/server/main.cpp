#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>


//������ʹ�õĶ˿ں�Ϊ5050
#define DEFAULT_PORT 5050
#define BUFFER_LENGTH 1024
int main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sListen,
		   sAccept;
	//�ͻ���ַ����
	int iLen;
	//���͵����ݳ���
	//int iSend;
	//�������ݵĳ���
	int iRecv,flag;
	flag = 1;
	//�������ݵĻ�����
	char recv_buf[BUFFER_LENGTH];
	char EXIT[]="exit";
	//Ҫ���͸��ͻ�����Ϣ
	//char buf[]="I am a server.";
	//�������Ϳͻ��ĵ�ַ
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
	//�������������׽ӿ�
	sListen=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//���½����������˵�ַ
	ser.sin_family=AF_INET;
	//htons()������һ��˫�ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	ser.sin_port=htons(iPort);
	//htonl()������һ�����ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	//ʹ��ϵͳָ����IP��ַINADDR_ANY
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//�������״̬
	if(listen(sListen,5)==SOCKET_ERROR)
	{
		printf("listen()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//��ʼ���ͻ���ַ���Ȳ���
	iLen=sizeof(cli);
	//�������ݵĻ�������ʼ��
	memset(recv_buf,0,sizeof(recv_buf));
	//����һ������ѭ�����ȴ��ͻ�����������
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


