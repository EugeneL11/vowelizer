// CPSC 441 Assignment 3
// Eugene Lee - 30137489
// TCP & UDP - Vowelizer (server)

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//define port for sockets and IP address
#define PORT1 9011
#define PORT2 9012
#define IP1 "127.0.0.1"

using namespace std;

int main() {
    //for TCP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int alen = sizeof(address);
    address.sin_family = AF_INET; //for IPv4
    inet_pton(AF_INET, IP1, &(address.sin_addr));
    address.sin_port = htons(PORT1);
    bind(server_fd, (struct sockaddr*)&address, alen);
    listen(server_fd, 3); //max 3 clients
    cout << "Waiting for new TCP connection..." << endl;
    int accepted = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&alen);
    cout << "TCP Connection accepted!" << endl;

    //for UDP socket
    int udpSock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in udpAddr;
    udpAddr.sin_family = AF_INET;
    udpAddr.sin_addr.s_addr = INADDR_ANY;
    udpAddr.sin_port = htons(PORT2);
    if (bind(udpSock, (struct sockaddr*)&udpAddr, sizeof(udpAddr)) == -1) {
        cout << "UDP Bind Failed!" << endl;
        return -1;
    }
    cout << "UDP Bind Successful!" << endl;

    while (1) {
        //initialize variables
        char buffer[1024] = {0};
        int bytesRec = 0;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        char buffer2[1024] = {0};
        char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        string vowelStr = "";
        string consonantStr = "";
        bytesRec = recv(accepted, buffer, sizeof(buffer), 0);
        cout << "Received: " << buffer << endl;
        string recStr(buffer, bytesRec);
        
        //option one (basic split)
        if (recStr.find("$bs1") != string::npos) { //if it has identifier
            recStr = recStr.erase(0, 4); //remove identifier now
            for (size_t i = 0; i < recStr.length(); ++i) { //loop through string
                char c = recStr[i];
                //check if the character is a vowel
                if (find(begin(vowels), end(vowels), c) != end(vowels)) {
                    vowelStr += c; //char is a vowel
                    consonantStr += " "; //add spaces to represent consonants
                } else {
                    consonantStr += c; //char is a consonant
                    vowelStr += " "; //add spaces to represent vowels
                }
            }
            //send consonant string using TCP
            send(accepted, consonantStr.c_str(), consonantStr.length(), 0);
            //receive dummy message to resolve client address for UDP
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
            //send vowel string using UDP
            ssize_t bytesSent = sendto(udpSock, vowelStr.c_str(), vowelStr.length(), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
        }

        //option two (basic merge)
        else if (recStr.find("$bm1") != string::npos) { //if it has identifier
            recStr = recStr.erase(0, 4); //remove identifier now, this is the consonant string
            cout << "Consonant String: " << recStr << endl;
            //receive vowel string
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, nullptr, nullptr);
            cout << "Vowel String: " << buffer2 << endl;
            string vowel(buffer2); //convert to string
            //loop through the consonant string
            for (size_t i = 0; i < recStr.length(); ++i) {
                //if a consonant has a space
                if (recStr[i] == ' ') {
                    //replace with counterpart from vowel string (works since they are same length)
                    recStr[i] = vowel[i];
                }
            }
            //send the merged string to client over TCP
            send(accepted, recStr.c_str(), recStr.length(), 0);
        }

        //option three (advanced split)
        else if (recStr.find("$as2") != string::npos) { //if it has identifier
            int count = 0;
            recStr = recStr.erase(0, 4); //remove identifier now
            for (size_t i = 0; i < recStr.length(); ++i) { //loop through string
                char c = recStr[i];
                //check if the character is a vowel
                if (find(begin(vowels), end(vowels), c) != end(vowels)) {
                    //if there are consonants in between
                    if (count > 0) {
                        //write the count in the vowel string
                        vowelStr += to_string(count);
                    }
                    vowelStr += c; //char is a vowel
                    count = 0; //reset the counter
                } else { //if consonant
                    consonantStr += c; //char is a consonant
                    count += 1; //increment consonant count
                }
            }
            //send the consonant string over TCP
            send(accepted, consonantStr.c_str(), consonantStr.length(), 0);
            //receive dummy message to resolve client address for UDP
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
            //send vowel string using UDP
            ssize_t bytesSent = sendto(udpSock, vowelStr.c_str(), vowelStr.length(), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
        }

        //option four (advanced merge)
        else if (recStr.find("$am2") != string::npos) { //if it has identifier
            consonantStr = recStr.erase(0, 4); //remove identifier now
            cout << "Consonant String: " << consonantStr << endl;
            ssize_t udpBytesRec = recvfrom(udpSock, buffer2, sizeof(buffer2), 0, nullptr, nullptr);
            cout << "Vowel String: " << buffer2 << endl;
            string vowel(buffer2); //convert to string
            string mergedStr = "";
            //loop through the vowel string
            for (size_t i = 0; i < vowel.length(); ++i) {
                char c = vowel[i];
                int cVal = c - '0'; //convert char to int
                //if it is a vowel
                if (find(begin(vowels), end(vowels), c) != end(vowels)) {
                    mergedStr += c; //add char to result string
                } else { //if not a vowel
                    mergedStr += consonantStr.substr(0, cVal); //add the correct num of non-vowels
                    consonantStr.erase(0, cVal); //remove the used non-vowels
                }
                //on the last iteration, add remaining consonants
                if (i == vowel.length() - 1) {
                    mergedStr += consonantStr;
                }
            }
            //send the merged string to client over TCP
            send(accepted, mergedStr.c_str(), mergedStr.length(), 0);
        }

        //option five (exit)
        else if (recStr == "Exiting...") {
            break;
        }
        // Clear the buffer to prepare for the next chunk
        memset(buffer, 0, sizeof(buffer));
    }
    //close all the sockets
    close(accepted);
    close(server_fd);
    close(udpSock);

    return 0;
}