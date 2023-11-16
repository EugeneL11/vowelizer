# vowelizer
Eugene Lee - 30137489 / CPSC 441 Assignment 3 / November 15th, 2023

Summary:
This is a vowelizer program written in C++, that splits text into consonants and vowels, transmits these separately across a network, and then combines them at the other end. It transfers data using both TCP and UDP. It includes both server and client side programs. 

User Manual: 
1. Compile the server: Go to the working directory of the code on your device's terminal, and run the following command. 
    "g++ -o vServer vowelizerServer.cpp"
2. Run the server: Run the following command to execute the server program. 
    "./vServer"
3. Compile the client: Run the following command. 
    "g++ -o vClient vowelizerClient.cpp"
4. Run the client: Run the followinf command to execute the client program. 
    "./vClient"

Testing Description: 
- I tested a alot both at school and at home, using my laptop. Since my laptop is Unix, it was not too challenging to make it also work on Linux devices. There seemed to be no difference between testing at home and at the university. I mainly wrote out to the terminal using cout to test my code. By printing out everything, I was able to see which parts are working and which parts aren't. It was a lot of debugging done this way. Being able to locate all the issues helped me understand all the different moving parts of the proxy, and handle all malfunctionalities appropriately.

What Works: 
- Everything in the vowelizer works as expected. I started off as a TCP-based echo server and built it up from there. I even added some error-handling. I set the UDP timeout to 7 seconds in both the client and the server. It has all the required functionalities of the assignment.

What Doesn't Work:
- There shouldn't be anything that doesn't work. I followed all the instructions.