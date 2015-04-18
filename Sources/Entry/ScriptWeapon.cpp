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

	requestMessage("StartFiring", &ScriptWeapon::startFire, true);
	requestMessage("StopFiring", &ScriptWeapon::stopFire, true);

	if (!mObj)
		return;

	auto type = mObj->GetObjectType();
	
	mFuncs[Func_Draw] = type->GetMethodByName("Draw");
	mFuncs[Func_DrawUI] = type->GetMethodByName("DrawUI");
	mFuncs[Func_Tick] = type->GetMethodByName("Tick");
	mFuncs[Func_Update] = type->GetMethodByName("Update");

	mFuncs[Func_CanFire] = type->GetMethodByName("get_CanFire");
	mFuncs[Func_GetFire] = type->GetMethodByName("get_Firing");
	mFuncs[Func_SetFire] = type->GetMethodByName("set_Firing");

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

	{
		asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

		ctx->Prepare(type->GetMethodByName("get_Name"));
		ctx->SetObject(mObj);

		ctx->Execute();

		mName = *reinterpret_cast<std::string*>(ctx->GetReturnObject());

		ctx->Prepare(type->GetMethodByName("get_Type"));
		ctx->SetObject(mObj);

		ctx->Execute();

		mType = (Gameplay::Weapon::Type)ctx->GetReturnDWord();

		mObj->GetEngine()->ReturnContext(ctx);
	}

	if (getOwnerId() == 0)
		return;

	mFuncs[Func_Draw] = type->GetMethodByName("Draw");
	mFuncs[Func_DrawUI] = type->GetMethodByName("DrawUI");
	mFuncs[Func_Tick] = type->GetMethodByName("Tick");
	mFuncs[Func_Update] = type->GetMethodByName("Update");
	mFuncs[Func_CanFire] = type->GetMethodByName("get_CanFire");
	mFuncs[Func_GetFire] = type->GetMethodByName("get_Firing");
	mFuncs[Func_SetFire] = type->GetMethodByName("set_Firing");
		
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

const std::string& ScriptWeapon::getName() const
{
	return mName;
}
Gameplay::Weapon::Type ScriptWeapon::getType() const
{
	return mType;
}

bool ScriptWeapon::canFire() const
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_CanFire]);
	ctx->SetObject(mObj);

	ctx->Execute();

	bool ret = ctx->GetReturnByte();

	mObj->GetEngine()->ReturnContext(ctx);

	return ret;
}
bool ScriptWeapon::isFiring() const
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_GetFire]);
	ctx->SetObject(mObj);

	ctx->Execute();

	bool ret = ctx->GetReturnByte();

	mObj->GetEngine()->ReturnContext(ctx);

	return ret;
}

void ScriptWeapon::startFire()
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	int r = ctx->Prepare(mFuncs[Func_SetFire]);
	r = ctx->SetObject(mObj);
	r = ctx->SetArgByte(0, 1);

	r = ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}
void ScriptWeapon::stopFire()
{
	asIScriptContext* ctx = mObj->GetEngine()->RequestContext();

	ctx->Prepare(mFuncs[Func_SetFire]);
	ctx->SetObject(mObj);
	ctx->SetArgByte(0, 0);

	ctx->Execute();

	mObj->GetEngine()->ReturnContext(ctx);
}


Kunlaboro::Optional<asIScriptObject*> ScriptWeapon::getObjectMsg()
{
	return mObj;
}
Kunlaboro::Optional<bool> ScriptWeapon::canFireMsg()
{
	return canFire();
}
Kunlaboro::Optional<bool> ScriptWeapon::isFiringMsg()
{
	return isFiring();
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
