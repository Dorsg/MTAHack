#include "NetworkManager.h"

namespace hackTeam {
	hackTeam::NetworkManager::NetworkManager()
	{

		if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			handleEror("The Office Server: Error at WSAStartup()");
		}

		mainSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (INVALID_SOCKET == mainSocket)
		{
			handleEror("Time Server: Error at socket():");
		}

		
		serverService.sin_family = AF_INET;
		serverService.sin_addr.s_addr = INADDR_ANY;
		serverService.sin_port = htons(TIME_PORT);

		if (SOCKET_ERROR == bind(mainSocket, (SOCKADDR*)&serverService, sizeof(serverService)))
		{

			string erorCode = to_string(WSAGetLastError());
			string eror;
			eror.append("Time Server : Error at bind():");
			eror.append(erorCode);
			closesocket(mainSocket);
			WSACleanup();
			return;
		}

		client_addr_len = sizeof(client_addr);

		cout << "Initialized server network.\n";

	}
	NetworkManager::~NetworkManager() {

		//Closing connections and Winsock.
		cout << "Time Server: Closing Connection.\n";
		closesocket(mainSocket);
		WSACleanup();
	}

	string NetworkManager::listen() {

		cout << "Office Server: Waiting for clients' requests.\n";
		
			bytesRecv = recvfrom(mainSocket, recvBuff, 255, 0, &client_addr, &client_addr_len);
			if (bytesRecv == SOCKET_ERROR)
			{
				closesocket(mainSocket);
				handleEror("Server: Error at recvfrom(): ");
			}

			recvBuff[bytesRecv] = '\0'; 

			string result;
			result.append(recvBuff);

			return result;
			
		

	}

	void NetworkManager::respond(string response)
	{
		strcpy(sendBuff, response.c_str()); //cpoying the strings, including the /0

		bytesSent = sendto(mainSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&client_addr, client_addr_len);
		if (bytesSent == SOCKET_ERROR)
		{
			closesocket(mainSocket);
			handleEror("Server: Error at sendto():");
		}
	}

	void NetworkManager::handleEror(string eror)
	{
		
			string erorCode = to_string(WSAGetLastError());
			eror.append(erorCode);
			WSACleanup();
			throw(eror);

		
	}

}
		

