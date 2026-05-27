#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in server;
    char buffer[1024];

    WSAStartup(MAKEWORD(2,2), &wsa);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(clientSocket, (struct sockaddr*)&server, sizeof(server));

    while(1) {

        printf("Enter message: ");

        fgets(buffer, sizeof(buffer), stdin);

        send(clientSocket, buffer, strlen(buffer), 0);

    }

    closesocket(clientSocket);

    WSACleanup();

    return 0;
}