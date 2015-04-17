#include "ScriptExtensions.hpp"

#include <Math/Eases.hpp>
#include <Math/Rect.hpp>
#include <Math/Vec2.hpp>

#include <angelscript.h>
#include <scriptarray/scriptarray.h>
#include <scriptmath/scriptmath.h>
#include <scriptstdstring/scriptstdstring.h>
#include <serializer/serializer.h>

#include <cassert>
#include <cstdio>
#include <new>

namespace
{
	void as_addons(asIScriptEngine* eng)
	{
		RegisterScriptArray(eng, true);
		RegisterScriptMath(eng);
		RegisterStdString(eng);
		RegisterStdStringUtils(eng);
	}

#ifndef AS_SUPPORT_VALRET
	template<typename T>
	void ease_value(asIScriptGeneric* gen)
	{
		Math::Easer<T>* ease = reinterpret_cast<Math::Easer<T>*>(gen->GetObject());
		T& beg = *reinterpret_cast<T*>(gen->GetArgObject(0));
		T& end = *reinterpret_cast<T*>(gen->GetArgObject(1));
		float t = gen->GetArgFloat(2);

		new (gen->GetAddressOfReturnLocation()) T(ease->ease(beg, end, t));
	}
	template<>
	void ease_value<float>(asIScriptGeneric* gen)
	{
		Math::Easer<float>* ease = reinterpret_cast<Math::Easer<float>*>(gen->GetObject());
		float beg = gen->GetArgFloat(0);
		float end = gen->GetArgFloat(1);
		float t = gen->GetArgFloat(2);

		gen->SetReturnFloat(ease->ease(beg, end, t));
	}
#endif

	enum EaseFuncs
	{
		Ease_InBack,
		Ease_InBounce,
		Ease_InCirc,
		Ease_InCubic,
		Ease_InElastic,
		Ease_InExpo,
		Ease_InQuad,
		Ease_InQuart,
		Ease_InQuint,
		Ease_InSine,
		Ease_OutBack,
		Ease_OutBounce,
		Ease_OutCirc,
		Ease_OutCubic,
		Ease_OutElastic,
		Ease_OutExpo,
		Ease_OutQuad,
		Ease_OutQuart,
		Ease_OutQuint,
		Ease_OutSine,
		Ease_InOutBack,
		Ease_InOutBounce,
		Ease_InOutCirc,
		Ease_InOutCubic,
		Ease_InOutElastic,
		Ease_InOutExpo,
		Ease_InOutQuad,
		Ease_InOutQuart,
		Ease_InOutQuint,
		Ease_InOutSine
	};

