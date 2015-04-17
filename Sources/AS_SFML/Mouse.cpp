#include "Internal.hpp"
#include <GameClass.hpp>
#include <Math/Vec2.hpp>
#include <SFML/Window/Mouse.hpp>

#ifndef AS_SUPPORT_VALRET
void getMousePos(asIScriptGeneric* gen)
{
	new (gen->GetAddressOfReturnLocation()) Math::Vec2(GameClass::Singleton().getWindow().mapPixelToCoords(sf::Mouse::getPosition(GameClass::Singleton().getWindow())));
}
#else
Math::Vec2 getMousePos()
{
	return sf::Mouse::getPosition(GameClass::Singleton().getWindow());
}
#endif

void AS_SFML::priv::mouse(asIScriptEngine* eng)
{
	int r;

	r = eng->SetDefaultNamespace("sf::Mouse"); asAssert(r);

#define B(Val) eng->RegisterEnumValue("Button", #Val, sf::Mouse:: ## Val)
	r = eng->RegisterEnum("Button"); asAssert(r);
	r = B(Left); asAssert(r);
	r = B(Right); asAssert(r);
	r = B(Middle); asAssert(r);
	r = B(XButton1); asAssert(r);
	r = B(XButton2); asAssert(r);
#undef B

#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterGlobalFunction("Vec2 get_Position()", asFUNCTION(getMousePos), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterGlobalFunction("Vec2 get_Position()", asFUNCTION(getMousePos), asCALL_CDECL); asAssert(r);
#endif

	r = eng->RegisterGlobalFunction("bool IsPressed(Button button)", asFUNCTION(sf::Mouse::isButtonPressed), asCALL_CDECL); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);
}
