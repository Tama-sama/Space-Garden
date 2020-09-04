#include "StateManager.hpp"
#include "Window.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"
#include "Controles.hpp"
#include "StringManager.hpp"

#include "Explosion.hpp"
#include "Tir.hpp"
#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Buffs.hpp"

#include "Menu.hpp"
#include "Game.hpp"


#pragma warning(disable : 26812)

State state = State::INTRO;

bool DebugsInfos = false;

bool Loading = false;
bool can_Switch = false;
sf::Mutex MutexTest;

extern bool changingkey;
extern Controle* ChangingControle;
extern bool isPause;

void UpdateSaveToMenu();
void UpdateSave();
void DisplaySave();
void DisplayDevMode();

void ChangeState(State NextState)
{
	RemoveAllSounds();
	RemoveAllSprites();
	RemoveAllStrings();

	state = NextState;
	
	LoadSounds(NextState);
	LoadSprite(NextState);
	LoadStrings(NextState);
	InitManager();
}

void LoadNextState(State NextState)
{
	Loading = true;
	can_Switch = false;

	LoadSprite(NextState);
	LoadSounds(NextState);
	LoadStrings(NextState);
	InitManager();

	Loading = false;
	can_Switch = true;
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
		if (!Loading && !can_Switch)		
			UpdateMenu();
		else
			UpdateMenuToGame();

		break;

	case State::GAME:
		if (!isPause)
		{
			if (!Loading && !can_Switch)
				UpdateGame();
			else
				UpdateGameToSave();
		}
		else
		{
			if (!Loading && !can_Switch)
				UpdateGamePause();
			else
				UpdateGameToMenu();
		}
		break;

	case State::SAVE:
		if (!Loading && !can_Switch)
			UpdateSave();
		else
			UpdateSaveToMenu();
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

	static float dots = 0;
	if (Loading)
	{
		dots += MainTime.GetTimeDeltaF();

		sf::Text LoadingText("Loading", Font, 70);
		LoadingText.setFillColor(sf::Color::Black);
		LoadingText.setPosition(1700, 20);

		if (dots >= 0.2f)
			LoadingText.setString("Loading .");
		if (dots >= 0.4f)
			LoadingText.setString("Loading ..");
		if (dots >= 0.6f)
			LoadingText.setString("Loading ...");
		if (dots >= 0.8f)
			dots = 0.f;

		win.Window().draw(LoadingText);
	}
	else
		dots = 0.f;


	if (DebugsInfos)
		DisplayDevMode();

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

			if (win.Events().key.code == sf::Keyboard::F8)
			{
				DebugsInfos = !DebugsInfos;
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








void DisplayDevMode()
{
	sf::RectangleShape RectHitBox;
	sf::CircleShape CircleHitBox;

	RectHitBox.setFillColor(sf::Color::Transparent);
	RectHitBox.setOutlineColor(sf::Color::Blue);
	RectHitBox.setOutlineThickness(1);

	CircleHitBox.setFillColor(sf::Color::Transparent);
	CircleHitBox.setOutlineColor(sf::Color::Blue);
	CircleHitBox.setOutlineThickness(1);

	for (Buffs& ActualBuff : BuffsList)
	{
		RectHitBox.setSize(sf::Vector2f(SIZE_BUFFS, SIZE_BUFFS));
		RectHitBox.setOrigin(SIZE_BUFFS / 2, SIZE_BUFFS / 2);
		RectHitBox.setPosition(ActualBuff.getpos());
		win.Window().draw(RectHitBox);
	}

	for (PlayerBullet& ActualPlayerBullet : Bullets)
	{
		CircleHitBox.setRadius(RADIUS_PLAYER_SHOOT);
		CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
		CircleHitBox.setPosition(ActualPlayerBullet.Pos());
		win.Window().draw(CircleHitBox);
	}

	for (EnnemiesShoots& ActualEnnemieBullet : EnnemiesShootsList)
	{
		CircleHitBox.setRadius(RADIUS_ENNEMIES_SHOOT);
		CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
		CircleHitBox.setPosition(ActualEnnemieBullet.getpos());
		win.Window().draw(CircleHitBox);
	}

	for (Ennemies& ActualEnnemie : ennemies)
	{
		CircleHitBox.setRadius(RADIUS_ENNEMIES);
		CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
		CircleHitBox.setPosition(ActualEnnemie.getPos());
		win.Window().draw(CircleHitBox);
	}

	if (state == State::GAME)
	{
		RectHitBox.setSize(sf::Vector2f(getSprite(Player1.getShip()).getGlobalBounds().width, getSprite(Player1.getShip()).getGlobalBounds().height));
		RectHitBox.setOrigin(RectHitBox.getSize().x / 2, RectHitBox.getSize().y / 2);
		RectHitBox.setPosition(Player1.getPosition());
		win.Window().draw(RectHitBox);

		RectHitBox.setSize(sf::Vector2f(getSprite(Player2.getShip()).getGlobalBounds().width, getSprite(Player2.getShip()).getGlobalBounds().height));
		RectHitBox.setOrigin(RectHitBox.getSize().x / 2, RectHitBox.getSize().y / 2);
		RectHitBox.setPosition(Player2.getPosition());
		win.Window().draw(RectHitBox);
	}

	std::string DebugInfos;
	DebugInfos += "Ressources registered : " + std::to_string(RessourcesList.size()) + "\n";
	DebugInfos += "Textures / Sprites Loaded : " + std::to_string(SpriteList.size()) + "\n";
	DebugInfos += "Sounds Loaded : " + std::to_string(SoundList.size()) + "\n";
	DebugInfos += "Music Loaded : " + std::to_string(MusicList.size()) + "\n";
	DebugInfos += "Strings Loaded : " + std::to_string(StringsList.size()) + "\n";
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
	BackGround.setFillColor(sf::Color::Color(0, 0, 0, 75));

	win.Window().draw(BackGround);
	win.Window().draw(DebugText);
}