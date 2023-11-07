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
void menuDisplay();

int main() {
    menuDisplay();

    return 0;
}

//function definition
void menuDisplay() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0); //socket to interact with server
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //port number of socket
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); //IP address of socket   
    connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //connect socket to server
    
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
    string splitStr;
    string mergeVowel;
    string mergeConsonant;

    while (true) {
        if (choice == "1") {
            cout << "\nSplitting Text (basic encoding)" << endl;
            cout << "Please enter a string to split into consonants and vowels: ";
            cin >> splitStr;
            send(client_fd, splitStr.c_str(), splitStr.length(), 0);

            menuDisplay();
            break;
        } else if (choice == "2") {
            cout << "\nMerging Text (basic encoding)" << endl;
            cout << "Please enter a consonant string to merge: ";
            cin >> mergeConsonant;
            send(client_fd, mergeConsonant.c_str(), mergeConsonant.length(), 0);
            cout << "Please enter a vowel string to merge: ";
            cin >> mergeVowel; //send over UDP
            send(client_fd, mergeVowel.c_str(), mergeVowel.length(), 0);

            menuDisplay();
            break;
        } else if (choice == "3") {
            cout << "\nSplitting Text (advanced encoding)" << endl;
            cout << "Please enter a string to split into consonants and vowels: ";
            cin >> splitStr;
            send(client_fd, splitStr.c_str(), splitStr.length(), 0);

            menuDisplay();
            break;
        } else if (choice == "4") {
            cout << "\nMerging Text (advanced encoding)" << endl;
            cout << "Please enter a consonant string to merge: ";
            cin >> mergeConsonant;
            send(client_fd, mergeConsonant.c_str(), mergeConsonant.length(), 0);
            cout << "Please enter a vowel string to merge: ";
            cin >> mergeVowel; //send over UDP
            send(client_fd, mergeVowel.c_str(), mergeVowel.length(), 0);

            menuDisplay();
            break;
        } else if (choice == "5") {
            cout << "\nThank you for using vowelizer! See you next time..." << endl;
            exit(0);
        } else {
            cout << "\nPlease choose a valid option ('1', '2', '3', '4', or '5'): ";
            cin >> choice;
        }
    }
}