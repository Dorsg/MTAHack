#pragma once
#include <iostream>
#include <string>
#include "Avatar.h"


using namespace std;
namespace hackTeam {

	


	

	class Protocols{
	private:

	public:
		char Register = 'R';
		char Available = 'A';
		char ContactAvatar = 'C';
		char ContactYou = 'U';
		char NotAvailable = 'N';
		char Locations = 'L';

		int Index_numberOfObjects = 0;
		int Index_letter = 0;
		int Index_unuiqueId = 1;
		int Index_locationX = 11;
		int Index_locationY = 15;
		const int Size_Location = 4;

		const int unuiqueIdSize = 10;
		string createStringFromLocation(Location& location){
			string x = to_string(location.x);
			string y = to_string(location.y);
			x.append(y);
			return x;
		}
		
	};

	/*
network.register ----> returns new id generated on server
network.getAvatars -----> returns details regarding the avatars in the following format:
 |number of entities|status|unuiqueKey|location|...
	*/
}
