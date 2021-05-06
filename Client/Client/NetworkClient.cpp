#define _CRT_SECURE_NO_WARNINGS
#include "NetworkClient.h"

using namespace std;
namespace hackTeam {

	/*Ctor and Dtor*/
	NetworkClient::NetworkClient(string& _id) : bytesSent(0), bytesRecv(0), recvBuff(new char[BUFFER_LENGTH]), sendBuff(new char[BUFFER_LENGTH]), unuiqueKey(_id)
	{
		if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			handleEror("Time Client: Error at WSAStartup()");
		}

		connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (INVALID_SOCKET == connSocket)
		{
			handleEror("Time Client: Error at socket(): ");
		}

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr("127.0.0.1");
		server.sin_port = htons(TIME_PORT);

		cout << "NetworkClient is ready" << endl;

	}
	NetworkClient:: ~NetworkClient(){

		if (recvBuff)
			delete[] recvBuff;
		if (sendBuff)
			delete[] sendBuff;
	}

	/*Private functions*/
	void NetworkClient::handleEror(string eror)
	{

		string erorCode = to_string(WSAGetLastError());
		eror.append(erorCode);
		WSACleanup();
		throw(eror);

	}
	void NetworkClient::sendAndReceiveServer(string stringToSend)
	{

		
		const char* stringC = stringToSend.c_str();
		strncpy(sendBuff, stringC, strlen(sendBuff));
		
		bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
		if (SOCKET_ERROR == bytesSent)
		{
			closesocket(connSocket);
			handleEror("Time Client: Error at sendto(): ");
		}
		
		bytesRecv = recv(connSocket, recvBuff, 255, 0);
		if (bytesRecv == SOCKET_ERROR)
		{
			closesocket(connSocket);
			handleEror("Time Client: Error at recv(): ");
		}

		recvBuff[bytesRecv] = '\0';
	}
	void NetworkClient::convertStringToAvatars(unordered_map<string, Avatar>& avatars) {
		string response;
		int numberOfAvatarsInString;
		int index = protocols.Index_numberOfObjects;

		response.append(recvBuff);
		numberOfAvatarsInString = response.at(index) - '0';//converting char to int
		response = response.substr(1, response.size()-1);


		string unuiqueKey;
		string location_x;
		string location_y;
		char status;
		//1 is for the letter
		int sizeSingleObjectString = 1 + protocols.unuiqueIdSize  + protocols.Size_Location*2 ;

		for (int i = 0; i < numberOfAvatarsInString; ++i) {

			status = response.substr((i * sizeSingleObjectString) + protocols.Index_letter, 1).at(0);
			unuiqueKey = response.substr((i* sizeSingleObjectString) +protocols.Index_unuiqueId, protocols.unuiqueIdSize);
			location_x = response.substr((i * sizeSingleObjectString) + protocols.Index_locationX, protocols.Size_Location);
			location_y = response.substr((i * sizeSingleObjectString) + protocols.Index_locationY, protocols.Size_Location);
	
			auto itr = avatars.find(unuiqueKey);
			if (itr == avatars.end())
				throw (string)"avatar was not found in avatars map";


			itr->second.location.x = stoi(location_x, 0, 10);
			itr->second.location.y = stoi(location_y, 0, 10);
			itr->second.status = status;
		}


	}
	


	/*Public functions*/
	void NetworkClient::registerAvatar(Avatar& avatar){

		string stringToSend;
		string locationInString = protocols.createStringFromLocation(avatar.location);
		
		
		stringToSend.insert(stringToSend.end(), protocols.Register);
		stringToSend.append(unuiqueKey);
		stringToSend.append(locationInString);
		sendAndReceiveServer(stringToSend);
		avatar.unuiqueKey.clear();
		avatar.unuiqueKey.append(recvBuff);
	}
	void NetworkClient::getLocations(unordered_map<string, Avatar>& avatars, const Avatar& avatar)
	{
		string stringToSend;
		string locationInString = protocols.createStringFromLocation(avatar.location);


		stringToSend.insert(stringToSend.end(), protocols.Locations);
		stringToSend.append(unuiqueKey);
		stringToSend.insert(stringToSend.end(), avatar.status);
		stringToSend.append(locationInString);
		sendAndReceiveServer(stringToSend);
		convertStringToAvatars(avatars);
	}
	void NetworkClient::makeOccupied(const Location& location)
	{
		
	}

	



	
}