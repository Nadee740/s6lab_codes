#include <stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<string.h> 
#include<arpa/inet.h> 
#include<time.h> 

int main()
{
    char *ip = "127.0.0.1";
    int port = 4327;
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror(" [ -] Socket error ");
        exit(1);
    }
    printf(" [+] UDP server socket created \n ");
    memset(&server_addr, '\0' , sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    n = bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror(" [ -] Bind error ");
        exit(1);
    }
    printf(" [+] Bind to the port number : %d \n ", port);
    while (1)
    {
        bzero(buffer, 1024);
        addr_size = sizeof(client_addr);
        recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
        printf(" Recieved a time request from client !\n ");
        time_t now = time(0);
        char *time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0';
        printf(" Server : Send the system time to client ... ");
        strcpy(buffer, time_str);
        sendto(sock, buffer, 1024, 0, (struct sockaddr *)&client_addr,
                  sizeof(client_addr));
    }
    return 0;

}