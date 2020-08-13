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
			m_sound.setBuffer(m_Buffer);
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

private:
	std::string m_name;
	//RessourceType m_type;
	State m_state;
	sf::SoundBuffer m_Buffer;
	sf::Sound m_sound;
	float m_volume_multi;

};



//struct Sound
//{
//	Sound(std::string Name) { name = Name; };
//
//	std::string name;
//	RessourceType type;
//	State state;
//	float volume_multi;
//
//	sf::SoundBuffer Buffer;
//	sf::Sound sound;
//
//	//sf::Music music;
//};
extern std::list<Sound> SoundList;

void LoadSounds(State _state);
sf::Sound& getSound(std::string Name);

