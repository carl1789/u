#include <iostream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 9090

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    std::string filename = "sample.txt"; // File to request

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Replace with server IP

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, filename.c_str(), filename.length(), 0);

    std::ofstream outfile("received_" + filename, std::ios::binary);

    int bytesRead;
    while ((bytesRead = read(sock, buffer, 1024)) > 0) {
        outfile.write(buffer, bytesRead);
    }

    std::cout << "File received and saved as received_" << filename << std::endl;

    outfile.close();
    close(sock);
    return 0;
}
