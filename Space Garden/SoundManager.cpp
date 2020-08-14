#include "SoundManager.hpp"

std::list<Sound> SoundList;

void LoadSounds(State _state)
{
	for (Ressources& ActualRessource : RessourcesList)
	{
		if (ActualRessource.state == _state)
		{
			if (ActualRessource.type == RessourceType::SOUNDFX)
			{
				SoundList.push_back(Sound(ActualRessource.name, ActualRessource.state, ActualRessource.path));
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
	while (SoundList.size() != 0)
	{
		for (Sound& ActualSound : SoundList)
		{
			SoundList.remove(ActualSound);
			break;
		}
	}
}