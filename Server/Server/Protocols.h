#pragma once
#include <iostream>
#include <string>
using namespace std;
namespace hackTeam {

	struct Location {
		int x;
		int y;
	};


	struct Avatar {
		Location location;
		char status;
	};


	class Protocols {
	private:

	public:
		const char Register = 'R';
		const char Available = 'A';
		const char ContactAvatar = 'C';
		const char ContactYou = 'U';
		const char NotAvailable = 'N';
		const char Locations = 'L';

		
	
		const int Index_letter = 0;
		const int Index_unuiqueId = 1;
		const int Index_locationX = 11;
		const int Index_locationY = 15;
		const int Size_Location = 4;

		const int unuiqueIdSize = 10;
		string createStringFromLocation(const Location& location){
			string x = to_string(location.x);
			string y = to_string(location.y);
			x.append(y);
			return x;
		}



		/*
	network.register ----> returns new id generated on server
	network.getAvatars -----> returns details regarding the avatars in the following format:
	 |number of entities|status|unuiqueKey|location|...

*/

	};
}


