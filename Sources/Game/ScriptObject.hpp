#pragma once

class asIObjectType;
class asIScriptObject;

namespace Game
{

	class ScriptObject
	{
	public:
		explicit ScriptObject(asIScriptObject* obj);
		explicit ScriptObject(asIObjectType* type);
		ScriptObject(const ScriptObject&) = delete;
		~ScriptObject();

		const asIScriptObject* getObject() const;

	private:
		asIScriptObject* mObj;
	};

}
