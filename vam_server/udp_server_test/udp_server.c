#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to listen for incoming data
double lat, lon;

void die(char *s) {
    perror(s);
    exit(1);
}

int main() {
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen, recv_len;
    char buf[BUFLEN];
    WSADATA wsa;

    slen = sizeof(si_other);

    // Initialize winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    // Create a socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    // Keep listening for data
    printf("Waiting for data...");
    fflush(stdout);

    // Try to receive some data, this is a blocking call
    while (1) {
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR) {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            continue;
        }

        // Print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %.*s\n", recv_len, buf);
             // Extract coordinates
        if (sscanf(buf, "pos: (%lf, %lf)", &lat, &lon) == 2) {
            printf("Latitude: %f, Longitude: %f\n", lat, lon);
        } else {
            printf("Failed to parse the coordinates.\n");
        }

        // Now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
            printf("sendto() failed with error code : %d", WSAGetLastError());
        }
        else {
            printf("send back Data: %.*s\n", recv_len, buf);
        }
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
