#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* hello = "Hello from Client!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Replace with server IP

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    read(sock, buffer, 1024);
    std::cout << "Server: " << buffer << std::endl;

    close(sock);
    return 0;
}
