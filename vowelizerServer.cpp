// CPSC 441 Assignment 3
// Eugene Lee - 30137489
// TCP & UDP - Vowelizer (server)

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9001

using namespace std;
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int alen = sizeof(address);
    address.sin_family = AF_INET; //for IPv4
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr));
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, alen);
    listen(server_fd, 3); //max 3 clients

    cout << "Waiting for new connection..." << endl;
    
    int accepted = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&alen);
    cout << "Connection accepted!" << endl;

    char buffer[1024] = {0};
    int bytesRec = 0;

    while (1) {
        bytesRec = recv(accepted, buffer, sizeof(buffer), 0);
        cout << "Received: " << buffer << endl;
        string recStr(buffer, bytesRec);
        if (recStr == "Exiting...") {
            break;
        }
        // Clear the buffer to prepare for the next chunk
        memset(buffer, 0, sizeof(buffer));
    }
    close(accepted);
    close(server_fd);

    return 0;
}