#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<string.h>
#include<fcntl.h>
#define MY_PORT		8989
#define MAXBUF		256

int main(int argc , char *argv[])
{
    int len;

    WSADATA wsa;
    SOCKET sockfd , clientfd;
    struct sockaddr_in self;
	char buffer[MAXBUF];


    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

	/*---create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

        printf("Socket created.\n");

	/*---initialize address/port structure---*/
	/* bzero(&self, sizeof(self));*/
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	/*---assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

        puts("Bind done");

	/*---make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}

        puts("Waiting for incoming connections...");

	/*---forever... ---*/
	while (1)
	{	struct sockaddr_in client_addr;
	//client_addr is of type sockaddr in which is the generic address structure.
		int addrlen=sizeof(client_addr);




		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
         //inet_ntoa function converts a network address in a struct in_addr to a dots-and-numbers format string.
         printf("IP address is: %s\n", inet_ntoa(client_addr.sin_addr)); //sin Addr contain the IP
         //function ntohs convert network byte order to host byteorder.
         printf("Port is: %d\n", (int) ntohs(client_addr.sin_port));     // sin port contain the port


    while (buffer[0]!='\0')
     {


         memset(buffer, 0, 256); //this function will empty the array, to make sure
       recv(clientfd, buffer, MAXBUF, 0);
       if(isalpha(buffer[0])!=0)//to avoid printing the length if just ENTER was pressed
       {
             printf("The Length of the Message(%s)is:%d\n",buffer,strlen(buffer));
       }

       strupr(buffer); //funtion strupr to make the the string to upper case
       strrev(buffer); //function strrev to revere the string
        len=strlen(buffer); //needed for the send and receive function
		send(clientfd, buffer,len ,0);

        }
		/*---close connection---*/
        // remove the close connection part
	}

	/*---clean up (should never get here!)---*/
	close(sockfd);
        WSACleanup();
	return 0;
}
