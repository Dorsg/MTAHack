#include "AppManager.h"

namespace hackTeam {
	
	/*Ctor and Dtor*/

	/*Private functions*/
	Location AppManager::extractLocationFromString(string request)
	{

		Location location;
		string valueOfXInString = request.substr(protocols.Index_locationX, protocols.Size_Location);
		string valueOfYInString = request.substr(protocols.Index_locationY, protocols.Size_Location);

		location.x = stoi(request.substr(protocols.Index_locationX, protocols.Size_Location), 0, 10);
		location.y = stoi(request.substr(protocols.Index_locationY, protocols.Size_Location), 0, 10);


		return location;
	}
	void AppManager::handleRegister(string request)
	{
		Location location = extractLocationFromString(request);
		string unuiqueId = data.addAvatar(location);

		network.respond(unuiqueId); //provide the client the id if the new avatar
	}
	void AppManager::handleLocations(string request)
	{
		string response = data.getAllAvatarsInString();
		network.respond(response);
	}

	


	/*Public functions*/
	void AppManager::run() {

		data.displayAvatarsStatus();
		while (true) {

			string request = network.listen();
			cout << "received: " << request << endl;
			handleRequest(request);

		}
	}
	void AppManager::handleRequest(string request)
	{

		const char flag = request.at(protocols.Index_letter);

		if (flag == protocols.Register) {
			handleRegister(request);
		}

		else if (flag == protocols.ContactAvatar) {

		}

		else if (flag == protocols.ContactYou) {
			//irelevant
		}

		else if (flag == protocols.Locations) {
			handleLocations(request);

		}

		//test
		data.displayAvatarsStatus();
		//
	}
	
}