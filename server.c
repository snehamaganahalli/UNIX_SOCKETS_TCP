/***********************************************************************************************

This is a UNIX TCP socket

***********************************************************************************************/

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>

#include<errno.h>
#include<stdio.h>

int main()
{

/* if it is a unix socket, then it will be on the same system.
   Hence you no need to mention the IP address and the port number.
   Just the socket name is enough to connect the server and the client socket.
*/
int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
if(-1 == sockfd)
{
  perror("socket creation:");
  return -1;
}

struct sockaddr_un serv_addr = {0};
serv_addr.sun_family = AF_UNIX;

unlink("socket_name");
/* Here the socket name is "socket_name", it will be created in the current
   directory. You can specify a different path eg: /socket_name will create a
   socket in the root directory. If a socket is created in root dicrectory then
   sudo previlege is needed.
*/
strncpy(serv_addr.sun_path, "socket_name", sizeof(serv_addr.sun_path)- 1);

/* Bind the socket with the address. Here address is the socket name.
*/
if(-1 == bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_un)))
{
  perror("socket bind:");
  return -1;
}

if(-1 == listen(sockfd,10 ))
{
  perror("socket listen:");
  return -1;
}

struct sockaddr_un cli_addr = {0};
socklen_t addrlen = sizeof(struct sockaddr_un);
/* Accept the first connection on the queue.
   Accept is a blocking call. i.e. when u gice ./s , it will be waiting for clients.
   Instead of accept call you can also use the select call in while(1), it will help
   to connect multiple clients. OR you can put while(1) and accept, this will also help
   for multiple client connection. We can change the behavior of accept call, i.e make it nonblocking also by fcntl function.
*/
int cli_fd = accept(sockfd, (struct sockaddr *) &cli_addr, &addrlen );

char buf[100];
if(-1 == read(cli_fd, buf, 100))
{
  perror("read:");
  return -1;
}

printf("%s", buf);

strncpy(buf, "sneha maganahalli", 100);

if(-1 == write(cli_fd, buf, 100))
{
  perror("write");
  return -1;
}

}
