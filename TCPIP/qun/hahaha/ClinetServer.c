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
	int iLen;
	int flag = 1;
	time_t t;
	//time(&t); //ȡ�õ�ǰʱ�� printf("%s\n",ctime(&t));//
	//���͵����ݳ���
	//int iSend;
	//�������ݵĳ���
	int iSend,iRecv;
	//�������ݵĻ�����
	char EXIT[] = "exit";
	char recv_buf[] = "�ɶ��ӣ����Ǵ�ɵ�ƣ��ǺǺǺǣ�����";
	//Ҫ���͸��ͻ�����Ϣ
	//char buf[]="I am a server.";
	//�������Ϳͻ��ĵ�ַ
	struct sockaddr_in ser,ser1,ser2,
		cli;
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
	ser1.sin_family=AF_INET;
	ser1.sin_port=htons(iPort);
	ser1.sin_addr.s_addr = inet_addr ("112.0.255.255");  //����Ų���+255
	if(bind(sSocket,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return 0;
	}
	//��ʼ���ͻ���ַ���Ȳ���
	iLen=sizeof(cli);
	//�������ݵĻ�������ʼ

	while(flag)
	{
        iSend = sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser1,sizeof(ser1));
        iRecv = recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
        //printf("������������������������������������������������������������������������������������������������������������������������������������\n");
          //  time(&t);
            //printf("%s",ctime(&t));
            //printf("%s\n",recv_buf);
            //printf("Accept client IP:[%s],port:[%d]\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
    }
	closesocket(sSocket);
	WSACleanup();
	return 0;
}




