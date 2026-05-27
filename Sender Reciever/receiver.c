#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server;
    char buffer[1024];

    WSAStartup(MAKEWORD(2,2), &wsa);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));

    listen(serverSocket, 1);

    printf("Waiting for connection...\n");

    clientSocket = accept(serverSocket, NULL, NULL);

    printf("Client connected!\n");

    while(1) {

        recv(clientSocket, buffer, sizeof(buffer), 0);

        printf("Received: %s\n", buffer);

    }

    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}