#include "Internal.hpp"
#include <Math/Rect.hpp>
#include <Math/Vec2.hpp>
#include <Util/DefaultFont.hpp>
#include <SFML/Graphics/Text.hpp>

namespace
{
	void create_default_text(void* mem)
	{
		new (mem)sf::Text("", Util::getDefaultFont());
	}

	void create_text(void* mem, const std::string& text, unsigned int size)
	{
		new (mem)sf::Text(text, Util::getDefaultFont(), size);
	}

	void destroy_text(sf::Text* mem)
	{
		mem->~Text();
	}

	void text_setString(sf::Text* text, const std::string& string)
	{
		text->setString(string);
	}

#ifndef AS_SUPPORT_VALRET
	void text_getString(asIScriptGeneric* gen)
	{
		sf::Text* text = reinterpret_cast<sf::Text*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())std::string(text->getString());
	}
	void getGlobalBounds(asIScriptGeneric* gen)
	{
		sf::Text* text = reinterpret_cast<sf::Text*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(text->getLocalBounds());
	}
	void getLocalBounds(asIScriptGeneric* gen)
	{
		sf::Text* text = reinterpret_cast<sf::Text*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(text->getLocalBounds());
	}
	void getPoint(asIScriptGeneric* gen)
	{
		sf::Text* text = reinterpret_cast<sf::Text*>(gen->GetObject());
#if defined(_M_X64) || defined(__amd64__)
		size_t id = gen->GetArgQWord(0);
#else
		size_t id = gen->GetArgDWord(0);
#endif
		new (gen->GetAddressOfReturnLocation())Math::Vec2(text->findCharacterPos(id));
	}
#else
	std::string text_getString(const sf::Text* text)
	{
		return text->getString();
	}
#endif
}

void AS_SFML::priv::text(asIScriptEngine* eng)
{
	int r;

	transformable_common<sf::Text>("Text", eng);
	drawable_common("Text", eng);

	r = eng->SetDefaultNamespace("sf::Text"); asAssert(r);

	r = eng->RegisterEnum("Style"); asAssert(r);
	r = eng->RegisterEnumValue("Style", "Regular", sf::Text::Regular); asAssert(r);
	r = eng->RegisterEnumValue("Style", "Bold", sf::Text::Bold); asAssert(r);
	r = eng->RegisterEnumValue("Style", "Italic", sf::Text::Italic); asAssert(r);
	r = eng->RegisterEnumValue("Style", "Underlined", sf::Text::Underlined); asAssert(r);
	r = eng->RegisterEnumValue("Style", "StrikeThrough", sf::Text::StrikeThrough); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	r = eng->RegisterObjectBehaviour("Text", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_text), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Text", asBEHAVE_CONSTRUCT, "void f(::string&in text, uint charsize = 30)", asFUNCTION(create_text), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Text", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_text), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("Text", "Text& opAssign(Text&in)", asMETHODPR(sf::Text, operator=, (const sf::Text&), sf::Text&), asCALL_THISCALL); asAssert(r);
	
	r = eng->RegisterObjectMethod("Text", "uint get_CharacterSize() const", asMETHOD(sf::Text, getCharacterSize), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "void set_CharacterSize(uint size)", asMETHOD(sf::Text, setCharacterSize), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "const Color& get_Color() const", asMETHOD(sf::Text, getColor), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "void set_Color(Color&in color)", asMETHOD(sf::Text, setColor), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "uint get_Style() const", asMETHOD(sf::Text, getStyle), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "void get_Style(uint style)", asMETHOD(sf::Text, setStyle), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Text", "void set_String(::string&in string)", asFUNCTION(text_setString), asCALL_CDECL_OBJFIRST); asAssert(r);
#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("Text", "::string get_String() const", asFUNCTION(text_getString), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "::Rect get_LocalBounds() const", asFUNCTION(getLocalBounds), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "::Rect get_GlobalBounds() const", asFUNCTION(getGlobalBounds), asCALL_GENERIC); asAssert(r);
#if defined(_M_X64) || defined(__amd64__)
	r = eng->RegisterObjectMethod("Text", "::Vec2 get_opIndex(uint64 id) const", asFUNCTION(getPoint), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Text", "::Vec2 get_opIndex(uint id) const", asFUNCTION(getPoint), asCALL_GENERIC); asAssert(r);
#endif
#else
	r = eng->RegisterObjectMethod("Text", "::string get_String() const", asFUNCTION(text_getString), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "::Rect get_LocalBounds() const", asMETHOD(sf::Text, getLocalBounds), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Text", "::Rect get_GlobalBounds() const", asMETHOD(sf::Text, getGlobalBounds), asCALL_THISCALL); asAssert(r);
#if defined(_M_X64) || defined(__amd64__)
	r = eng->RegisterObjectMethod("Text", "::Vec2 get_opIndex(uint64 id) const", asMETHOD(sf::Text, findCharacterPos), asCALL_THISCALL); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Text", "::Vec2 get_opIndex(uint id) const", asMETHOD(sf::Text, findCharacterPos), asCALL_THISCALL); asAssert(r);
#endif
#endif


}

void AS_SFML::priv::text(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::Text>(), "Text");
}
