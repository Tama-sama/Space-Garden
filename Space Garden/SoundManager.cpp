#include "SoundManager.hpp"

std::list<Sound> SoundList;
int MusicMultip = 50;
int SoundMultip = 30;


void LoadSounds(State _state)
{
	for (Ressources& ActualRessource : RessourcesList)
	{
		if (ActualRessource.state == _state)
		{
			if (ActualRessource.type == RessourceType::SOUNDFX)
			{
				SoundList.push_back(Sound(ActualRessource.name, ActualRessource.state, ActualRessource.path, ActualRessource.soundmultiplier));
			}

		}
	}
}

sf::Sound& getSound(std::string Name)
{
	for (Sound& ActualSound : SoundList)
	{
		if (ActualSound.getName() == Name)
		{
			return ActualSound.getSound();
		}
	}
}

void RemoveAllSounds()
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Sound& ActualSound : SoundList)
		{
			if (ActualSound.getState() != State::ALL)
			{
				SoundList.remove(ActualSound);
				Removed = true;
				break;
			}
		}
	}
}