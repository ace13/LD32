#pragma once

#include <AS_SFML/Common.hpp>
#include <Util/Time.hpp>
#include <Kunlaboro/Component.hpp>

class asIObjectType;
class asIScriptFunction;
class asIScriptObject;
class asIScriptModule;

namespace sf { class RenderTarget; }

namespace Game
{

	class ScriptObject : public Kunlaboro::Component
	{
	public:
		ScriptObject();
		ScriptObject(const ScriptObject&) = delete;
		~ScriptObject();

		void addedToEntity();

		void setObject(asIScriptObject*);
		asIScriptObject* getObject();
		
	private:
		enum FuncType
		{
			Func_Update,
			Func_Tick,
			Func_Draw,
			Func_DrawUI,

			Func_COUNT
		};

		Kunlaboro::Optional<asIScriptObject*> getObjectMsg(asIScriptModule* mod);
		void setObjectMsg(asIScriptObject* obj, asIScriptModule* mod);
		void updateFunc(const Util::Timespan& dt);
		void tickFunc(const Util::Timespan& dt);
		void drawFunc(sf::RenderTarget&);
		void drawUIFunc(sf::RenderTarget&);

		asIScriptObject* mObj;

		asIScriptFunction* mFuncs[Func_COUNT];
	};

}
