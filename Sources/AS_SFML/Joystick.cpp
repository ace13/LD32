#include "Internal.hpp"
#include <SFML/Window/Joystick.hpp>

struct JoystickImpl
{
	unsigned int ID;

	JoystickImpl() : ID(0) { }
	JoystickImpl(unsigned int id) : ID(id) { }
	JoystickImpl(const JoystickImpl&) = default;
	~JoystickImpl() = default;

	JoystickImpl& operator=(const JoystickImpl&) = default;

	bool connected() const
	{
		return sf::Joystick::isConnected(ID);
	}

	bool hasAxis(sf::Joystick::Axis axis) const
	{
		return sf::Joystick::hasAxis(ID, axis);
	}

	bool isPressed(unsigned int button) const
	{
		return sf::Joystick::isButtonPressed(ID, button);
	}

	float axisPos(sf::Joystick::Axis axis) const
	{
		return sf::Joystick::getAxisPosition(ID, axis);
	}

	unsigned int axisCount() const
	{
		return sf::Joystick::AxisCount;
	}
	unsigned int buttonCount() const
	{
		return sf::Joystick::ButtonCount;
	}

#ifdef AS_SUPPORT_VALRET
	sf::Joystick::Identification getIdent() const
	{
		return sf::Joystick::getIdentification(ID);
	}
#endif
};

namespace
{
	void create_joystick(void* mem, unsigned int id) { new (mem)JoystickImpl(id); }
	void create_default_joystick(void* mem) { new (mem)JoystickImpl(); }
	void destroy_joystick(JoystickImpl* mem) { mem->~JoystickImpl(); }

#ifndef AS_SUPPORT_VALRET
	void getIdent(asIScriptGeneric* gen)
	{
		JoystickImpl* obj = reinterpret_cast<JoystickImpl*>(gen->GetObject());
		new (gen->GetAddressOfReturnLocation()) sf::Joystick::Identification(sf::Joystick::getIdentification(obj->ID));
	}
#endif
}

void AS_SFML::priv::joystick(asIScriptEngine* eng)
{
	int r;

	r = eng->SetDefaultNamespace("sf::Joystick"); asAssert(r);

#define RegEnumValue(value) eng->RegisterEnumValue("Axis", #value, sf::Joystick:: ## value)
	r = eng->RegisterEnum("Axis"); asAssert(r);
	r = RegEnumValue(X); asAssert(r);
	r = RegEnumValue(Y); asAssert(r);
	r = RegEnumValue(Z); asAssert(r);
	r = RegEnumValue(R); asAssert(r);
	r = RegEnumValue(U); asAssert(r);
	r = RegEnumValue(V); asAssert(r);
	r = RegEnumValue(PovX); asAssert(r);
	r = RegEnumValue(PovY); asAssert(r);
#undef RegEnumValue

	r = eng->RegisterObjectType("Identification", sizeof(sf::Joystick::Identification), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<sf::Joystick::Identification>()); asAssert(r);
	r = eng->RegisterObjectProperty("Identification", "::string Name", asOFFSET(sf::Joystick::Identification, name)); asAssert(r);
	r = eng->RegisterObjectProperty("Identification", "uint Vendor", asOFFSET(sf::Joystick::Identification, vendorId)); asAssert(r);
	r = eng->RegisterObjectProperty("Identification", "uint Product", asOFFSET(sf::Joystick::Identification, productId)); asAssert(r);

	r = eng->SetDefaultNamespace("sf"); asAssert(r);

	r = eng->RegisterObjectType("Joystick", sizeof(JoystickImpl), asOBJ_VALUE | asGetTypeTraits<JoystickImpl>()); asAssert(r);
	r = eng->RegisterObjectProperty("Joystick", "uint ID", asOFFSET(JoystickImpl, ID)); asAssert(r);

	r = eng->RegisterObjectBehaviour("Joystick", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_joystick), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Joystick", asBEHAVE_CONSTRUCT, "void f(uint id)", asFUNCTION(create_joystick), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Joystick", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_joystick), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("Joystick", "Joystick& opAssign(Joystick&in)", asMETHOD(JoystickImpl, operator=), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Joystick", "bool get_Connected() const", asMETHOD(JoystickImpl, connected), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Joystick", "uint get_AxisCount() const", asMETHOD(JoystickImpl, axisCount), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Joystick", "uint get_ButtonCount() const", asMETHOD(JoystickImpl, buttonCount), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Joystick", "bool HasAxis(sf::Joystick::Axis axis) const", asMETHOD(JoystickImpl, hasAxis), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Joystick", "bool IsPressed(uint button) const", asMETHOD(JoystickImpl, isPressed), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Joystick", "float AxisPosition(sf::Joystick::Axis axis) const", asMETHOD(JoystickImpl, axisPos), asCALL_THISCALL); asAssert(r);

#ifndef AS_SUPPORT_VALRET
	r = eng->RegisterObjectMethod("Joystick", "sf::Joystick::Identification get_Identification() const", asFUNCTION(getIdent), asCALL_GENERIC); asAssert(r);
#else
	r = eng->RegisterObjectMethod("Joystick", "sf::Joystick::Identification get_Identification() const", asMETHOD(JoystickImpl, getIdent), asCALL_THISCALL); asAssert(r);
#endif
}

void AS_SFML::priv::joystick(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<JoystickImpl>(), "Joystick");
	ser->AddUserType(new CSFMLType<sf::Joystick::Identification>(), "Identification");
}
