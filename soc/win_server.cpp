#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from Server!";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "Socket failed" << std::endl;
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(PORT);

    int res = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if(res != 0) {
      std::cout << "Failed to bind" << std::endl;
      closesocket(server_fd);
      WSACleanup();
      exit(1);
    }
    listen(server_fd, 3);

    std::cout << "Server listening on port " << PORT << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    recv(new_socket, buffer, 1024, 0);
    std::cout << "Client: " << buffer << std::endl;

    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}