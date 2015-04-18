#pragma once

class asIScriptEngine;
class CSerializer;

#if !(defined(__linux__) && (defined(_M_X64) || defined(__amd64__)))
#define AS_SUPPORT_VALRET
#endif

#define asAssert(r) assert(r >= 0);

namespace AS_SFML
{

	bool addSFMLExtensions(asIScriptEngine* engine);
	bool addSFMLSerializers(CSerializer* serializer);

}
