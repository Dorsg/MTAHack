#include "Data.h"

using namespace std;
namespace hackTeam {

	/*Ctor and Dtor*/


	/*Private functions*/


	/*Public functions*/
	string Data::addAvatar(Location& location)
	{
		string id = generateUnuiqueId();
		Avatar avatar;
		avatar.location = location;
		avatar.status = 'A';
		avatars.insert({ id, avatar});
		return id;
	}
	void Data::deleteAvatar(string id)
	{
		auto itr = avatars.find(id);
		avatars.erase(itr);
	}
	void Data::updateLocation(string id, Location newLocation)
	{
		auto itr = avatars.find(id);
		itr->second.location = newLocation;
	}
	void Data::updateStatus(string id, char newStatus)
	{
		auto itr = avatars.find(id);
		itr->second.status = newStatus;
	}
	string Data::generateUnuiqueId()
	{
		string res = to_string(avatars.size() + 1);
		int digitsToAdd = protocols.unuiqueIdSize - res.length();

		for (int i = 0; i < digitsToAdd; ++i) {
			res.append("0");
		}

		return res;
	}
	void Data::displayAvatarsStatus()
	{
		cout << "Displaying Avatars Status:" << endl;
		cout << "======================================================" << endl;
		cout << "|id          |X          |Y          |Status          " << endl;
		auto itr = avatars.begin();

		while (itr != avatars.end()) {
			cout << itr->first<<"     " << itr->second.location.x <<"     "<< itr->second.location.y <<"     "<< itr->second.status << endl;
			++itr;
		}

		
	}
	string Data::getAllAvatarsInString(){
		string res;
		res.append(to_string(avatars.size()));

		auto itr = avatars.begin();

		while (itr != avatars.end()){
			res.push_back(itr->second.status);
			res.append(itr->first);
			string location = protocols.createStringFromLocation(itr->second.location);
			res.append(location);
			++itr;
		}

		return res;

	}
}