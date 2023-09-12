/*
 * client.cpp
 *
 *  Created on: 18-Aug-2023
 *      Author: Shiv Pathak
 */


#define _WIN32_WINNT 0x0501
#include <bits/stdc++.h>
#include <winsock2.h>
#include "mingw.thread.h"
#include "mingw.invoke.h"

#define PORT 9998
using namespace std;
struct sockaddr_in srv;
int nsocket;
void receive() {
    char sbuff[1024] = {0};
    int rev;

    while (true) {
        rev = recv(nsocket, sbuff, sizeof(sbuff), 0);
        if (rev <= 0) {
            cout << "Client disconnected or error occurred." << endl;
            break;
        }
        sbuff[rev] = '\0';
        cout << "msg from server : " << sbuff << endl;
    }
}

void sendMsg() {
    while (true) {
        cout << "send msg to the server: ";
        char input[1024];
        cin.getline(input, sizeof(input));

        // Send the message to the client multiple times (e.g., 5 times)
            send(nsocket, input, strlen(input) + 1, 0);
    }
}
int main(){
	int nret=0;
	    WSADATA ws;
	    if(WSAStartup(MAKEWORD(2, 2),&ws)<0) {
	        cout << "WSA failed"<<endl;
	    } else {
	        cout << "WSA created"<<endl;
	    }
	    nsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	    srv.sin_family=AF_INET;
	       srv.sin_port=htons(PORT);
	       srv.sin_addr.s_addr=inet_addr("127.0.0.1");
	       memset(srv.sin_zero,0,8);

	      int ncon=connect(nsocket,(struct sockaddr*) &srv,sizeof(srv));
	      if(ncon<0){
	    	  cout<<"connection failed"<<endl;
	    	  WSACleanup();
	    	  exit(EXIT_FAILURE);
	      }
	      else{
	    	  cout<<"connected to the server"<<endl;
	      }
	         thread t1(receive);
	         thread t2(sendMsg);


	              t1.join();
	              t2.join();
	        while(true){

	        }
	        closesocket(nsocket);
}



