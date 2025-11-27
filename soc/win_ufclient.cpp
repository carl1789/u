// Client program for a Trigonometry Calculator using UDP in C++ (Windows)
// Sends a user-provided request and prints the calculated result from the server.

#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

const char* HOST = "127.0.0.1";
constexpr int PORT = 65433;
constexpr int BUFFER_SIZE = 1024;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(client_socket);
        WSACleanup();
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
        sendto(client_socket, user_input.c_str(), user_input.length(), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

        // Receive response
        socklen_t server_len = sizeof(server_addr);
        int len = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_len);
        if (len < 0) {
            std::cerr << "recvfrom failed" << std::endl;
            break;
        }
        buffer[len] = '\0';

        std::cout << "Server response: " << buffer << std::endl;
    }

    std::cout << "Exiting client." << std::endl;
    closesocket(client_socket);
    WSACleanup();
    return 0;
}