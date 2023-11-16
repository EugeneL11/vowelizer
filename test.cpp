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
#define PORT 9011
#define PORT2 9012

using namespace std;

int main() {
    //TCP socket
    int tcpSock = socket(AF_INET, SOCK_STREAM, 0); //socket to interact with server
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //port number of socket
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); //IP address of socket   
    connect(tcpSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //connect socket to server

    //UDP socket
    int udpSock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr2;
    serv_addr2.sin_family = AF_INET;
    serv_addr2.sin_port = htons(PORT2);
    serv_addr2.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (true) {
        //menu to display to user
        string menuStr = 
            "Menu Options\n"
            "- Split Text (basic encoding)      [Press '1']\n"
            "- Merge Text (basic encoding)      [Press '2']\n"
            "- Split Text (advanced encoding)   [Press '3']\n"
            "- Merge Text (advanced encoding)   [Press '4']\n"
            "- Quit                             [Press '5']\n\n"
            "Which option would you like to choose: ";
        string choice = "";
        cout << menuStr;
        getline(cin, choice);
        string splitStr = "";
        string splitStr2 = "";
        string mergeVowel = "";
        string mergeConsonant = "";
        string mergeConsonant2 = "";
        string closeMsg = "Exiting...";
        char buffer[1024] = {0};
        int bytesRec;
        char buffer2[1024] = {0};
        string recStr = "";
        string none = "a";

        if (choice == "1") {
            cout << "\nSplitting Text (basic encoding)" << endl;
            cout << "Please enter a string to split into consonants and vowels: ";
            getline(cin, splitStr);
            splitStr2 = "$bs1" + splitStr; //add the identifier
            send(tcpSock, splitStr2.c_str(), splitStr2.length(), 0);
            //sending using UDP just so the server can have client address
            ssize_t bytesSent = sendto(udpSock, none.c_str(), none.length(), 0, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2));
            bytesRec = recv(tcpSock, buffer, sizeof(buffer), 0);
            cout << "Split Consonant String (Basic): " << buffer << endl;
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, nullptr, nullptr);
            cout << "Split Vowel String(Basic): " << buffer2 << endl << endl;

        } else if (choice == "2") {
            cout << "\nMerging Text (basic encoding)" << endl;
            cout << "Please enter a consonant string to merge: ";
            getline(cin, mergeConsonant);
            mergeConsonant2 = "$bm1" + mergeConsonant; //add the identifier
            send(tcpSock, mergeConsonant2.c_str(), mergeConsonant2.length(), 0);
            cout << "Please enter a vowel string to merge: ";
            getline(cin, mergeVowel); //send over UDP
            ssize_t bytesSent = sendto(udpSock, mergeVowel.c_str(), mergeVowel.length(), 0, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2));
            
            bytesRec = recv(tcpSock, buffer, sizeof(buffer), 0);
            cout << "Merged String (Basic): " << buffer << endl << endl;

        } else if (choice == "3") {
            cout << "\nSplitting Text (advanced encoding)" << endl;
            cout << "Please enter a string to split into consonants and vowels: ";
            getline(cin, splitStr);
            splitStr2 = "$as2" + splitStr; //add the identifier
            send(tcpSock, splitStr2.c_str(), splitStr2.length(), 0);
            //sending using UDP just so the server can have client address
            ssize_t bytesSent = sendto(udpSock, none.c_str(), none.length(), 0, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2));
            bytesRec = recv(tcpSock, buffer, sizeof(buffer), 0);
            cout << "Split Consonant String (Advanced): " << buffer << endl;
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, nullptr, nullptr);
            cout << "Split Vowel String (Advanced): " << buffer2 << endl << endl;

        } else if (choice == "4") {
            cout << "\nMerging Text (advanced encoding)" << endl;
            cout << "Please enter a consonant string to merge: ";
            getline(cin, mergeConsonant);
            mergeConsonant2 = "$am2" + mergeConsonant; //add the identifier
            send(tcpSock, mergeConsonant2.c_str(), mergeConsonant2.length(), 0);
            cout << "Please enter a vowel string to merge: ";
            getline(cin, mergeVowel); //send over UDP
            ssize_t bytesSent = sendto(udpSock, mergeVowel.c_str(), mergeVowel.length(), 0, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2));

            bytesRec = recv(tcpSock, buffer, sizeof(buffer), 0);
            cout << "Merged String (Advanced): " << buffer << endl << endl;

        } else if (choice == "5") {
            cout << "\nThank you for using vowelizer! See you next time..." << endl;
            send(tcpSock, closeMsg.c_str(), closeMsg.length(), 0);
            break;
            
        } else {
            cout << "\nPlease choose a valid option ('1', '2', '3', '4', or '5')" << endl;
            //cin >> choice;
        }
    }
    //close both sockets
    close(tcpSock);
    close(udpSock);
    return 0;
}