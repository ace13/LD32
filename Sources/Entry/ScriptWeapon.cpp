#include "ScriptWeapon.hpp"
#include <Game/ScriptManager.hpp>
#include <angelscript.h>

using namespace Game;

ScriptWeapon::ScriptWeapon() : Kunlaboro::Component("Fallacy.ScriptWeapon"),
	mObj(nullptr)
{
	ScriptManager::Singleton().notifyNewObject(this);
	std::memset(mFuncs, 0, sizeof(mFuncs));
}

ScriptWeapon::~ScriptWeapon()
{
	ScriptManager::Singleton().notifyObjectRemoved(this);

	if (mObj)
	{
		mObj->GetObjectType()->SetUserData(nullptr, (uintptr_t)mObj);
		mObj->Release();
	}
}

void ScriptWeapon::addedToEntity()
{
	requestMessage("GetObject", &ScriptWeapon::getObjectMsg, true);
	requestMessage("SetObject", &ScriptWeapon::setObject, true);

	if (!mObj)
		return;

	auto type = mObj->GetObjectType();
	
	mFuncs[Func_Draw] = type->GetMethodByName("Draw");
	mFuncs[Func_DrawUI] = type->GetMethodByName("DrawUI");
	mFuncs[Func_Tick] = type->GetMethodByName("Tick");
	mFuncs[Func_Update] = type->GetMethodByName("Update");

	if (mFuncs[Func_Draw])
		requestMessage("Game.Draw", &ScriptWeapon::drawFunc);
	if (mFuncs[Func_DrawUI])
		requestMessage("Game.DrawUI", &ScriptWeapon::drawUIFunc);
	if (mFuncs[Func_Tick])
		requestMessage("Game.Tick", &ScriptWeapon::tickFunc);
	if (mFuncs[Func_Update])
		requestMessage("Game.Update", &ScriptWeapon::updateFunc);
}

void ScriptWeapon::setObject(asIScriptObject* obj)
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
		requestMessage("Game.Draw", &ScriptWeapon::drawFunc);
	if (mFuncs[Func_DrawUI])
		requestMessage("Game.DrawUI", &ScriptWeapon::drawUIFunc);
	if (mFuncs[Func_Tick])
		requestMessage("Game.Tick", &ScriptWeapon::tickFunc);
	if (mFuncs[Func_Update])
		requestMessage("Game.Update", &ScriptWeapon::updateFunc);
}

asIScriptObject* ScriptWeapon::getObject()
{
	return mObj;
}

Kunlaboro::Optional<asIScriptObject*> ScriptWeapon::getObjectMsg()
{
	return mObj;
}

void ScriptWeapon::updateFunc(const Util::Timespan& dt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Update]);
	ctx->SetObject(mObj);
	ctx->SetArgFloat(0, std::chrono::duration_cast<std::chrono::duration<float>>(dt).count());

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptWeapon::tickFunc(const Util::Timespan& dt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Tick]);
	ctx->SetObject(mObj);
	ctx->SetArgFloat(0, std::chrono::duration_cast<std::chrono::duration<float>>(dt).count());

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptWeapon::drawFunc(sf::RenderTarget& rt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_Draw]);
	ctx->SetObject(mObj);
	ctx->SetArgObject(0, &rt);

	int r = ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptWeapon::drawUIFunc(sf::RenderTarget& rt)
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_DrawUI]);
	ctx->SetObject(mObj);
	ctx->SetArgObject(0, &rt);

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
