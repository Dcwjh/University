#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>


//������ʹ�õĶ˿ں�Ϊ5050
#define DEFAULT_PORT 7070
#define BUFFER_LENGTH 1024
int main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	//�ͻ���ַ����
	int iLen;
	//���͵����ݳ���
	//int iSend;
	//�������ݵĳ���
	int iSend,iRecv;
	//�������ݵĻ�����
	char send_buf[] = "Hello!I am a server.";
	char recv_buf[BUFFER_LENGTH];
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
	sSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(sSocket==INVALID_SOCKET)
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
	if(bind(sSocket,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//��ʼ���ͻ���ַ���Ȳ���
	iLen=sizeof(cli);
	//�������ݵĻ�������ʼ��
	memset(recv_buf,0,sizeof(recv_buf));
	//����һ������ѭ�����ȴ��ͻ�����������
	while(1)
	{
        iRecv=recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
		if(iRecv == SOCKET_ERROR)
		{
			printf("recvfrom()Failed:%d\n",WSAGetLastError());
			break;
		}
       else if(iRecv == 0)
            break;
       else{
            printf("recvfrom():%s\n",recv_buf);
            printf("Accept client IP:[%s],port:[%d]\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
       }
       iSend = sendto(sSocket,send_buf,sizeof(send_buf),0,(SOCKADDR*)&cli,sizeof(cli));
       if(iSend == SOCKET_ERROR){
            printf("sendto()Failed.%d\n",WSAGetLastError());
            printf("-------------------------------------\n");
            break;
       }
       else if(iSend == 0)
        break;
       else{
        printf("sendto() succeeded!\n");
        printf("----------------------");
       }
	}
	closesocket(sSocket);
	WSACleanup();
	return 0;
}



