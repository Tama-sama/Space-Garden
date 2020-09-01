#include "StateManager.hpp"
#include "Window.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"
#include "Controles.hpp"

#include "Explosion.hpp"
#include "Tir.hpp"
#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Buffs.hpp"

#include "Menu.hpp"
#include "Game.hpp"


#pragma warning(disable : 26812)


State state = State::INTRO;
extern bool changingkey;
extern Controle* ChangingControle;
extern bool isPause;

void UpdateSave();
void DisplaySave();

void ChangeState(State NextState)
{
	RemoveAllSounds();
	RemoveAllSprites();

	state = NextState;
	
	LoadSounds(NextState);
	LoadSprite(NextState);
	InitManager();
}

void InitManager()
{
	static bool FirstInit = false;
	if (!FirstInit)
	{
		Font.loadFromFile("../Ressources/Otto.ttf");

		getSprite("JoueurR").setTextureRect(sf::IntRect(0, 0, 62, 101));
		getSprite("JoueurR").setOrigin(getSprite("JoueurR").getGlobalBounds().width / 2, getSprite("JoueurR").getGlobalBounds().height / 2);
		
		getSprite("JoueurB").setTextureRect(sf::IntRect(0, 0, 62, 101));
		getSprite("JoueurB").setOrigin(getSprite("JoueurB").getGlobalBounds().width / 2, getSprite("JoueurB").getGlobalBounds().height / 2);
		
		getSprite("JoueurG").setTextureRect(sf::IntRect(0, 0, 62, 101));
		getSprite("JoueurG").setOrigin(getSprite("JoueurG").getGlobalBounds().width / 2, getSprite("JoueurG").getGlobalBounds().height / 2);
		
		getSprite("JoueurN").setTextureRect(sf::IntRect(0, 0, 62, 101));
		getSprite("JoueurN").setOrigin(getSprite("JoueurN").getGlobalBounds().width / 2, getSprite("JoueurN").getGlobalBounds().height / 2);
		
		getSprite("JoueurV").setTextureRect(sf::IntRect(0, 0, 62, 101));
		getSprite("JoueurV").setOrigin(getSprite("JoueurV").getGlobalBounds().width / 2, getSprite("JoueurV").getGlobalBounds().height / 2);

		FirstInit = true;
	}

	switch (state)
	{
	case State::MAIN_MENU:
		break;

	case State::GAME:
		break;

	default:
		break;
	}
}

void UpdateManager()
{
	// Events
	EventsManager();

	//restart of the clock (time per frame)
	MainTime.RestartClock();

	for (Sound& ActualSound : SoundList)
		ActualSound.update();

	for (Musics* ActualMusic : MusicList)
		ActualMusic->update();
	MusicPlayManager();

	switch (state)
	{
	case State::MAIN_MENU :
		UpdateMenu();
		break;

	case State::GAME:
		if (!isPause)
			UpdateGame();
		else
			UpdateGamePause();
		break;

	case State::SAVE:
		UpdateSave();
		break;

	default:
		break;
	}
}



void DisplayManager()
{

	// apply view for screen size adaptation
	win.Window().setView(win.getView().View());

	// Clear the Window
	win.Window().clear(sf::Color::Color(0, 100, 0));


	switch (state)
	{
	case State::INTRO:
		Intro();
		break;

	case State::MAIN_MENU:
		DisplayMenu();
		break;

	case State::GAME:
		DisplayGame();

		if (isPause)
			DisplayGamePause();

		break;

	case State::SAVE:
		DisplaySave();
		break;

	default:
		break;
	}



	std::string DebugInfos;
	DebugInfos += "Ressources registered : " + std::to_string(RessourcesList.size()) + "\n";
	DebugInfos += "Textures / Sprites Loaded : " + std::to_string(SpriteList.size()) + "\n";
	DebugInfos += "Sounds Loaded : " + std::to_string(SoundList.size()) + "\n";
	DebugInfos += "Music Loaded : " + std::to_string(MusicList.size()) + "\n";
	DebugInfos += "\n";
	DebugInfos += "Player Bullets : " + std::to_string(Bullets.size()) + "\n";
	DebugInfos += "Ennemies Bullets : " + std::to_string(EnnemiesShootsList.size()) + "\n";
	DebugInfos += "Ennemies : " + std::to_string(ennemies.size()) + "\n";
	DebugInfos += "Buffs : " + std::to_string(BuffsList.size()) + "\n";
	DebugInfos += "Explosions : " + std::to_string(Explosions.size()) + "\n";


	sf::Text DebugText(DebugInfos, Font, 45);
	DebugText.setPosition(245, 0);

	sf::RectangleShape BackGround(sf::Vector2f(DebugText.getGlobalBounds().width + 10, DebugText.getGlobalBounds().height));
	BackGround.setPosition(240, 0);
	BackGround.setFillColor(sf::Color::Color(0,0,0,75));

	win.Window().draw(BackGround);
	win.Window().draw(DebugText);


	// Display on window
	win.Window().display();
}

extern std::string a;
extern std::string b;
extern bool NameDone[2];

void EventsManager()
{
	while (win.Window().pollEvent(win.Events()))
	{
		if (win.Events().type == sf::Event::Closed)
			win.Window().close();

		if (win.Events().type == sf::Event::KeyPressed)
		{
			if (changingkey)
			{
				ChangingControle->KeyBoard = win.Events().key.code;
				changingkey = false;
				ChangingControle = 0;
			}

			PressedKey.push_back(win.Events().key.code);
		}

		if (win.Events().type == sf::Event::KeyReleased)
		{
			PressedKey.remove(win.Events().key.code);
		}

		for (int i = 0; i < 8; i++)
		{
			GamepadManager(i, win.Events());
		}

		if (state == State::SAVE)
		{
			if (Player1.getController() == 8 || Player2.getController() == 8)
			{
				if (win.Events().type == sf::Event::TextEntered)
				{
					std::string* ptName;
					int i = 0;

					if (Player1.getController() == 8)
					{
						ptName = &a;
						i = 0;
					}
					else
					{
						ptName = &b;
						i = 1;
					}

					if (!NameDone[i])
					{
						if ((win.Events().text.unicode >= 'A' && win.Events().text.unicode <= 'Z') ||
							(win.Events().text.unicode >= 'a' && win.Events().text.unicode <= 'z'))
						{
							if (ptName->size() < 10)
							{
								*ptName += win.Events().text.unicode;
							}
						}
						else if (win.Events().text.unicode == 8 && ptName->size() > 0)
						{
							ptName->pop_back();
						}
					}
				}
			}
		}
	}
}