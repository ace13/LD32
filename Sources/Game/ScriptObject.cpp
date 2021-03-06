#include "ScriptObject.hpp"
#include "ScriptManager.hpp"
#include <angelscript.h>

using namespace Game;

ScriptObject::ScriptObject() : Kunlaboro::Component("Game.ScriptObject"),
	mObj(nullptr)
{
	ScriptManager::Singleton().notifyNewObject(this);
	std::memset(mFuncs, 0, sizeof(mFuncs));
}

ScriptObject::~ScriptObject()
{
	ScriptManager::Singleton().notifyObjectRemoved(this);

	if (mObj)
	{
		mObj->GetObjectType()->SetUserData(nullptr, (uintptr_t)mObj);
		mObj->Release();
	}
}

void ScriptObject::addedToEntity()
{
	requestMessage("GetObject", &ScriptObject::getObjectMsg, true);
	requestMessage("SetObject", &ScriptObject::setObjectMsg, true);

	if (!mObj)
		return;

	auto type = mObj->GetObjectType();
	
	mFuncs[Func_Draw] = type->GetMethodByName("Draw");
	mFuncs[Func_DrawUI] = type->GetMethodByName("DrawUI");
	mFuncs[Func_Tick] = type->GetMethodByName("Tick");
	mFuncs[Func_Update] = type->GetMethodByName("Update");

	if (mFuncs[Func_Draw])
		requestMessage("Game.Draw", &ScriptObject::drawFunc);
	if (mFuncs[Func_DrawUI])
		requestMessage("Game.DrawUI", &ScriptObject::drawUIFunc);
	if (mFuncs[Func_Tick])
		requestMessage("Game.Tick", &ScriptObject::tickFunc);
	if (mFuncs[Func_Update])
		requestMessage("Game.Update", &ScriptObject::updateFunc);
}

void ScriptObject::setObject(asIScriptObject* obj)
{
	if (mObj)
	{
		auto type = mObj->GetObjectType();
		type->SetUserData(nullptr, (uintptr_t)mObj);
		std::memset(mFuncs, 0, sizeof(mFuncs));

		mObj->Release();
		mObj = nullptr;

		unrequestMessage("Game.Draw");
		unrequestMessage("Game.DrawUI");
		unrequestMessage("Game.Tick");
		unrequestMessage("Game.Update");
	}

	mObj = obj;

	auto type = mObj->GetObjectType();
	type->SetUserData(this, (uintptr_t)mObj);

	if (getOwnerId() == 0)
		return;

	mFuncs[Func_Draw] = type->GetMethodByName("Draw");
	mFuncs[Func_DrawUI] = type->GetMethodByName("DrawUI");
	mFuncs[Func_Tick] = type->GetMethodByName("Tick");
	mFuncs[Func_Update] = type->GetMethodByName("Update");

	if (mFuncs[Func_Draw])
		requestMessage("Game.Draw", &ScriptObject::drawFunc);
	if (mFuncs[Func_DrawUI])
		requestMessage("Game.DrawUI", &ScriptObject::drawUIFunc);
	if (mFuncs[Func_Tick])
		requestMessage("Game.Tick", &ScriptObject::tickFunc);
	if (mFuncs[Func_Update])
		requestMessage("Game.Update", &ScriptObject::updateFunc);
}

asIScriptObject* ScriptObject::getObject()
{
	return mObj;
}

Kunlaboro::Optional<asIScriptObject*> ScriptObject::getObjectMsg(asIScriptModule* mod)
{
	if (mod == mObj->GetObjectType()->GetModule())
		return mObj;
	return nullptr;
}

void ScriptObject::setObjectMsg(asIScriptObject* obj, asIScriptModule* mod)
{
	if (mod == mObj->GetObjectType()->GetModule())
		setObject(obj);
}

void ScriptObject::updateFunc(const Util::Timespan& dt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Update]);
	ctx->SetObject(mObj);
	ctx->SetArgFloat(0, std::chrono::duration_cast<std::chrono::duration<float>>(dt).count());

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptObject::tickFunc(const Util::Timespan& dt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Tick]);
	ctx->SetObject(mObj);
	ctx->SetArgFloat(0, std::chrono::duration_cast<std::chrono::duration<float>>(dt).count());

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptObject::drawFunc(sf::RenderTarget& rt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Draw]);
	ctx->SetObject(mObj);
	ctx->SetArgObject(0, &rt);

	int r = ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptObject::drawUIFunc(sf::RenderTarget& rt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_DrawUI]);
	ctx->SetObject(mObj);
	ctx->SetArgObject(0, &rt);

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
