#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int alen = sizeof(address);
    address.sin_family = AF_INET; //for IPv4
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr));
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, alen);
    listen(server_fd, 3); //max 3 clients

    int accepted = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&alen);
    char buffer[1024] = {0};
    read(accepted, buffer, 1024);
    cout << "Received: " << buffer << endl;
    close(server_fd);

    return 0;
}