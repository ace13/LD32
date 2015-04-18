#include "Internal.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <Math/Vec2.hpp>

#ifndef AS_SUPPORT_VALRET
void mapPixel(asIScriptGeneric* gen)
{
	sf::RenderTarget* rt = reinterpret_cast<sf::RenderTarget*>(gen->GetObject());
	new (gen->GetAddressOfReturnLocation()) Math::Vec2(rt->mapPixelToCoords((sf::Vector2i)*reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0))));
}
void mapCoords(asIScriptGeneric* gen)
{
	sf::RenderTarget* rt = reinterpret_cast<sf::RenderTarget*>(gen->GetObject());
	new (gen->GetAddressOfReturnLocation()) Math::Vec2(rt->mapCoordsToPixel(*reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0))));
}
#else
Math::Vec2 mapPixel(sf::RenderTarget& target, const Math::Vec2& point)
{
	return target.mapPixelToCoords((sf::Vector2i)point);
}
Math::Vec2 mapCoords(sf::RenderTarget& target, const Math::Vec2& point)
{
	return target.mapCoordsToPixel(point);
}
#endif

void AS_SFML::priv::rendertarget(asIScriptEngine* eng)
{
	int r;

	r = eng->RegisterObjectMethod("Renderer", "const View& get_View() const", asMETHOD(sf::RenderTarget, getView), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Renderer", "void set_View(View&in) const", asMETHOD(sf::RenderTarget, setView), asCALL_THISCALL); asAssert(r);
	
#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("Renderer", "::Vec2 MapPixel(::Vec2&in) const", asFUNCTION(mapPixel), asCALL_GENERIC); asAssert(r);
	r = eng->RegisterObjectMethod("Renderer", "::Vec2 MapCoords(::Vec2&in) const", asFUNCTION(mapCoords), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Renderer", "::Vec2 MapPixel(::Vec2&in) const", asFUNCTION(mapPixel), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Renderer", "::Vec2 MapCoords(::Vec2&in) const", asFUNCTION(mapCoords), asCALL_CDECL_OBJFIRST); asAssert(r);
#endif

	r = eng->RegisterObjectMethod("Renderer", "void Clear()", asMETHOD(sf::RenderTarget, clear), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Renderer", "void Clear(Color&in)", asMETHOD(sf::RenderTarget, clear), asCALL_THISCALL); asAssert(r);
}
