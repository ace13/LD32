#include "ScriptExtensions.hpp"

#include <Math/Rect.hpp>
#include <Math/Vec2.hpp>

#include <angelscript.h>
#include <scriptarray/scriptarray.h>
#include <scriptdictionary/scriptdictionary.h>
#include <scriptmath/scriptmath.h>
#include <scriptmath/scriptmathcomplex.h>
#include <scriptstdstring/scriptstdstring.h>

#include <cassert>
#include <new>

namespace
{
	void as_addons(asIScriptEngine* eng)
	{
		RegisterScriptArray(eng, true);
		RegisterScriptMath(eng);
		RegisterScriptMathComplex(eng);
		RegisterStdString(eng);
		RegisterStdStringUtils(eng);
		RegisterScriptDictionary(eng);
	}

#ifndef AS_SUPPORT_VALRET
	void rect_getCenter(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->getCenter());
	}
	void rect_getSize(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->getSize());
	}
	void rect_capture(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		Math::Vec2* capture = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->capture(*capture));
	}
#endif

	void rect_create(void* mem, float top, float left, float width, float height)
	{
		new (mem)Math::Rect(top, left, width, height);
	}
	void rect_create_vec(void* mem, const Math::Vec2& pos, const Math::Vec2& size)
	{
		new (mem)Math::Rect(pos, size);
	}
	void rect_destroy(Math::Rect* mem)
	{
		mem->~Rect();
	}

	void rect(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float top = 0, float left = 0, float width = 0, float height = 0)", asFUNCTION(rect_create), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(Vec2&in,Vec2&in)", asFUNCTION(rect_create_vec), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(rect_destroy), asCALL_CDECL_OBJFIRST); asAssert(r);

		r = eng->RegisterObjectMethod("Rect", "bool opEquals(Rect&in rhs) const", asFUNCTIONPR(sf::operator==, (const sf::FloatRect&, const sf::FloatRect&), bool), asCALL_CDECL_OBJFIRST); asAssert(r);

		r = eng->RegisterObjectProperty("Rect", "float Top", asOFFSET(Math::Rect, top)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Left", asOFFSET(Math::Rect, left)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Width", asOFFSET(Math::Rect, width)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Height", asOFFSET(Math::Rect, height)); asAssert(r);

		r = eng->RegisterObjectMethod("Rect", "void set_Center(Vec2&in center)", asMETHOD(Math::Rect, setCenter), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "void set_Size(Vec2&in size)", asMETHOD(Math::Rect, setSize), asCALL_THISCALL); asAssert(r);
#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Center() const", asFUNCTION(rect_getCenter), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Size() const", asFUNCTION(rect_getSize), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 Capture(Vec2&in toGrab)", asFUNCTION(rect_capture), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Center() const", asMETHOD(Math::Rect, getCenter), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Size() const", asMETHOD(Math::Rect, getSize), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 Capture(Vec2&in toGrab)", asMETHOD(Math::Rect, capture), asCALL_THISCALL); asAssert(r);
#endif

		r = eng->RegisterObjectMethod("Rect", "bool Contains(Vec2&in point) const", asMETHODPR(Math::Rect, contains, (const sf::Vector2f&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "bool Intersects(Rect&in rect) const", asMETHODPR(Math::Rect, intersects, (const sf::FloatRect&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "bool Intersects(Rect&in rect, Rect&out) const", asMETHODPR(Math::Rect, intersects, (const sf::FloatRect&, sf::FloatRect&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "void Move(Vec2&in offset)", asMETHOD(Math::Rect, move), asCALL_THISCALL); asAssert(r);
	}

#ifndef AS_SUPPORT_VALRET
	void vec2_getNormalized(asIScriptGeneric* gen)
	{
		Math::Vec2* vec = reinterpret_cast<Math::Vec2*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(vec->getNormalized());
	}
	void vec2_getRotated(asIScriptGeneric* gen)
	{
		Math::Vec2* vec = reinterpret_cast<Math::Vec2*>(gen->GetObject());
		float ang = gen->GetArgFloat(0);
		new (gen->GetAddressOfReturnLocation())Math::Vec2(vec->getRotated(ang));
	}
#endif

	void vec2(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectProperty("Vec2", "float X", asOFFSET(Math::Vec2, x)); asAssert(r);
		r = eng->RegisterObjectProperty("Vec2", "float Y", asOFFSET(Math::Vec2, y)); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "float get_Angle() const", asMETHOD(Math::Vec2, getAngle), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float get_Length() const", asMETHOD(Math::Vec2, getLength), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float get_LengthSquared() const", asMETHOD(Math::Vec2, getLengthSquared), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void set_Angle(float ang)", asMETHOD(Math::Vec2, setAngle), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void set_Length(float ang)", asMETHOD(Math::Vec2, setLength), asCALL_THISCALL); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "float Bearing(Vec2&in) const", asMETHOD(Math::Vec2, getBearing), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float Distance(Vec2&in) const", asMETHOD(Math::Vec2, getDistance), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float DistanceSquared(Vec2&in) const", asMETHOD(Math::Vec2, getDistanceSquared), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float Dot(Vec2&in) const", asMETHOD(Math::Vec2, getDot), asCALL_THISCALL); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "void Normalize()", asMETHOD(Math::Vec2, normalize), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void Rotate(float ang)", asMETHOD(Math::Vec2, rotate), asCALL_THISCALL); asAssert(r);
		
#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod("Vec2", "Vec2 get_Normalized() const", asFUNCTION(vec2_getNormalized), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 Rotated(float ang)", asFUNCTION(vec2_getRotated), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod("Vec2", "Vec2 get_Normalized() const", asMETHOD(Math::Vec2, getNormalized), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 Rotated(float ang)", asMETHOD(Math::Vec2, getRotated), asCALL_THISCALL); asAssert(r);
#endif
	}

	void math(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectType("Rect", sizeof(Math::Rect), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Math::Rect>()); asAssert(r);
		r = eng->RegisterObjectType("Vec2", sizeof(Math::Vec2), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Math::Vec2>()); asAssert(r);

		rect(eng);
		vec2(eng);
	}
}

void Game::addGeneralScriptExtensions(asIScriptEngine* eng)
{
	as_addons(eng);
	math(eng);
}
