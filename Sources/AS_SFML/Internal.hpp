#pragma once

#include "Common.hpp"
#include <angelscript.h>
#include <serializer/serializer.h>
#include <cassert>

namespace AS_SFML
{
	namespace priv
	{
		void audio_common(const char* name, asIScriptEngine* eng);
		void drawable_common(const char* name, asIScriptEngine* eng);
		template<typename Transformable>
		void transformable_common(const char* name, asIScriptEngine* eng)
		{
			int r;
			r = eng->RegisterObjectMethod(name, "const ::Vec2& get_Origin() const", asMETHODPR(Transformable, getOrigin, (void) const, const sf::Vector2f&), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void set_Origin(::Vec2&in origin)", asMETHODPR(Transformable, setOrigin, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "const ::Vec2& get_Position() const", asMETHODPR(Transformable, getPosition, (void) const, const sf::Vector2f&), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void set_Position(::Vec2&in pos)", asMETHODPR(Transformable, setPosition, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "const ::Vec2& get_Scale() const", asMETHODPR(Transformable, getScale, (void) const, const sf::Vector2f&), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void set_Scale(::Vec2&in scale)", asMETHODPR(Transformable, setScale, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "float get_Rotation() const", asMETHODPR(Transformable, getRotation, (void) const, float), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void set_Rotation(float ang)", asMETHODPR(Transformable, setRotation, (float), void), asCALL_THISCALL); asAssert(r);

			r = eng->RegisterObjectMethod(name, "void Move(::Vec2&in offest)", asMETHODPR(Transformable, move, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void Move(float x, float y)", asMETHODPR(Transformable, move, (float, float), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void Scale(::Vec2&in factor)", asMETHODPR(Transformable, scale, (const sf::Vector2f&), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void Scale(float x, float y)", asMETHODPR(Transformable, scale, (float, float), void), asCALL_THISCALL); asAssert(r);
			r = eng->RegisterObjectMethod(name, "void Rotate(float ang)", asMETHODPR(Transformable, rotate, (float), void), asCALL_THISCALL); asAssert(r);
		}

		void color(asIScriptEngine*);
		void joystick(asIScriptEngine*);
		void keyboard(asIScriptEngine*);
		void mouse(asIScriptEngine*);
		void music(asIScriptEngine*);
		void rendertarget(asIScriptEngine*);
		void shader(asIScriptEngine*);
		void shapes(asIScriptEngine*);
		void sound(asIScriptEngine*);
		void sprite(asIScriptEngine*);
		void text(asIScriptEngine*);
		void texture(asIScriptEngine*);
		void view(asIScriptEngine*);

		void color(CSerializer*);
		void joystick(CSerializer*);
		void shapes(CSerializer*);
		void sprite(CSerializer*);
		void text(CSerializer*);
		void view(CSerializer*);

		template<typename T>
		struct CSFMLType : public CUserType
		{
			void Store(CSerializedValue *val, void *ptr)
			{
				val->SetUserData(new T(*(T*)ptr));
			}
			void Restore(CSerializedValue *val, void *ptr)
			{
				T *buffer = (T*)val->GetUserData();
				*(T*)ptr = *buffer;
			}
			void CleanupUserData(CSerializedValue *val)
			{
				T *buffer = (T*)val->GetUserData();
				delete buffer;
			}
		};
	}
}
