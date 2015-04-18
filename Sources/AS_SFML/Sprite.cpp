#include "Internal.hpp"
#include <Math/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace
{
	void create_default_sprite(void* mem)
	{
		new (mem)sf::Sprite();
	}
	void create_sprite(void* mem, sf::Texture* texture, const Math::Rect& rect)
	{
		if (rect.width != 0 && rect.height != 0)
			new (mem)sf::Sprite(*texture, (sf::IntRect)rect);
		else
			new (mem)sf::Sprite(*texture);
	}
	void destroy_sprite(sf::Sprite* mem)
	{
		mem->~Sprite();
	}

#ifndef AS_SUPPORT_VALRET
	void getGlobalBounds(asIScriptGeneric* gen)
	{
		sf::Sprite* sprite = reinterpret_cast<sf::Sprite*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(sprite->getLocalBounds());
	}
	void getLocalBounds(asIScriptGeneric* gen)
	{
		sf::Sprite* sprite = reinterpret_cast<sf::Sprite*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(sprite->getLocalBounds());
	}
#endif
}

void AS_SFML::priv::sprite(asIScriptEngine* eng)
{
	int r;

	transformable_common<sf::Sprite>("Sprite", eng);
	drawable_common("Sprite", eng);

	r = eng->RegisterObjectBehaviour("Sprite", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_sprite), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Sprite", asBEHAVE_CONSTRUCT, "void f(Texture@, ::Rect&in = ::Rect())", asFUNCTION(create_sprite), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Sprite", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_sprite), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("Sprite", "Sprite& opAssign(Sprite&in)", asMETHODPR(sf::Sprite, operator=, (const sf::Sprite&), sf::Sprite&), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sprite", "const Texture@ GetTexture() const", asMETHOD(sf::Sprite, getTexture), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sprite", "void SetTexture(const Texture@ texture, bool reset = false)", asMETHOD(sf::Sprite, setTexture), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sprite", "const Color& get_Color() const", asMETHOD(sf::Sprite, getColor), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sprite", "void set_Color(Color&in color)", asMETHOD(sf::Sprite, setColor), asCALL_THISCALL); asAssert(r);
#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("Sprite", "::Rect get_LocalBounds() const", asFUNCTION(getLocalBounds), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Sprite", "::Rect get_GlobalBounds() const", asFUNCTION(getGlobalBounds), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Sprite", "::Rect get_LocalBounds() const", asMETHOD(sf::Sprite, getLocalBounds), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sprite", "::Rect get_GlobalBounds() const", asMETHOD(sf::Sprite, getGlobalBounds), asCALL_THISCALL); asAssert(r);
#endif

}

void AS_SFML::priv::sprite(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::Sprite>(), "Sprite");
}