	template<typename T>
	void create_default_easer(void* mem)
	{
		new (mem)Math::Easer<T>(Math::Eases::easeInCubic<T>, 1);
	}
	template<typename T>
	void create_easer(void* mem, EaseFuncs func, float d)
	{
		Math::Easer<T>::EaseFunc f;

		switch (func)
		{
		case Ease_InBack: f = Math::Eases::easeInBack<T>; break;
		case Ease_InBounce: f = Math::Eases::easeInBounce<T>; break;
		case Ease_InCirc: f = Math::Eases::easeInCirc<T>; break;
		case Ease_InCubic: f = Math::Eases::easeInCubic<T>; break;
		case Ease_InElastic: f = Math::Eases::easeInElastic<T>; break;
		case Ease_InExpo: f = Math::Eases::easeInExpo<T>; break;
		case Ease_InQuad: f = Math::Eases::easeInQuad<T>; break;
		case Ease_InQuart: f = Math::Eases::easeInQuart<T>; break;
		case Ease_InQuint: f = Math::Eases::easeInQuint<T>; break;
		case Ease_InSine: f = Math::Eases::easeInSine<T>; break;
		case Ease_OutBack: f = Math::Eases::easeOutBack<T>; break;
		case Ease_OutBounce: f = Math::Eases::easeOutBounce<T>; break;
		case Ease_OutCirc: f = Math::Eases::easeOutCirc<T>; break;
		case Ease_OutCubic: f = Math::Eases::easeOutCubic<T>; break;
		case Ease_OutElastic: f = Math::Eases::easeOutElastic<T>; break;
		case Ease_OutExpo: f = Math::Eases::easeOutExpo<T>; break;
		case Ease_OutQuad: f = Math::Eases::easeOutQuad<T>; break;
		case Ease_OutQuart: f = Math::Eases::easeOutQuart<T>; break;
		case Ease_OutQuint: f = Math::Eases::easeOutQuint<T>; break;
		case Ease_OutSine: f = Math::Eases::easeOutSine<T>; break;
		case Ease_InOutBack: f = Math::Eases::easeInOutBack<T>; break;
		case Ease_InOutBounce: f = Math::Eases::easeInOutBounce<T>; break;
		case Ease_InOutCirc: f = Math::Eases::easeInOutCirc<T>; break;
		case Ease_InOutCubic: f = Math::Eases::easeInOutCubic<T>; break;
		case Ease_InOutElastic: f = Math::Eases::easeInOutElastic<T>; break;
		case Ease_InOutExpo: f = Math::Eases::easeInOutExpo<T>; break;
		case Ease_InOutQuad: f = Math::Eases::easeInOutQuad<T>; break;
		case Ease_InOutQuart: f = Math::Eases::easeInOutQuart<T>; break;
		case Ease_InOutQuint: f = Math::Eases::easeInOutQuint<T>; break;
		case Ease_InOutSine: f = Math::Eases::easeInOutSine<T>; break;
		}

		new (mem)Math::Easer<T>(f, d);
	}
	template<typename T>
	void destroy_easer(Math::Easer<T>* ease)
	{
		ease->~Easer();
	}

	template<typename T>
	void ease(const char* name, const char* typeName, asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectType(name, sizeof(Math::Easer<T>), asOBJ_VALUE | asGetTypeTraits<Math::Easer<T>>()); asAssert(r);

		r = eng->RegisterObjectBehaviour(name, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_easer<T>), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour(name, asBEHAVE_CONSTRUCT, "void f(EaseFunc, float)", asFUNCTION(create_easer<T>), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour(name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_easer<T>), asCALL_CDECL_OBJFIRST); asAssert(r);

		char buffer[256];
		std::sprintf(buffer, "%s ease(%s&in start, %s&in change, float time) const", typeName, typeName, typeName);
#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod(name, buffer, asFUNCTION(ease_value<T>), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod(name, buffer, asMETHOD(Math::Easer<T>, ease), asCALL_THISCALL); asAssert(r);
#endif

	}

#ifndef AS_SUPPORT_VALRET
	void rect_getCenter(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->getCenter());
	}
	void rect_getSize(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->getSize());
	}
	void rect_capture(asIScriptGeneric* gen)
	{
		Math::Rect* rect = reinterpret_cast<Math::Rect*>(gen->GetObject());
		Math::Vec2* capture = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		new (gen->GetAddressOfReturnLocation())Math::Vec2(rect->capture(*capture));
	}
