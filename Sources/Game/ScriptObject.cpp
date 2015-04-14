#include "ScriptObject.hpp"
#include <angelscript.h>

using namespace Game;

ScriptObject::ScriptObject(asIScriptObject* obj) :
	mObj(obj)
{
	mObj->AddRef(); // FIXME: Should I do this?
}
ScriptObject::ScriptObject(asIObjectType* type) :
	mObj(nullptr)
{
	mObj = reinterpret_cast<asIScriptObject*>(type->GetEngine()->CreateScriptObject(type));
}

ScriptObject::~ScriptObject()
{
	mObj->Release();
}

const asIScriptObject* ScriptObject::getObject() const
{
	return mObj;
}


