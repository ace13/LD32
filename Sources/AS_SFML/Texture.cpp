#include "Internal.hpp"
#include <Math/Vec2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <new>

namespace
{
#ifndef AS_SUPPORT_VALRET
	void getSize(asIScriptGeneric* gen)
	{
		sf::Texture* text = reinterpret_cast<sf::Texture*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(text->getSize());
	}
#else
	Math::Vec2 getSize(sf::Texture* text)
	{
		return text->getSize();
	}
#endif
}

void AS_SFML::priv::texture(asIScriptEngine* eng)
{
	int r;

	r = eng->SetDefaultNamespace("sf::Texture"); asAssert(r);

	r = eng->RegisterGlobalFunction("uint get_MaximumSize()", asFUNCTION(sf::Texture::getMaximumSize), asCALL_CDECL);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	r = eng->RegisterObjectMethod("Texture", "bool get_Smooth() const", asMETHOD(sf::Texture, isSmooth), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Texture", "void set_Smooth(bool smooth)", asMETHOD(sf::Texture, setSmooth), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Texture", "bool get_Repeated() const", asMETHOD(sf::Texture, isRepeated), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Texture", "void set_Repeated(bool repeat)", asMETHOD(sf::Texture, setRepeated), asCALL_THISCALL); asAssert(r);

}
