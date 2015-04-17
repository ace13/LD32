#include "Internal.hpp"
#include <SFML/Audio/Music.hpp>

void AS_SFML::priv::music(asIScriptEngine* eng)
{
	int r;

	audio_common("Music", eng);

	r = eng->RegisterObjectMethod("Music", "void Play()", asMETHOD(sf::Music, play), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "void Pause()", asMETHOD(sf::Music, pause), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "void Stop()", asMETHOD(sf::Music, stop), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Music", "sf::Audio::Status get_Status() const", asMETHOD(sf::Music, getStatus), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "bool get_Looping() const", asMETHOD(sf::Music, getLoop), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "void set_Looping(bool loop)", asMETHOD(sf::Music, setLoop), asCALL_THISCALL); asAssert(r);

	r = eng->RegisterObjectMethod("Music", "float get_Pitch() const", asMETHOD(sf::Music, getPitch), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "void set_Pitch(float pitch) const", asMETHOD(sf::Music, setPitch), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "float get_Volume() const", asMETHOD(sf::Music, getVolume), asCALL_THISCALL); asAssert(r);
	r = eng->RegisterObjectMethod("Music", "void set_Volume(float volume) const", asMETHOD(sf::Music, setVolume), asCALL_THISCALL); asAssert(r);
}

void AS_SFML::priv::audio_common(const char* name, asIScriptEngine* eng)
{
	static bool first = true;
	int r;

	if (first)
	{
		first = false;

		r = eng->SetDefaultNamespace("sf::Audio"); asAssert(r);

		r = eng->RegisterEnum("Status"); asAssert(r);
		r = eng->RegisterEnumValue("Status", "Stopped", sf::SoundSource::Stopped); asAssert(r);
		r = eng->RegisterEnumValue("Status", "Paused", sf::SoundSource::Paused); asAssert(r);
		r = eng->RegisterEnumValue("Status", "Playing", sf::SoundSource::Playing); asAssert(r);

		r = eng->SetDefaultNamespace("sf"); asAssert(r);
	}

}
