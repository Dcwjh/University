#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//������ʹ�õĶ˿ں�Ϊ5050
#define DEFAULT_PORT 7070
#define BUFFER_LENGTH 1024
int main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	//�ͻ���ַ����
	int iLen,count =0;
	int flag = 1;
	time_t t;
	//time(&t); //ȡ�õ�ǰʱ�� printf("%s\n",ctime(&t));//
	//���͵����ݳ���
	//int iSend;
	//�������ݵĳ���
	int iSend,iRecv;
	//�������ݵĻ�����
	char EXIT[] = "exit";
	char recv_buf[BUFFER_LENGTH];
	//Ҫ���͸��ͻ�����Ϣ
	//char buf[]="I am a server.";
	//�������Ϳͻ��ĵ�ַ
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



