// CPSC 441 Assignment 3
// Eugene Lee - 30137489
// TCP & UDP - Vowelizer (client)

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstdlib> //can i use this to use exit()?

//define port to use
#define PORT 8080

using namespace std;

//function declaration
void menuDisplay(int socket);

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0); //socket to interact with server
    struct sockaddr_in serv_addr; 
    string msg = "Hello from client!";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //port number of socket
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); //IP address of socket

    connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //connect socket to server
    
    menuDisplay(client_fd);

    send(client_fd, msg.c_str(), msg.length(), 0); //send data to server
    cout << "YAY" << endl;
    return 0;
}

//function definition
void menuDisplay(int socket) {
    //menu to display to user
    string menuStr = 
        "Menu Options\n"
        "- Split Text (basic encoding)      [Press '1']\n"
        "- Merge Text (basic encoding)      [Press '2']\n"
        "- Split Text (advanced encoding)   [Press '3']\n"
        "- Merge Text (advanced encoding)   [Press '4']\n"
        "- Quit                             [Press '5']\n\n"
        "Which option would you like to choose: ";
    string choice;
    cout << "Connection successful!\n\n" << menuStr;
    cin >> choice;
    
    while (true) {
        if (choice == "1") {
            cout << "\nsplitting text (basic)" << endl;
            menuDisplay(socket);
            break;
        } else if (choice == "2") {
            cout << "\nmerging text (basic)" << endl;
            menuDisplay(socket);
            break;
        } else if (choice == "3") {
            cout << "\nsplitting text (advanced)" << endl;
            menuDisplay(socket);
            break;
        } else if (choice == "4") {
            cout << "\nmerging text (advanced)" << endl;
            menuDisplay(socket);
            break;
        } else if (choice == "5") {
            cout << "\nThank you for using vowelizer! See you next time..." << endl;
            exit(0);
        } else {
            cout << "\nchoose a valid option: ";
            cin >> choice;
        }
    }
}