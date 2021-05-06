#pragma once
#include <string>
#include <unordered_map>
#define AVATAR_RADIUS 11

using namespace std;
namespace hackTeam {

	struct Location {
		int x;
		int y;
	};

	class Avatar {
	private:
		Location location;
		string unuiqueKey;
		char status;


		//Private functions
		float getDistance(Avatar& otherAvatar);

	public:

		//Ctor
		Avatar(string unuiqueKey);

		//getters
		Location& getLocation() { return location; }
		string getUnuiqueKey() { return unuiqueKey; }
		char getStatus(){ return status;}

		//setters
		void setLocation(Location& other) { location = other; }
		void setUnuiqueKey(string other) { unuiqueKey = other; }
		void setStatus(char other) { status = other; }

		//functions
		string getIdOfCloseOtherAvatar(unordered_map<string, Avatar> avatars);
	};
}