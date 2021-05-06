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
#include "Avatar.h"


using namespace hackTeam;

void main()
{

	unordered_map<string, Avatar> avatars;
	//לעבור על כל המיקומים ולראות אם יש מישהו קרוב אליי
	//חוץ מעצמי


	Avatar Adam("0000000000");
	Location location;
	location.x = 4444;
	location.y = 3333;

	Adam.setLocation(location);
	Adam.setStatus('A');
	
	
	NetworkClient network(Adam.getUnuiqueKey());
	

	network.registerAvatar(Adam);
	avatars.insert({ Adam.getUnuiqueKey(),Adam });
	network.getLocations(avatars,Adam);

	char c = 1;

	

	while (1){
		Avatar& current = avatars.find(Adam.getUnuiqueKey())->second;
		Location oldLocation = current.getLocation();
		oldLocation.x += 10;
		oldLocation.y += 10;

		current.setLocation(oldLocation);

		network.getLocations(avatars, current);
		Sleep(1000);




		//cout << "This is the unuique key we received from the server" << Adam.getUnuiqueKey() << endl;

		cout << "Displaying Avatars Status:" << endl;
		cout << "======================================================" << endl;
		cout << "|id          |X          |Y          |Status          " << endl;
		auto itr = avatars.begin();

		while (itr != avatars.end()) {
			cout << itr->first << "     " << itr->second.getLocation().x << "     " << itr->second.getLocation().y << "     " << itr->second.getStatus() << endl;
			++itr;
		}

	}







	




	
}