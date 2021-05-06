#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include "Protocols.h"

#define PORT 27015
#define TIME_PORT PORT
#define CONFIRM 200






namespace hackTeam {
	

	class NetworkManager {
	private:
		
		WSAData wsaData;
		SOCKET mainSocket;
		sockaddr_in serverService;
		sockaddr client_addr;
		int client_addr_len;
		int bytesSent = 0;
		int bytesRecv = 0;
		char sendBuff[255];
		char recvBuff[255];
		
		

	public :

		NetworkManager();
		~NetworkManager();

		string listen();
		void respond(string response);
		void handleEror(string eror);
	

	};



	


	
}


