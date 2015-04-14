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
