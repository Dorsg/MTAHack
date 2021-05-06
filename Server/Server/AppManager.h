#pragma once
#include "NetworkManager.h"
#include "Data.h"

namespace hackTeam {
	class AppManager {
	private:
		Protocols protocols;
		NetworkManager network;
		Data data;


		/*Private functions*/
		Location extractLocationFromString(string request);
		void handleRegister(string request);
		void handleLocations(string request);


	public:
		/*Ctor and Dtor*/


		/*Public functions*/
		void run();
		void handleRequest(string request);
		
	};
}