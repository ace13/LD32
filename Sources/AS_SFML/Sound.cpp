#include "Internal.hpp"
#include <SFML/Audio/Sound.hpp>
#include <new>

namespace
{
	void create_default_sound(void* mem)
	{
		new (mem)sf::Sound();
	}
	void create_sound(void* mem, sf::SoundBuffer* buf)
	{
		new (mem)sf::Sound(*buf);
	}
	void destroy_sound(sf::Sound* sound)
	{
		sound->~Sound();
	}

	void setBuf(sf::Sound* sound, const sf::SoundBuffer* buf)
	{
		sound->setBuffer(*buf);
	}
	const sf::SoundBuffer* getBuf(const sf::Sound* sound)
	{
		return sound->getBuffer();
	}
}

void AS_SFML::priv::sound(asIScriptEngine* eng)
{
	int r;

	r = eng->RegisterObjectBehaviour("Sound", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(create_default_sound), asCALL_CDECL_OBJFIRST); asAssert(r);
	//r = eng->RegisterObjectBehaviour("Sound", asBEHAVE_CONSTRUCT, "void f(const SoundBuf@&in)", asFUNCTION(create_sound), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectBehaviour("Sound", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destroy_sound), asCALL_CDECL_OBJFIRST); asAssert(r);

	r = eng->RegisterObjectMethod("Sound", "Sound& opAssign(Sound&in)", asMETHOD(sf::Sound, operator=), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sound", "void SetBuf(const SoundBuf@)", asFUNCTION(setBuf), asCALL_CDECL_OBJFIRST); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "const SoundBuf@ SetBuf() const", asFUNCTION(getBuf), asCALL_CDECL_OBJFIRST); asAssert(r);

	audio_common("Sound", eng);

	r = eng->RegisterObjectMethod("Sound", "void Play()", asMETHOD(sf::Sound, play), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void Pause()", asMETHOD(sf::Sound, pause), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void Stop()", asMETHOD(sf::Sound, stop), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sound", "sf::Audio::Status get_Status() const", asMETHOD(sf::Sound, getStatus), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "bool get_Looping() const", asMETHOD(sf::Sound, getLoop), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void set_Looping(bool loop)", asMETHOD(sf::Sound, setLoop), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sound", "float get_Pitch() const", asMETHOD(sf::Sound, getPitch), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void set_Pitch(float pitch) const", asMETHOD(sf::Sound, setPitch), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "float get_Volume() const", asMETHOD(sf::Sound, getVolume), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void set_Volume(float volume) const", asMETHOD(sf::Sound, setVolume), asCALL_THISCALL); asAssert(r);
}

void AS_SFML::priv::sound(CSerializer* ser)
{
	ser->AddUserType(new CSFMLType<sf::Sound>(), "Sound");
}
