#include "Avatar.h"
namespace hackTeam {
	float Avatar::getDistance(Avatar& otherAvatar)
	{
		float Xdiff;
		float Ydiff;

		Xdiff = location.x - otherAvatar.getLocation().x;
		Ydiff = location.y - otherAvatar.getLocation().y;

		return sqrt((Xdiff * Xdiff )+ (Ydiff * Ydiff));
		
	}
	hackTeam::Avatar::Avatar(string unuiqueKey) : unuiqueKey(unuiqueKey)
	{

	}

	string Avatar::getIdOfCloseOtherAvatar(unordered_map<string, Avatar> avatars)
	{
		auto itr = avatars.begin();
		float distance;

		while (itr != avatars.end()) {
			distance = getDistance(itr->second);
			if (distance <= AVATAR_RADIUS)
				return itr->first;

			itr++;
		}

		return "0";
		

	}

}