#endif

	void rect_create(void* mem, float top, float left, float width, float height)
	{
		new (mem)Math::Rect(top, left, width, height);
	}
	void rect_create_vec(void* mem, const Math::Vec2& pos, const Math::Vec2& size)
	{
		new (mem)Math::Rect(pos, size);
	}
	void rect_destroy(Math::Rect* mem)
	{
		mem->~Rect();
	}

	void rect(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float top = 0, float left = 0, float width = 0, float height = 0)", asFUNCTION(rect_create), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(Vec2&in,Vec2&in)", asFUNCTION(rect_create_vec), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Rect", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(rect_destroy), asCALL_CDECL_OBJFIRST); asAssert(r);

		r = eng->RegisterObjectMethod("Rect", "bool opEquals(Rect&in rhs) const", asFUNCTIONPR(sf::operator==, (const sf::FloatRect&, const sf::FloatRect&), bool), asCALL_CDECL_OBJFIRST); asAssert(r);

		r = eng->RegisterObjectProperty("Rect", "float Top", asOFFSET(Math::Rect, top)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Left", asOFFSET(Math::Rect, left)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Width", asOFFSET(Math::Rect, width)); asAssert(r);
		r = eng->RegisterObjectProperty("Rect", "float Height", asOFFSET(Math::Rect, height)); asAssert(r);

		r = eng->RegisterObjectMethod("Rect", "void set_Center(Vec2&in center)", asMETHOD(Math::Rect, setCenter), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "void set_Size(Vec2&in size)", asMETHOD(Math::Rect, setSize), asCALL_THISCALL); asAssert(r);
#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Center() const", asFUNCTION(rect_getCenter), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Size() const", asFUNCTION(rect_getSize), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 Capture(Vec2&in toGrab)", asFUNCTION(rect_capture), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Center() const", asMETHOD(Math::Rect, getCenter), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 get_Size() const", asMETHOD(Math::Rect, getSize), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "Vec2 Capture(Vec2&in toGrab)", asMETHOD(Math::Rect, capture), asCALL_THISCALL); asAssert(r);
#endif

		r = eng->RegisterObjectMethod("Rect", "bool Contains(Vec2&in point) const", asMETHODPR(Math::Rect, contains, (const sf::Vector2f&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "bool Intersects(Rect&in rect) const", asMETHODPR(Math::Rect, intersects, (const sf::FloatRect&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "bool Intersects(Rect&in rect, Rect&out) const", asMETHODPR(Math::Rect, intersects, (const sf::FloatRect&, sf::FloatRect&) const, bool), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Rect", "void Move(Vec2&in offset)", asMETHOD(Math::Rect, move), asCALL_THISCALL); asAssert(r);
	}

#ifndef AS_SUPPORT_VALRET
	void vec2_getNormalized(asIScriptGeneric* gen)
	{
		Math::Vec2* vec = reinterpret_cast<Math::Vec2*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation())Math::Vec2(vec->getNormalized());
	}
	void vec2_getRotated(asIScriptGeneric* gen)
	{
		Math::Vec2* vec = reinterpret_cast<Math::Vec2*>(gen->GetObject());
		float ang = gen->GetArgFloat(0);
		new (gen->GetAddressOfReturnLocation())Math::Vec2(vec->getRotated(ang));
	}
#endif

	void create_default_vec2(void* mem) { new (mem)Math::Vec2(); }
	void create_vec2(void* mem, float x, float y) { new (mem)Math::Vec2(x, y); }
	void destroy_vec2(Math::Vec2* mem) { mem->~Vec2(); }

#ifndef AS_SUPPORT_VALRET
	enum OPER_TYPE
	{
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV
	};

	template<unsigned int Type>
	void math_vec2_oper(asIScriptGeneric* gen)
	{
		Math::Vec2& v = *reinterpret_cast<Math::Vec2*>(gen->GetObject());
		Math::Vec2& v2 = *reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));

		if (Type == OP_ADD)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v + v2);
		else if (Type == OP_SUB)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v - v2);
		else if (Type == OP_MUL)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v * v2);
		else if (Type == OP_DIV)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v / v2);
	}
	template<unsigned int Type>
	void math_vec2_oper_float(asIScriptGeneric* gen)
	{
		Math::Vec2& v = *reinterpret_cast<Math::Vec2*>(gen->GetObject());
		float v2 = gen->GetArgFloat(0);

		if (Type == OP_MUL)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v * v2);
		else if (Type == OP_DIV)
			new (gen->GetAddressOfReturnLocation())Math::Vec2(v / v2);
	}
