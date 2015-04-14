#include "Common.hpp"
#include "Internal.hpp"
#include <Util/DefaultFont.hpp>

#include <SFML/Graphics.hpp>

void registerTypes(asIScriptEngine*);

bool AS_SFML::addSFMLExtensions(asIScriptEngine* engine)
{
	typedef void(*regfunc)(asIScriptEngine*);
	regfunc parts[] = {
		registerTypes, priv::color, priv::joystick, priv::keyboard,
		priv::mouse, priv::music, priv::rendertarget, priv::shader,
		priv::shapes, priv::sound, priv::sprite, priv::text,
		priv::texture, priv::view
	};

	engine->SetDefaultNamespace("sf");
	for (auto& func : parts)
		func(engine);

	engine->SetDefaultNamespace("");
	return true;
}

bool AS_SFML::addSFMLSerializers(CSerializer* serializer)
{
	typedef void(*regfunc)(CSerializer*);
	regfunc parts[] = {
		priv::color, priv::joystick, priv::shapes, priv::sprite,
		priv::text, priv::view
	};

	for (auto& func : parts)
		func(serializer);

	return true;
}

namespace
{
	sf::Font* getDefaultFontPtr()
	{
		return &Util::getDefaultFont();
	}
}

void registerTypes(asIScriptEngine* eng)
{
	int r;

	r = eng->RegisterObjectType("Color", sizeof(sf::Color), asOBJ_VALUE | asGetTypeTraits<sf::Color>()); asAssert(r);
	r = eng->RegisterObjectType("Font", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("Music", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("Renderer", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("Shader", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("Sound", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("Sprite", sizeof(sf::Sprite), asOBJ_VALUE | asGetTypeTraits<sf::Sprite>()); asAssert(r);
	r = eng->RegisterObjectType("Text", sizeof(sf::Text), asOBJ_VALUE | asGetTypeTraits<sf::Text>()); asAssert(r);
	r = eng->RegisterObjectType("Texture", 0, asOBJ_REF | asOBJ_NOCOUNT); asAssert(r);
	r = eng->RegisterObjectType("View", sizeof(sf::View), asOBJ_VALUE | asGetTypeTraits<sf::View>()); asAssert(r);

	r = eng->SetDefaultNamespace("sf::Shapes"); asAssert(r);

	r = eng->RegisterObjectType("Circle", sizeof(sf::CircleShape), asOBJ_VALUE | asGetTypeTraits<sf::CircleShape>()); asAssert(r);
	r = eng->RegisterObjectType("Convex", sizeof(sf::ConvexShape), asOBJ_VALUE | asGetTypeTraits<sf::ConvexShape>()); asAssert(r);
	r = eng->RegisterObjectType("Rectangle", sizeof(sf::RectangleShape), asOBJ_VALUE | asGetTypeTraits<sf::RectangleShape>()); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	r = eng->RegisterGlobalFunction("Font@ get_DefaultFont()", asFUNCTION(getDefaultFontPtr), asCALL_CDECL); asAssert(r);
}
