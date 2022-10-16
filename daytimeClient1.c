#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

int main(int argc, char *argv[]) {
    char recvbuffer[BUFSIZE]; // I/O buffer
    int numBytes = 0;

    if (argc < 3) // Test for correct number of arguments
    DieWithUserMessage("Parameter(s)",
        "<Server Address> <Server Port>");

    char *servIP = argv[1]; // First arg: server IP address (dotted quad)

    in_port_t servPort = atoi(argv[2]);

    // Create a reliable, stream socket using TCP
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Construct the server address structure
    struct sockaddr_in servAddr;             // Server address
    memset(&servAddr, 0, sizeof(servAddr));  // Zero out structure
    servAddr.sin_family = AF_INET;           // IPv4 address family
    // Convert address
    inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    servAddr.sin_port = htons(servPort);     // Server port

    // Establish the connection to the echo server
    connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr));

    numBytes = recv(sock, recvbuffer, BUFSIZE - 1, 0);
    recvbuffer[numBytes] = '\0';    // Terminate the string!
    fputs(recvbuffer, stdout);      // Print the echo buffer

    fputc('\n', stdout); // Print a final linefeed

    close(sock);
    
    exit(0);
}