#include "Internal.hpp"
#include <Math/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <new>

namespace
{
	void create_view(void* mem) { new (mem)sf::View(); }
	void create_view_rect(void* mem, const Math::Rect& rect) { new (mem)sf::View(rect); }
	void create_view_vals(void* mem, const Math::Vec2& center, const Math::Vec2& size) { new (mem)sf::View(center, size); }
	void destroy_view(sf::View* mem) { mem->~View(); }
}

void AS_SFML::priv::view(asIScriptEngine* eng)
{
	int r;

	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_view), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f(::Rect&in rect)", asFUNCTION(create_view_rect), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f(::Vec2&in center, ::Vec2&in size)", asFUNCTION(create_view_vals), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_view), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("View", "::Vec2& get_Center() const", asMETHOD(sf::View, getCenter), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "float get_Rotation() const", asMETHOD(sf::View, getRotation), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "::Vec2& get_Size() const", asMETHOD(sf::View, getSize), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "::Rect& get_Viewport() const", asMETHOD(sf::View, getViewport), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void set_Center(::Vec2&in center)", asMETHODPR(sf::View, setCenter, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void set_Rotation(float angle)", asMETHOD(sf::View, setRotation), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void set_Size(::Vec2&in center)", asMETHODPR(sf::View, setSize, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void set_Viewport(::Rect&in center)", asMETHOD(sf::View, setViewport), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("View", "void Move(::Vec2&in offset)", asMETHODPR(sf::View, move, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void Rotate(float angle)", asMETHOD(sf::View, rotate), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("View", "void Zoom(float factor)", asMETHOD(sf::View, zoom), asCALL_THISCALL); asAssert(r);
}

void AS_SFML::priv::view(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::View>(), "sf::View");
}
