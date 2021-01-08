#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUF_SIZE 100
int main() {
    // std::cout << "Hello, World!" << std::endl;
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(1234);
    bind(server_sock, (struct sockaddr*)&server_address, sizeof(server_address));
    
    listen(server_sock, 20);
    struct  sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    char buffer[BUF_SIZE] = {0};
    while (1) {
        int client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_addr_size);
        ssize_t strLen = recv(client_sock, buffer, BUF_SIZE, 0);
        if (strcmp(buffer, "stop") == 0) break;
        for (char & i : buffer) {
            if (i >= 'a' && i <= 'z')
                i += 'A' - 'a';
        }
//        printf("%s\n", buffer);
        send(client_sock, buffer, strLen, 0);
        close(client_sock);
        memset(buffer, 0, BUF_SIZE);
    }
    close(server_sock);
    
    return 0;
}
