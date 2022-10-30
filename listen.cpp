#include "listen.h"
#include <iostream>
#include <gst/gst.h>
#include<unistd.h>
#define SOCKETERROR -1

using namespace std;
typedef struct {
  struct sockaddr_in addr; /* Client remote address */
    int connfd;              /* Connection file descriptor */
    int uid;                 /* Client unique identifier */
    char name[32];           /* Client name */
} client_t;


void *handle_connection(void *p_client_socket)
{
    int *client_socket=(int*)p_client_socket;
    int fd=*client_socket;

    char *buf;
    buf=(char*)malloc((255*sizeof(char))+1);
    send(fd,"merhaba web",11,0);
    
    
     
    while(1)
    {
     memset(buf,0,strlen(buf));
     printf(" Buffer Length :%d",strlen(buf));
     int len=recv(fd,buf,255,MSG_PEEK);
    
    
    if(len >255)
    {   
        free(buf);
        buf=(char*)malloc(len*sizeof(char)+1);
       
    }//
     int r=recv(fd,buf,len,0);
     printf("r:%d len:%d",r,len);
     printf("\n buf:%s",buf);
     printf(" \n err  val %s %d ",strerror(errno),errno);    
     if(r<=0)
     {
        printf(" err  val %s %d ",strerror(errno),errno);
        printf("%d",client_socket);
        break;
     } 
         

      
    }
    free(client_socket);
    return NULL;
}
int check(int exp,const char*msg)
{
    if(exp==SOCKETERROR)
    {
        cout<<"err:"<<msg<<endl;
        exit(1);
    }
    return exp;
}
void*ListenFunc(void *pData )
{
    
    cout<<"Start Listening Task"<<endl;
    client_t * client;
    int *pInt = (int*)pData;
    *pInt++;
    //WSADATA   Winsockdata ;
    //int       iWsaStartup ;
    //int       iWsaCleanup;
    int   TCPServerSocket;
    struct  sockaddr_in  TCPServerAdd;
    struct  sockaddr_in  TCPClientAdd;
    socklen_t    iTCPClientAdd=sizeof(TCPServerAdd);
    //char *ip="127.0.0.1";
    int iListen;
    int check=0;
    //int client_socket[online_user_num];
    int capacity=30;
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr =inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);
    cout<<"socket ailesi"<<TCPClientAdd.sin_family;
    TCPServerSocket = socket(AF_INET,SOCK_STREAM,0);
    cout<<TCPClientAdd.sin_family;
    if (TCPServerSocket == -1)
    {
        cout<<"TCP Server Socket Creation Failed"<<endl;
        //cout<<"Error Code - "<<WSAGetLastError()<<endl;
    }
    cout<<"TCP Server Socket Creation Success"<<endl;
    const int enable =1;
    setsockopt(TCPServerSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    //cout<<"set";
    bind(TCPServerSocket,(sockaddr *)&TCPServerAdd,sizeof(TCPServerAdd));
    cout<<"bind"<<endl;
    listen(TCPServerSocket,5);
    while (1)
    {
        check=accept(TCPServerSocket,(sockaddr*)&TCPClientAdd,&iTCPClientAdd);
        printf(" err  val %s %d ",strerror(errno),errno);
        printf("accepted");
        pthread_t t;

        if(check>0)
            {

                int*pclient;
                pclient=(int*)malloc(sizeof(check));
                *pclient=socket(AF_INET,SOCK_STREAM,0);
                *pclient=check;

                pthread_create(&t,NULL,handle_connection,(void*)pclient);
                printf("\n socket size:%d",sizeof(*pclient));
            }
            else
            {
                printf("%d",errno);
                
                //close(client_socket);
                    
            }
    }
    close(TCPServerSocket);
    return NULL;




}



















