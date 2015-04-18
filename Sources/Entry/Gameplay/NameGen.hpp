#pragma once

#include <string>

namespace Gameplay
{

	class Namegen
	{
	public:
		// Typical tumblr-idiot-esque name
		// Examples:
		//
		// stuckwithharrypottertilltheend
		// polished-trophy-pretty-whore
		// seeminglydeepstatement
		// unconventionalmoose
		// theyellowbrickroad
		// feathersmcstrange
		// chickensandwich
		// deathbedscene
		//
		static std::string getTypicalName();

		// Boss name, slightly smarter, with a title;
		//
		//  M.D. - Master Debater
		//  C.L. - Cunning Linguist
		//  etc..
		//
		static std::string getBossName();

	private:
		Namegen();
	};

}
