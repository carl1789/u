#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cmath>
#include <sstream>

constexpr int PORT = 65433;
constexpr int BUFFER_SIZE = 1024;

// Function to perform the calculation
std::string calculate_trig(const std::string& request) {
    std::istringstream iss(request);
    std::string func;
    double angle_degrees;

    iss >> func >> angle_degrees;

    if (iss.fail()) {
        return "Error: Invalid request format. Use 'function angle'.";
    }
    
    double angle_radians = angle_degrees * M_PI / 180.0;
    double result;

    if (func == "sin") {
        result = sin(angle_radians);
    } else if (func == "cos") {
        result = cos(angle_radians);
    } else if (func == "tan") {
        result = tan(angle_radians);
    } else {
        return "Error: Unsupported function. Use 'sin', 'cos', or 'tan'.";
    }

    std::ostringstream oss;
    oss << "The " << func << " of " << angle_degrees << " degrees is " << result;
    return oss.str();
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Trigonometry Calculator Server listening on port " << PORT << std::endl;

    while (true) {
        int len = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        if (len < 0) {
            std::cerr << "recvfrom failed" << std::endl;
            continue;
        }
        buffer[len] = '\0';
        
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        
        std::cout << "Received request: '" << buffer << "' from " << client_ip << std::endl;
        
        // Calculate and send response
        std::string response = calculate_trig(std::string(buffer));
        sendto(server_socket, response.c_str(), response.length(), 0, (const struct sockaddr *)&client_addr, client_len);
        std::cout << "Sent response: '" << response << "' to " << client_ip << std::endl;
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}