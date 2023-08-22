/*
 * server.cpp
 *
 *  Created on: 22-Aug-2023
 *      Author: Shiv Pathak
 */
/*
 * server.cpp
 *
 *  Created on: 22-Aug-2023
 *      Author: Shiv Pathak
 */
/*
 * server.cpp
 *
 *  Created on: 22-Aug-2023
 *      Author: Shiv Pathak
 */

/*
 * server.cpp
 *
 *  Created on: 21-Aug-2023
 *      Author: Shiv Pathak
 */

#include <bits/stdc++.h>
#include <winsock2.h>
#define PORT 9998
using namespace std;
struct sockaddr_in srv;
fd_set fr,fw,fe;
int main() {
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        cout << "WSA failed"<<endl;
        return 1;
    } else {
        cout << "WSA created"<<endl;
    }

    int nsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(srv.sin_zero, 0, sizeof(srv.sin_zero));
    //setsockopt
    int noptval=0;
    int noptlen=sizeof(noptval);
    int socksec = setsockopt(nsocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&noptval, noptlen);
    if(!socksec){
    	cout<<"setsockopt call successfully"<<endl;
    }
    else{
    	       cout<<"setsockopt call successfully"<<endl;
    			WSACleanup();
    	        exit(EXIT_FAILURE);
    }
    //blocking nonblocking
    u_long optval=0;
    int nblock=ioctlsocket(nsocket,FIONBIO,&optval);
    if(nblock==0){
    	cout<<"ioctlsocket call passed"<<endl;
    }
    else{
    	cout<<"ioctlsocket call failed"<<endl;
    }

    int nret=bind(nsocket,(sockaddr*)&srv,sizeof(sockaddr));
    if(nret<0){
    	cout<<"not bind successfully"<<endl;
    }
    else{
    	cout<<"bind successfully"<<endl;
    }
     int lisreq=listen(nsocket,5);
     if(lisreq<0){
    	 cout<<"listen not successful"<<endl;
     }
     else{
    	 cout<<"listen successful"<<endl;
     }

     struct sockaddr_in client;
    int nlen=sizeof(client);

    int nclient=accept(nsocket,(struct sockaddr*)&client,&nlen);

    if(nclient<0){
    	cout<<"failed to connect"<<endl;
    }
    else{
    	cout<<"connected to the client successfully"<<endl;
    }
    while(true){
   char sbuff[1024]={ 0, };
   int rev=recv(nclient,sbuff,1024,0);
   if(rev>0){
           cout<<sbuff<<endl;    //show the msg from client
           cout << "Server : "<<endl;
           			char input[1000];
           			string s;
           			getline(cin , s);
           			int n = s.size();
           			for(int i = 0 ; i < n ; i++)
                                    {
           				input[i] = s[i];
           			}

           			input[n] = '\0';

           			send(nclient , input , strlen(input)+1 , 0);
           		}
    }
    closesocket(nclient);
    nclient=0;
}














