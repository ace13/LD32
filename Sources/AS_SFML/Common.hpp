#pragma once

class asIScriptEngine;
class CSerializer;

namespace AS_SFML
{

	extern bool addSFMLExtensions(asIScriptEngine* engine);
	extern bool addSFMLSerializers(CSerializer* serializer);

}
