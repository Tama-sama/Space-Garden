#pragma once
#include "Tools.hpp"
#include "StateManager.hpp"
#include "RessourcesManager.hpp"


class Sound
{
public:
	Sound(std::string Name, State _state, std::string Path)
	{
		m_name = Name;
		m_state = _state;

		if (m_Buffer.loadFromFile(Path))
		{
			m_sound.setBuffer(m_Buffer);	// need to redo it beacause the address is moved when pushback
		}
		else
		{
			std::cout << "ERROR: sounds : " << m_name << " didn't load" << std::endl;
		}
	};
	~Sound() {};

	std::string getName() const { return m_name; };
	sf::Sound& getSound() { return m_sound; };
	sf::SoundBuffer& getSoundBuffer() { return m_Buffer; };
	void update() 
	{ 
		if (m_sound.getStatus() != sf::Sound::Playing)
			m_sound.setBuffer(m_Buffer); 
	};

	bool operator == (const Sound& s) const { return m_name == s.m_name && m_state == s.m_state; };
	bool operator != (const Sound& s) const { return !operator==(s); };

private:
	std::string m_name;
	//RessourceType m_type;
	State m_state;
	sf::SoundBuffer m_Buffer;
	sf::Sound m_sound;
	float m_volume_multi;

};


extern std::list<Sound> SoundList;

void LoadSounds(State _state);
sf::Sound& getSound(std::string Name);
void RemoveAllSounds();

