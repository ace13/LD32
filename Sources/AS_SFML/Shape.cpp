#include "Internal.hpp"
#include <Math/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdio>

namespace
{
#ifndef AS_SUPPORT_VALRET
	void getGlobalBounds(asIScriptGeneric* gen)
	{
		sf::Shape* shape = reinterpret_cast<sf::Shape*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(shape->getLocalBounds());
	}
	void getLocalBounds(asIScriptGeneric* gen)
	{
		sf::Shape* shape = reinterpret_cast<sf::Shape*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Rect(shape->getLocalBounds());
	}
	void getPoint(asIScriptGeneric* gen)
	{
		sf::Shape* shape = reinterpret_cast<sf::Shape*>(gen->GetObject());
		unsigned int id = gen->GetArgDWord(0);
		new (gen->GetAddressOfReturnLocation())Math::Vec2(shape->getPoint(id));
	}
#endif

	void shape_common(const char* name, asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectMethod(name, "const Color& get_FillColor() const", asMETHOD(sf::Shape, getFillColor), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "void set_FillColor(Color&in color)", asMETHOD(sf::Shape, setFillColor), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "const Color& get_OutlineColor() const", asMETHOD(sf::Shape, getOutlineColor), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "void set_OutlineColor(Color&in color)", asMETHOD(sf::Shape, setOutlineColor), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "float get_OutlineThickness() const", asMETHOD(sf::Shape, getOutlineThickness), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "void set_OutlineThickness(float size)", asMETHOD(sf::Shape, setOutlineThickness), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "uint get_PointCount() const", asMETHOD(sf::Shape, getPointCount), asCALL_THISCALL); asAssert(r);
		
		r = eng->RegisterObjectMethod(name, "const Texture@ GetTexture() const", asMETHOD(sf::Shape, getTexture), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "void SetTexture(const Texture@ texture, bool reset = false)", asMETHOD(sf::Shape, setTexture), asCALL_THISCALL); asAssert(r);

#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod(name, "::Rect get_LocalBounds() const", asFUNCTION(getLocalBounds), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod(name, "::Rect get_GlobalBounds() const", asFUNCTION(getGlobalBounds), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod(name, "::Vec2 get_opIndex(uint id) const", asFUNCTION(getPoint), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod(name, "::Rect get_LocalBounds() const", asMETHOD(sf::Shape, getLocalBounds), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "::Rect get_GlobalBounds() const", asMETHOD(sf::Shape, getGlobalBounds), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod(name, "::Vec2 get_opIndex(uint id) const", asMETHOD(sf::Shape, getPoint), asCALL_THISCALL); asAssert(r);
#endif

	}

	void draw_common(sf::RenderTarget* rt, const sf::Drawable& draw)
	{
		rt->draw(draw);
	}

	void draw_shader(sf::RenderTarget* rt, const sf::Drawable& draw, const sf::Shader* shader)
	{
		rt->draw(draw, shader);
	}

	void create_default_circle(void* mem)
	{
		new (mem)sf::CircleShape();
	}
	void create_circle(void* mem, float rad, unsigned int points)
	{
		new (mem)sf::CircleShape(rad, points);
	}
	void destroy_circle(sf::CircleShape* mem)
	{
		mem->~CircleShape();
	}

	void create_default_convex(void* mem)
	{
		new (mem)sf::ConvexShape();
	}
	void create_convex(void* mem, unsigned int points)
	{
		new (mem)sf::ConvexShape(points);
	}
	void destroy_convex(sf::ConvexShape* mem)
	{
		mem->~ConvexShape();
	}

	void create_default_rectangle(void* mem)
	{
		new (mem)sf::RectangleShape();
	}
	void create_rectangle(void* mem, const Math::Vec2& size)
	{
		new (mem)sf::RectangleShape(size);
	}
	void destroy_rectangle(sf::RectangleShape* mem)
	{
		mem->~RectangleShape();
	}

}

void AS_SFML::priv::shapes(asIScriptEngine* eng)
{
	int r;

	r = eng->SetDefaultNamespace("sf::Shapes"); asAssert(r);

	const char* shapes[] = {
		"Circle", "Convex", "Rectangle"
	};
	
	transformable_common<sf::CircleShape>("Circle", eng);
	transformable_common<sf::ConvexShape>("Convex", eng);
	transformable_common<sf::RectangleShape>("Rectangle", eng);

	for (auto shape : shapes)
	{
		drawable_common(shape, eng);
		shape_common(shape, eng);
	}

	r = eng->RegisterObjectBehaviour("Circle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_circle), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Circle", asBEHAVE_CONSTRUCT, "void f(float radius = 0, uint points = 30)", asFUNCTION(create_circle), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Circle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_circle), asCALL_CDECL_OBJFIRST);
	r = eng->RegisterObjectMethod("Circle", "Circle& opAssign(Circle&in)", asMETHODPR(sf::CircleShape, operator=, (const sf::CircleShape&), sf::CircleShape&), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Circle", "float get_Radius() const", asMETHOD(sf::CircleShape, getRadius), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Circle", "void set_Radius(float radius)", asMETHOD(sf::CircleShape, setRadius), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Circle", "void set_PointCount(uint count)", asMETHOD(sf::CircleShape, setPointCount), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectBehaviour("Convex", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_convex), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Convex", asBEHAVE_CONSTRUCT, "void f(uint points = 0)", asFUNCTION(create_convex), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Convex", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_convex), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Convex", "Convex& opAssign(Convex&in)", asMETHODPR(sf::ConvexShape, operator=, (const sf::ConvexShape&), sf::ConvexShape&), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Convex", "void set_PointCount(uint count)", asMETHOD(sf::ConvexShape, setPointCount), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Convex", "void set_opIndex(uint id, ::Vec2&in point)", asMETHOD(sf::ConvexShape, setPoint), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectBehaviour("Rectangle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_rectangle), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Rectangle", asBEHAVE_CONSTRUCT, "void f(::Vec2&in size = ::Vec2())", asFUNCTION(create_rectangle), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Rectangle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_rectangle), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Rectangle", "Rectangle& opAssign(Rectangle&in)", asMETHODPR(sf::RectangleShape, operator=, (const sf::RectangleShape&), sf::RectangleShape&), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Rectangle", "const ::Vec2& get_Size()", asMETHOD(sf::RectangleShape, getSize), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Rectangle", "void set_Size(::Vec2&in size)", asMETHOD(sf::RectangleShape, setSize), asCALL_THISCALL); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);
}

void AS_SFML::priv::drawable_common(const char* name, asIScriptEngine* eng)
{
	int r;

	std::string temp = eng->GetDefaultNamespace();
	std::string ns = temp;
	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	char declaration[64];
	std::sprintf(declaration, "void Draw(%s::%s&in)", ns.c_str(), name);
	r = eng->RegisterObjectMethod("Renderer", declaration, asFUNCTION(draw_common), asCALL_CDECL_OBJFIRST); asAssert(r);
	std::sprintf(declaration, "void Draw(%s::%s&in,const Shader@)", ns.c_str(), name);
	r = eng->RegisterObjectMethod("Renderer", declaration, asFUNCTION(draw_shader), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->SetDefaultNamespace(temp.c_str()); asAssert(r);
}

void AS_SFML::priv::shapes(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::CircleShape>(), "Circle");
	ser->AddUserType(new CSFMLType<sf::ConvexShape>(), "Convex");
	ser->AddUserType(new CSFMLType<sf::RectangleShape>(), "Rectangle");
}
