#define _WIN32_WINNT 0x0501
#include <iostream>
#include <winsock2.h>
#include <thread>
#include <cstring>
#include"mingw.thread.h"

using namespace std;

#define PORT 9998

SOCKET nclient;
struct sockaddr_in srv;

void receive() {
    char sbuff[1024] = {0};
    int rev;

    while (true) {
        rev = recv(nclient, sbuff, sizeof(sbuff), 0);
        if (rev <= 0) {
            cout << "Client disconnected or error occurred." << endl;
            break;
        }
        sbuff[rev] = '\0';
        cout << "Msg from Client: " << sbuff << endl;
    }
}

void sendMsg() {
    while (true) {
        cout << "send msg to the client: ";
        char input[1024];
        cin.getline(input, sizeof(input));

            send(nclient, input, strlen(input) + 1, 0);
    }
}

int main() {
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        cout << "WSA failed" << endl;
        return 1;
    }

    int nsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = INADDR_ANY;

    int nret = bind(nsocket, (sockaddr*)&srv, sizeof(srv));
    if (nret < 0) {
        cout << "Bind failed" << endl;
        return 1;
    }

    int lisreq = listen(nsocket, 5);
    if (lisreq < 0) {
        cout << "Listen failed" << endl;
        return 1;
    }

    struct sockaddr_in client;
    int nlen = sizeof(client);

    nclient = accept(nsocket, (struct sockaddr*)&client, &nlen);
    if (nclient == INVALID_SOCKET) {
        cout << "Failed to connect" << endl;
        return 1;
    }

    cout << "Connected to the client successfully" << endl;

    thread t1(receive);
    thread t2(sendMsg);

    t1.detach(); // Detach threads to run independently
    t2.detach();

    while (true) {
        // Keep the main thread running
    }

    closesocket(nclient);
    closesocket(nsocket);
    WSACleanup();
    return 0;
}
