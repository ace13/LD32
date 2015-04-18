#include "Internal.hpp"
#include <SFML/Graphics/Color.hpp>
#include <new>

// Constructors / Destructors
namespace
{
	void create_color(void* mem) { new (mem)sf::Color; }
	void create_color_val(void* mem, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) { new (mem)sf::Color(r, g, b, a); }
	void create_color_copy(void* mem, const sf::Color& copy) { new (mem)sf::Color(copy); }
	void destroy_color(sf::Color* mem) { mem->~Color(); }

#ifndef AS_SUPPORT_VALRET
	void color_add(asIScriptGeneric* gen)
	{
		sf::Color& lhs = *reinterpret_cast<sf::Color*>(gen->GetObject());
		sf::Color& rhs = *reinterpret_cast<sf::Color*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())sf::Color(lhs + rhs);
	}
	void color_sub(asIScriptGeneric* gen)
	{
		sf::Color& lhs = *reinterpret_cast<sf::Color*>(gen->GetObject());
		sf::Color& rhs = *reinterpret_cast<sf::Color*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())sf::Color(lhs - rhs);
	}
	void color_mul(asIScriptGeneric* gen)
	{
		sf::Color& lhs = *reinterpret_cast<sf::Color*>(gen->GetObject());
		sf::Color& rhs = *reinterpret_cast<sf::Color*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())sf::Color(lhs * rhs);
	}
#endif
}

void AS_SFML::priv::color(asIScriptEngine* eng)
{
	int r;
	r = eng->RegisterObjectProperty("Color", "uint8 R", asOFFSET(sf::Color, r)); asAssert(r);
	r = eng->RegisterObjectProperty("Color", "uint8 G", asOFFSET(sf::Color, g)); asAssert(r);
	r = eng->RegisterObjectProperty("Color", "uint8 B", asOFFSET(sf::Color, b)); asAssert(r);
	r = eng->RegisterObjectProperty("Color", "uint8 A", asOFFSET(sf::Color, a)); asAssert(r);

	r = eng->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_color), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(uint8 r, uint8 g, uint8 b, uint8 a = 255)", asFUNCTION(create_color_val), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(Color&in)", asFUNCTION(create_color_copy), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Color", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_color), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("Color", "Color& opAssign(Color&in)", asMETHODPR(sf::Color, operator=, (const sf::Color&), sf::Color&), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color& opAddAssign(Color&in)", asFUNCTIONPR(sf::operator+=, (sf::Color&, const sf::Color&), sf::Color&), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color& opSubAssign(Color&in)", asFUNCTIONPR(sf::operator-=, (sf::Color&, const sf::Color&), sf::Color&), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color& opMulAssign(Color&in)", asFUNCTIONPR(sf::operator*=, (sf::Color&, const sf::Color&), sf::Color&), asCALL_CDECL_OBJFIRST); asAssert(r);
	
#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("Color", "Color opAdd(Color&in) const", asFUNCTION(color_add), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color opSub(Color&in) const", asFUNCTION(color_sub), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color opMul(Color&in) const", asFUNCTION(color_mul), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Color", "Color opAdd(Color&in) const", asFUNCTIONPR(sf::operator+, (const sf::Color&, const sf::Color&), sf::Color), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color opSub(Color&in) const", asFUNCTIONPR(sf::operator-, (const sf::Color&, const sf::Color&), sf::Color), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Color", "Color opMul(Color&in) const", asFUNCTIONPR(sf::operator*, (const sf::Color&, const sf::Color&), sf::Color), asCALL_CDECL_OBJFIRST); asAssert(r);
#endif

	r = eng->RegisterObjectMethod("Color", "bool opEquals(Color&in) const", asFUNCTIONPR(sf::operator==, (const sf::Color&, const sf::Color&), bool), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->SetDefaultNamespace("sf::Colors"); asAssert(r);

	r = eng->RegisterGlobalProperty("const Color Black", const_cast<sf::Color*>(&sf::Color::Black)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Blue", const_cast<sf::Color*>(&sf::Color::Blue)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Cyan", const_cast<sf::Color*>(&sf::Color::Cyan)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Green", const_cast<sf::Color*>(&sf::Color::Green)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Magenta", const_cast<sf::Color*>(&sf::Color::Magenta)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Red", const_cast<sf::Color*>(&sf::Color::Red)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Transparent", const_cast<sf::Color*>(&sf::Color::Transparent)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color White", const_cast<sf::Color*>(&sf::Color::White)); asAssert(r);
	r = eng->RegisterGlobalProperty("const Color Yellow", const_cast<sf::Color*>(&sf::Color::Yellow)); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);
}

void AS_SFML::priv::color(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::Color>(), "sf::Color");
}
