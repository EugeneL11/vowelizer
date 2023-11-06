#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    string msg = "Hello from client!";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(client_fd, msg.c_str(), msg.length(), 0);
    cout << "YAY" << endl;
    return 0;
}