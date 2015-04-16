#pragma once

#include <AS_SFML/Common.hpp>

class CSerializer;

namespace Game
{

	extern void addGeneralScriptExtensions(asIScriptEngine* eng);
	extern void addGeneralSerializerTypes(CSerializer* serial);

}
