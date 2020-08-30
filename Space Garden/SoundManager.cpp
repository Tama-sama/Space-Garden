#include "SoundManager.hpp"

std::list<Sound> SoundList;
std::list<Musics*> MusicList;
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
			else if (ActualRessource.type == RessourceType::MUSIC)
			{
				Musics* ConstructMusic = new Musics;
				ConstructMusic->Construct(ActualRessource.name, ActualRessource.state, ActualRessource.path, ActualRessource.soundmultiplier);

				MusicList.push_back(ConstructMusic);
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

sf::Music& getMusic(std::string Name)
{
	for (Musics* ActualMusic : MusicList)
	{
		if (ActualMusic->getName() == Name)
		{
			return ActualMusic->getMusic();
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

		for (Musics* ActualMusic : MusicList)
		{
			if (ActualMusic->getState() != State::ALL)
			{
				delete ActualMusic;
				MusicList.remove(ActualMusic);
				Removed = true;
				break;
			}
		}
	}
}


void MusicPlayManager()
{
	if (state == State::MAIN_MENU || state == State::SAVE)// Music Menu charger tous le temps
	{
		getMusic("Menu").setLoop(true);
		if (getMusic("Menu").getStatus() != sf::Music::Playing)
			getMusic("Menu").play();
	}
	else
	{
		if (getMusic("Menu").getStatus() == sf::Music::Playing)
			getMusic("Menu").stop();
	}

	if (state == State::GAME)	// Music Game et boss charger que dans le state Game
	{
		// si se n'est pas le boss
		getMusic("Game").setLoop(true);
		if (getMusic("Game").getStatus() != sf::Music::Playing)
			getMusic("Game").play();
		// else si c'est le boss
		// To Do ...
	}
}