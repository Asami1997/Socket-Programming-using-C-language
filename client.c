
#include<stdio.h> //standard I/O header file
#include<winsock2.h>  //Header file which includes functions used by winsock

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{

    char * quits="QUIT";
    char * quits2="quit";
     SOCKET a;
    WSADATA data;
    char * buffer , reply[256];
    struct sockaddr_in toserv;
    int recvi;
    buffer=malloc(256);//because i need to allocate a memory space otherwise error will result

     // first step is to initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&data) != 0) //if there is error in initialising
    {
        printf("Failuer in initializing : %d",WSAGetLastError());//call wsagetlasterror to know the error
        return 1;
    }

    printf("Initialised.\n");

   //Now we can create the socket after initialising winsock
    //AF_INET is the address family that the socket can communicate with
    //Will return INVALID_SOCKET if there is any error in declaring the socket
    if((a = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Error in creating socket: %d" , WSAGetLastError());
    }

    printf("Socket created successfully.\n");//means that the socket created successfully

     //Now the part where we connect to the server
    //we need to get IP and port to connect to serve

    toserv.sin_addr.s_addr = inet_addr("127.0.0.1");
    toserv.sin_family = AF_INET;
    toserv.sin_port = htons( 8989 ); //port(8989) which is assigned in server

    //Connect to remote server
    if (connect(a , (struct sockaddr *)&toserv , sizeof(toserv)) < 0)
    {
        printf(" error in connection\n");
        return 1;
    }

   printf("Connected successfully\n");


     //now we will send  data to server

     while(1)
     {
              scanf("%255s",buffer); //to keep space for the null character

    if(strcmp(buffer,quits)==0||strcmp(buffer,quits2)==0) //if user pressed QUIT or quit ,close the socket
    {
        closesocket(a);
        WSACleanup();
        return 0;
    }

    if( send(a , buffer , strlen(buffer) , 0) < 0)
    {
        puts("ERROR IN SENDING");
        return 1;
    }
    puts("Data has been sent successfully\n");

    //Receive a reply from the server
    if((recvi = recv(a , reply , 256 , 0)) == SOCKET_ERROR)
    {
        puts("ERROR IN RECEVING");
    }

    puts("A reply recevied from server\n");

    //Add the null character to string
    reply[recvi] = '\0';
    puts(reply);

     }




}
