#include <stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h>
 #include<arpa/inet.h> 
 
 int main()
{
    char *ip = "127.0.0.1";
    int port = 4327;
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror(" [ -] Socket error ");
        exit(1);
    }
    printf(" [+] UDP server socket created \n ");
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);
    bzero(buffer, 1024);
    strcpy(buffer, " sending a time request to server ");
    printf(" Client : %s \n ", buffer);
    sendto(sock, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
    bzero(buffer, 1024);
    addr_size = sizeof(addr);
    recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
    printf(" Server : %s \n ", buffer);
    close(sock);
    printf(" Disconnected from the server \n ");
    return 0;
}