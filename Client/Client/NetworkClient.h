#pragma once
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h> 
#include <string>
#include <stdlib.h>
#include <unordered_map>
#include "Protocols.h"

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define TIME_PORT	27015
#define BUFFER_LENGTH 255

namespace hackTeam{

	

	class NetworkClient{

	private:

		
		
		WSAData wsaData;
		SOCKET connSocket;
		sockaddr_in server;
		int bytesSent = 0;
		int bytesRecv = 0;
		char* sendBuff;
		char* recvBuff;


		void sendAndReceiveServer(string stringToSend);
		void convertStringToAvatars(unordered_map<string, Avatar>& avatars);
		void handleEror(string eror);


	public:
		Protocols protocols;
		string unuiqueKey; //this object contains the id since it's always being used.
		NetworkClient(string _id);
		~NetworkClient();

		//posts
		void registerAvatar(Avatar& avatar);
		void contactAvatar(const string& avatarToContact, Location& location);
		void makeAvailable(const Location& location);
		void makeOccupied(const Location& location);
		


		//gets
		void getLocations(unordered_map<string, Avatar>& avatars, Avatar& avatar);



		string getLastResponse() { return recvBuff; }

		
		


		
		

	};

}
