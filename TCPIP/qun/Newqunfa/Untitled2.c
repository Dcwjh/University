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
	char recv_buf[BUFFER_LENGTH];
	char send_buf[BUFFER_LENGTH];
	//Ҫ���͸��ͻ�����Ϣ
	//char buf[]="I am a server.";
	//�������Ϳͻ��ĵ�ַ
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
	ser1.sin_addr.s_addr = inet_addr ("192.168.1.102");
	ser2.sin_family=AF_INET;
	ser2.sin_port=htons(iPort);
	ser2.sin_addr.s_addr = inet_addr ("112.23.81.126");
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




