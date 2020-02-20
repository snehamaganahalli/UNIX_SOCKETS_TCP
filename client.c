/***************************************************************************************************
                                TCP client Socket
***************************************************************************************************/
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h> //required for struct sockaddr_un

#include<stdio.h>
#include<errno.h>

int main()
{


int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
if(-1 == sockfd)
{
  perror("socket creation:");
  return -1;
}

struct sockaddr_un serv_addr;
memset(&serv_addr, 0, sizeof(struct sockaddr_un));

serv_addr.sun_family = AF_UNIX;
strncpy(serv_addr.sun_path, "socket_name", sizeof(serv_addr.sun_path)- 1);

/* Whenever TCP socket is used, connect system call is necessary.
   because TCP needs a 3 way handshake to establish a connection.
   TCP does a connection first and then the packets starts flowing.
   
   connect is similar to bind in terms of args.

   socket connect: Connection refused: This error comes when server is not present and client
   tries to connect to server socket.
*/
if (-1 == connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_un)))
{
  perror("socket connect:");
  return -1;
}

char buf[100] = "JAI HANUMAN :) ANJANEYA";

/* The  send()  call  may  be used only when the socket is in a connected state. 
   The only difference between send() and write(2) is the presence of flags
   ssize_t send(int sockfd, const void *buf, size_t len, int flags);
   ssize_t write(int fd, const void *buf, size_t count);  
 
   ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen);

   sendto is used for UDP.
   If sendto() is used on a connection-mode (SOCK_STREAM) socket, the arguments dest_addr and addrlen are ignored */
if(-1 == write(sockfd, buf, 100))
{
  perror("write:");
  return -1;
}

if(-1 == read(sockfd, buf, 100))
{
  perror("read:");
  return -1;
}

printf("\n %s \n", buf);

return 0;

}
