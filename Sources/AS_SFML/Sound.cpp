#include "Internal.hpp"
#include <SFML/Audio/Sound.hpp>

void AS_SFML::priv::sound(asIScriptEngine* eng)
{
	int r;

	audio_common("Sound", eng);

	r = eng->RegisterObjectMethod("Sound", "void Play()", asMETHOD(sf::Sound, play), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void Pause()", asMETHOD(sf::Sound, pause), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void Stop()", asMETHOD(sf::Sound, stop), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Sound", "Audio::Status get_Status() const", asMETHOD(sf::Sound, getStatus), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "bool get_Looping() const", asMETHOD(sf::Sound, getLoop), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Sound", "void set_Looping(bool loop)", asMETHOD(sf::Sound, setLoop), asCALL_THISCALL); asAssert(r);
}
