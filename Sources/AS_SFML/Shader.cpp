#include "Internal.hpp"
#include <SFML/Graphics/Shader.hpp>

namespace
{
	void shader_setTexture(sf::Shader* shader, const std::string& name, sf::Texture* tex)
	{
		shader->setParameter(name, *tex);
	}
	void shader_setCurTexture(sf::Shader* shader, const std::string& name)
	{
		shader->setParameter(name, sf::Shader::CurrentTexture);
	}
}

void AS_SFML::priv::shader(asIScriptEngine* eng)
{
	int r;

	r = eng->SetDefaultNamespace("sf::Shader"); asAssert(r);

	r = eng->RegisterGlobalFunction("bool get_Available()", asFUNCTION(sf::Shader::isAvailable), asCALL_CDECL);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, float val)", asMETHODPR(sf::Shader, setParameter, (const std::string&, float), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, float x, float y)", asMETHODPR(sf::Shader, setParameter, (const std::string&, float, float), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, float x, float y, float z)", asMETHODPR(sf::Shader, setParameter, (const std::string&, float, float, float), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, float x, float y, float z, float w)", asMETHODPR(sf::Shader, setParameter, (const std::string&, float, float, float, float), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, ::Vec2&in vec)", asMETHODPR(sf::Shader, setParameter, (const std::string&, const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, Color&in color)", asMETHODPR(sf::Shader, setParameter, (const std::string&, const sf::Color&), void), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void Set(::string&in name, Texture@ color)", asFUNCTION(shader_setTexture), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Shader", "void SetCurTexture(::string&in name)", asFUNCTION(shader_setCurTexture), asCALL_CDECL_OBJFIRST); asAssert(r);
}
