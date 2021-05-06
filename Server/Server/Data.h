#pragma once
#include <iostream>
#include <iomanip>  
#include <string>
#include <unordered_map>
#include "Protocols.h"



using namespace std;

struct Location {
	float x = 0;
	float y = 0;
	string status;

	//A לא זמין
	//B מבקש ליצור קשר
	//C מבקשים ליצור איתך קשר
	//D לא זמין
};

namespace hackTeam {
	class Data {
	private:
		
		Protocols protocols;
		unordered_map<string, Avatar> avatars; // key is the id

		/*Private functions*/

	public:

		/*Ctor and Dtor*/
		Data(){}
		

		/*Public functions*/
		string addAvatar(Location& location);
		Avatar getAvatarByUnuiqueKey(string unuiqueKey) {return avatars.at(unuiqueKey);}
		void deleteAvatar(string id);
		void updateLocation(string id,  Location newLocation);
		void updateStatus(string id, char newStatus);
		string generateUnuiqueId();
		void displayAvatarsStatus();
		string getAllAvatarsInString();
		
		
	};

	
}
