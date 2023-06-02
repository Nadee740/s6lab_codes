#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 

int main()
{
    char *ip = "127.0.0.1";
    int port = 10002;
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
    printf(" [+] UDP server socket created \n");
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    n = bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror(" [ -] Bind error ");
        exit(1);
    }
    printf(" [+] Bind to the port number : %d  \n ", port);while (1)
    {
        bzero(buffer, 1024);
        addr_size = sizeof(client_addr);
        recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
        printf(" Client : %s \n ", buffer);
        char temp;
        int left = 0, right = strlen(buffer) - 1;
        while (left < right)
        {
            temp = buffer[left];
            buffer[left] = buffer[right];
            buffer[right] = temp;
            left++;
            right--;
        }
        int len = strlen(buffer);
        for (int i = 0; i < len; i++)
        {
            if (buffer[i] >= 'a'&& buffer[i] <= 'z')
            {
                buffer[i] -= 32;
            }
        }
        sendto(sock, buffer, 1024, 0, (struct sockaddr *)&client_addr,sizeof(client_addr));
        printf(" Server : %s \n ", buffer);
    }
    return 0;
}