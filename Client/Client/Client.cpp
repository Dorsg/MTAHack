#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include "NetworkClient.h"


using namespace hackTeam;

void main()
{



	unordered_map<string, Avatar> avatars;
	//unordered_map<Location, string> avatarsLocations;


	Avatar Adam;
	Adam.location.x = 4444;
	Adam.location.y = 3333;
	Adam.status = 'A';
	Adam.unuiqueKey = "0000000000";

	
	
	NetworkClient network(Adam.unuiqueKey);
	

	network.registerAvatar(Adam);
	avatars.insert({ Adam.unuiqueKey,Adam });
	network.getLocations(avatars,Adam);

	char c = 1;

	Avatar& current = avatars.find(Adam.unuiqueKey)->second;

	while (1) {

		
		
			current.location.x -= 10;		
		
			current.location.y += 10;
		
		network.getLocations(avatars, current);
		Sleep(1000);




		cout << "This is the unuique key we received from the server" << Adam.unuiqueKey << endl;

		cout << "Displaying Avatars Status:" << endl;
		cout << "======================================================" << endl;
		cout << "|id          |X          |Y          |Status          " << endl;
		auto itr = avatars.begin();

		while (itr != avatars.end()) {
			cout << itr->first << "     " << itr->second.location.x << "     " << itr->second.location.y << "     " << itr->second.status << endl;
			++itr;
		}

	}







	




	
}