#endif

	void vec2(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectProperty("Vec2", "float X", asOFFSET(Math::Vec2, x)); asAssert(r);
		r = eng->RegisterObjectProperty("Vec2", "float Y", asOFFSET(Math::Vec2, y)); asAssert(r);

		r = eng->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_vec2), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(create_vec2), asCALL_CDECL_OBJFIRST); asAssert(r);
		r = eng->RegisterObjectBehaviour("Vec2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_vec2), asCALL_CDECL_OBJFIRST); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "Vec2& opAssign(Vec2&in)", asMETHOD(Math::Vec2, operator=), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opAddAssign(Vec2&in)", asMETHOD(Math::Vec2, operator+=), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opSubAssign(Vec2&in)", asMETHOD(Math::Vec2, operator-=), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opMulAssign(Vec2&in)", asMETHODPR(Math::Vec2, operator*=, (const Math::Vec2&), Math::Vec2&), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opDivAssign(Vec2&in)", asMETHODPR(Math::Vec2, operator/=, (const Math::Vec2&), Math::Vec2&), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opMulAssign(float)", asMETHODPR(Math::Vec2, operator*=, (float), Math::Vec2&), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2& opDivAssign(float)", asMETHODPR(Math::Vec2, operator/=, (float), Math::Vec2&), asCALL_THISCALL); asAssert(r);

#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opAdd(Vec2&in)", asFUNCTION(math_vec2_oper<OP_ADD>), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opSub(Vec2&in)", asFUNCTION(math_vec2_oper<OP_SUB>), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opMul(Vec2&in)", asFUNCTION(math_vec2_oper<OP_MUL>), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opDiv(Vec2&in)", asFUNCTION(math_vec2_oper<OP_DIV>), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opMul(float)", asFUNCTION(math_vec2_oper_float<OP_MUL>), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opDiv(float)", asFUNCTION(math_vec2_oper_float<OP_DIV>), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opAdd(Vec2&in)", asMETHOD(Math::Vec2, operator+), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opSub(Vec2&in)", asMETHOD(Math::Vec2, operator-), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opMul(Vec2&in)", asMETHODPR(Math::Vec2, operator*, (const Math::Vec2&) const, Math::Vec2), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opDiv(Vec2&in)", asMETHODPR(Math::Vec2, operator/, (const Math::Vec2&) const, Math::Vec2), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opMul(float)", asMETHODPR(Math::Vec2, operator*, (float) const, Math::Vec2), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 opDiv(float)", asMETHODPR(Math::Vec2, operator/, (float) const, Math::Vec2), asCALL_THISCALL); asAssert(r);
#endif

		r = eng->RegisterObjectMethod("Vec2", "float get_Angle() const", asMETHOD(Math::Vec2, getAngle), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float get_Length() const", asMETHOD(Math::Vec2, getLength), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float get_LengthSquared() const", asMETHOD(Math::Vec2, getLengthSquared), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void set_Angle(float ang)", asMETHOD(Math::Vec2, setAngle), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void set_Length(float ang)", asMETHOD(Math::Vec2, setLength), asCALL_THISCALL); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "float Bearing(Vec2&in) const", asMETHOD(Math::Vec2, getBearing), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float Distance(Vec2&in) const", asMETHOD(Math::Vec2, getDistance), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float DistanceSquared(Vec2&in) const", asMETHOD(Math::Vec2, getDistanceSquared), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "float Dot(Vec2&in) const", asMETHOD(Math::Vec2, getDot), asCALL_THISCALL); asAssert(r);

		r = eng->RegisterObjectMethod("Vec2", "void Normalize()", asMETHOD(Math::Vec2, normalize), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "void Rotate(float ang)", asMETHOD(Math::Vec2, rotate), asCALL_THISCALL); asAssert(r);
		
