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

#ifndef AS_SUPPORT_VALRET
	void untransform_point(asIScriptGeneric* gen)
	{
		sf::View* view = reinterpret_cast<sf::View*>(gen->GetObject());
		Math::Vec2* point = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())Math::Vec2(view->getInverseTransform().transformPoint(*point));
	}
	void transform_point(asIScriptGeneric* gen)
	{
		sf::View* view = reinterpret_cast<sf::View*>(gen->GetObject());
		Math::Vec2* point = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())Math::Vec2(view->getTransform().transformPoint(*point));
	}
#else
	Math::Vec2 untransform_point(sf::View* view, const Math::Vec2& vec)
	{
		return view->getInverseTransform().transformPoint(vec);
	}
	Math::Vec2 transform_point(sf::View* view, const Math::Vec2& vec)
	{
		return view->getTransform().transformPoint(vec);
	}
#endif
}

void AS_SFML::priv::view(asIScriptEngine* eng)
{
	int r;

	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_view), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f(::Rect&in rect)", asFUNCTION(create_view_rect), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_CONSTRUCT, "void f(::Vec2&in center, ::Vec2&in size)", asFUNCTION(create_view_vals), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("View", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_view), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("View", "View& opAssign(View&in)", asMETHOD(sf::View, operator=), asCALL_THISCALL); asAssert(r);

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

#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("View", "Vec2 Transform(Vec2&in)", asFUNCTION(transform_point), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("View", "Vec2 Untransform(Vec2&in)", asFUNCTION(untransform_point), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("View", "Vec2 Transform(Vec2&in)", asFUNCTION(transform_point), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("View", "Vec2 Untransform(Vec2&in)", asFUNCTION(untransform_point), asCALL_CDECL_OBJFIRST); asAssert(r);
#endif
}

void AS_SFML::priv::view(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::View>(), "View");
}
