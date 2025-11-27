#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from Server!";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(PORT);

    int res = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if(res != 0) {
      std::cout << "Failed to bind" << std::endl;
      exit(1);
    }
    listen(server_fd, 3);

    std::cout << "Server listening on port " << PORT << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    read(new_socket, buffer, 1024);
    std::cout << "Client: " << buffer << std::endl;

    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
