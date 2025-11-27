// Client program for a Trigonometry Calculator using UDP in C++ (Unix/Linux)
// Sends a user-provided request and prints the calculated result from the server.

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* HOST = "127.0.0.1";
constexpr int PORT = 65433;
constexpr int BUFFER_SIZE = 1024;

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(client_socket);
        return 1;
    }

    std::string user_input;
    while (true) {
        std::cout << "Enter calculation (e.g., 'sin 30') or 'exit' to quit: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            break;
        }
        if (user_input.empty()){
            continue;
        }

        // Send user request to server
        sendto(client_socket, user_input.c_str(), user_input.length(), MSG_CONFIRM, (const struct sockaddr *)&server_addr, sizeof(server_addr));

        // Receive response
        socklen_t server_len = sizeof(server_addr);
        ssize_t len = recvfrom(client_socket, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &server_len);
        if (len < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[len] = '\0';

        std::cout << "Server response: " << buffer << std::endl;
    }

    std::cout << "Exiting client." << std::endl;
    close(client_socket);
    return 0;
}