#ifndef AS_SUPPORT_VALRET
		r = eng->RegisterObjectMethod("Vec2", "Vec2 get_Normalized() const", asFUNCTION(vec2_getNormalized), asCALL_GENERIC); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 Rotated(float ang)", asFUNCTION(vec2_getRotated), asCALL_GENERIC); asAssert(r);
#else
		r = eng->RegisterObjectMethod("Vec2", "Vec2 get_Normalized() const", asMETHOD(Math::Vec2, getNormalized), asCALL_THISCALL); asAssert(r);
		r = eng->RegisterObjectMethod("Vec2", "Vec2 Rotated(float ang)", asMETHOD(Math::Vec2, getRotated), asCALL_THISCALL); asAssert(r);
#endif
	}

	void math(asIScriptEngine* eng)
	{
		int r;

		r = eng->RegisterObjectType("Rect", sizeof(Math::Rect), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Math::Rect>()); asAssert(r);
		r = eng->RegisterObjectType("Vec2", sizeof(Math::Vec2), asOBJ_VALUE | asGetTypeTraits<Math::Vec2>()); asAssert(r);

		rect(eng);
		vec2(eng);
	
#define FUNC(name) r = eng->RegisterEnumValue("EaseFunc", #name, Ease_ ## name); asAssert(r)
#define METHOD(name) FUNC(In ## name); FUNC(Out ## name); FUNC(InOut ## name)

		r = eng->RegisterEnum("EaseFunc"); asAssert(r);
		METHOD(Back);
		METHOD(Bounce);
		METHOD(Circ);
		METHOD(Cubic);
		METHOD(Elastic);
		METHOD(Expo);
		METHOD(Quad);
		METHOD(Quart);
		METHOD(Quint);
		METHOD(Sine);

#undef FUNC
#undef METHOD

		ease<float>("FloatEaser", "float", eng);
		ease<Math::Vec2>("Vec2Easer", "Vec2", eng);

		r = eng->RegisterGlobalProperty("const float PI", const_cast<float*>(&Math::PI)); asAssert(r);
		r = eng->RegisterGlobalProperty("const float HALF_PI", const_cast<float*>(&Math::HALF_PI)); asAssert(r);
		r = eng->RegisterGlobalProperty("const float TWICE_PI", const_cast<float*>(&Math::TWICE_PI)); asAssert(r);
		r = eng->RegisterGlobalFunction("float Random(float min, float max)", asFUNCTION(Math::randomFloat), asCALL_CDECL); asAssert(r);
		r = eng->RegisterGlobalFunction("int Random(int min, int max)", asFUNCTION(Math::randomInt), asCALL_CDECL); asAssert(r);
	}
}

void Game::addGeneralScriptExtensions(asIScriptEngine* eng)
{
	as_addons(eng);
	math(eng);
}

namespace
{
	template<typename T>
	struct CSimpleType : public CUserType
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

	struct CArrayType : public CUserType
	{
		void Store(CSerializedValue *val, void *ptr)
		{
			CScriptArray *arr = (CScriptArray*)ptr;
			for (unsigned int i = 0; i < arr->GetSize(); i++)
				val->m_children.push_back(new CSerializedValue(val, "", "", arr->At(i), arr->GetElementTypeId()));
		}
		void Restore(CSerializedValue *val, void *ptr)
		{
			CScriptArray *arr = (CScriptArray*)ptr;
			arr->Resize(val->m_children.size());
			for (size_t i = 0; i < val->m_children.size(); ++i)
				val->m_children[i]->Restore(arr->At(i), arr->GetElementTypeId());
		}
	};
}

void Game::addGeneralSerializerTypes(CSerializer* ser)
{
	ser->AddUserType(new CArrayType(), "array");
	ser->AddUserType(new CSimpleType<std::string>(), "string");

	ser->AddUserType(new CSimpleType<Math::Rect>(), "Rect");
	ser->AddUserType(new CSimpleType<Math::Vec2>(), "Vec2");
}
