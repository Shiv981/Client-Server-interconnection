/*
 * client.cpp
 *
 *  Created on: 18-Aug-2023
 *      Author: Shiv Pathak
 */



#include <bits/stdc++.h>
#include <winsock2.h>
#define PORT 9909
using namespace std;
struct sockaddr_in srv;

int main(){
	int nret=0;
	    WSADATA ws;
	    if(WSAStartup(MAKEWORD(2, 2),&ws)<0) {
	        cout << "WSA failed"<<endl;
	    } else {
	        cout << "WSA created"<<endl;
	    }
	    int nsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
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

}




