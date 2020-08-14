#include "Menu.hpp"

#include "Window.hpp"
#include "StateManager.hpp"
#include "Tir.hpp"
#include "Explosion.hpp"

#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"


int MenuChoice = 0;


enum class Menus
{
	MAIN,
	PLAY,
	SCOREBOARDS,
	OPTIONS,
	CREDITS,

	HOW_PLAY,
};
Menus ActualMenu;

void UpdateMenu()
{
	switch (ActualMenu)
	{

	case Menus::MAIN:
		UpdateMainMenu();
		break;
	case Menus::PLAY:
		UpdatePlayMenu();
		break;
	case Menus::SCOREBOARDS:
		break;
	case Menus::OPTIONS:
		break;
	case Menus::CREDITS:
		UpdateCredits();
		break;
	case Menus::HOW_PLAY:
		break;

	default:
		break;
	}
}

void UpdateMainMenu()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	for (Sound& ActualSound : SoundList)
		ActualSound.update();
	// musics
	/*if (sfMusic_getStatus(Menu_music.music) == sfStopped)
	{
		sfMusic_stop(Boss_music.music);
		sfMusic_stop(Game_music.music);
		sfMusic_play(Menu_music.music);
		sfMusic_setLoop(Menu_music.music, sfTrue);
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice > 0)
		{
			MenuChoice--;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice < 4)
		{
			MenuChoice++;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		switch (MenuChoice)
		{
		case 0:
			getSound("menu_click").play();
			ActualMenu = Menus::PLAY;
			break;
		case 1:
			getSound("menu_click").play();
			//ActualMenu = Menus::SCOREBOARDS;
			break;
		case 2:
			getSound("menu_click").play();
			//ActualMenu = Menus::OPTIONS;
			break;
		case 3:
			getSound("menu_click").play();
			ActualMenu = Menus::CREDITS;
			break;
		case 4:
			getSound("menu_click").play();
			win.Window().close();
			break;

		default:
			break;
		}
	}
}
void UpdatePlayMenu()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	for (Sound& ActualSound : SoundList)
		ActualSound.update();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice > 0)
		{
			MenuChoice--;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice < 2)
		{
			MenuChoice++;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		switch (MenuChoice)
		{
		case 0:
			getSound("menu_click").play();
			break;
		case 1:
			getSound("menu_click").play();
			break;
		case 2:
			getSound("menu_click").play();
			ActualMenu = Menus::HOW_PLAY;
			break;

		default:
			break;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		MenuChoice = 0;
		ActualMenu = Menus::MAIN;
	}
}
void UpdateCredits()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		ActualMenu = Menus::MAIN;
	}
}






void DisplayMenu()
{
	switch (ActualMenu)
	{

	case Menus::MAIN:
		DisplayMainMenu();
		break;
	case Menus::PLAY:
		DisplayPlayMenu();
		break;
	case Menus::SCOREBOARDS:
		break;
	case Menus::OPTIONS:
		break;
	case Menus::CREDITS:
		DisplayCredits();
		break;
	case Menus::HOW_PLAY:
		DisplayHowToPlay();
		break;

	default:
		break;
	}
}

void DisplayMainMenu()
{
	sf::Text buttons_text("", Font, 70);
	std::string Textyes[5]{ "Jouer","ScoreBoards","Options","Credits","Quitter" };
	sf::Vector2f TextPos[5]{ sf::Vector2f(850,50),sf::Vector2f(975,265), sf::Vector2f(850,450), sf::Vector2f(1000,650), sf::Vector2f(845,850) };

	win.Window().draw(getSprite("Fond_menu2"));

	for (int i = 0; i < 5; i++)
	{
		if (i == MenuChoice)
		{
			getSprite("Button").setTextureRect(sf::IntRect(477, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Color(180, 50, 0));
		}
		else
		{
			getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Black);
		}

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 200 * i + getSprite("Button").getGlobalBounds().height));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250, 200 * i ));
		}

		if (i == 1)
			buttons_text.setCharacterSize(50);
		else
			buttons_text.setCharacterSize(70);

		buttons_text.setString(Textyes[i]);
		buttons_text.setPosition(TextPos[i]);

		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}
}
void DisplayPlayMenu()
{
	sf::Text buttons_text("", Font, 70);
	std::string Textyes[3]{ "Solo","Coop","Comment jouer" };
	sf::Vector2f TextPos[3]{ sf::Vector2f(850,55),sf::Vector2f(1020,245), sf::Vector2f(800,450) };
	sf::Text Return("B Retour", Font, 75);

	win.Window().draw(getSprite("Fond_menu2"));

	for (int i = 0; i < 3; i++)
	{
		if (i == MenuChoice)
		{
			getSprite("Button").setTextureRect(sf::IntRect(477, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Color(180, 50, 0));
		}
		else
		{
			getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Black);
		}

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 200 * i + getSprite("Button").getGlobalBounds().height));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250, 200 * i));
		}

		buttons_text.setString(Textyes[i]);
		buttons_text.setPosition(TextPos[i]);

		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}

	
	Return.setFillColor(sf::Color::Color(180, 50, 0));
	Return.setPosition(1300, 800);
	win.Window().draw(Return);
}
void DisplayCredits()
{
	sf::Text Return("B Retour", Font, 75);
	Return.setFillColor(sf::Color::Color(180, 50, 0));
	Return.setPosition(1500,940);

	win.Window().draw(getSprite("Credits"));
	win.Window().draw(Return);

}
void DisplayHowToPlay()
{
	sf::IntRect PlayerRect(0,0,62,101);
	sf::Vector2f PlayersPos[4]{ sf::Vector2f(500,800),sf::Vector2f(850,800) ,sf::Vector2f(1200,800) ,sf::Vector2f(1400,800) };
	getSprite("Joueur1").setTextureRect(PlayerRect);
	getSprite("Joueur1").setOrigin(getSprite("Joueur1").getGlobalBounds().width / 2, getSprite("Joueur1").getGlobalBounds().height / 2);
	
	win.Window().draw(getSprite("Comment_jouer"));

	for (int i = 0; i < 4; i++)
	{
		getSprite("Joueur1").setPosition(PlayersPos[i]);
		win.Window().draw(getSprite("Joueur1"));
	}

	getSprite("XP").setPosition(1185, 925);
	win.Window().draw(getSprite("XP"));
	getSprite("XpBar").setPosition(1185 - 51, 925 - 22);
	win.Window().draw(getSprite("XpBar"));

}