#include "Menu.hpp"

#include "Window.hpp"
#include "StateManager.hpp"

#include "Tir.hpp"
#include "Explosion.hpp"
#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Player.hpp"
#include "Buffs.hpp"
#include "Controles.hpp"

#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"
#include "Game.hpp"

int MenuChoice = 0;

// how to play
Player Tutos[4]{ Player(sf::Vector2f(500,800), 1 ,0),Player(sf::Vector2f(850,800),1, 0),Player(sf::Vector2f(1200,800),1, 0),Player(sf::Vector2f(1400,800),1, 0) };

enum class Menus
{
	MAIN,
	SELECTION,
	SCOREBOARDS,
	OPTIONS,
	CREDITS,

	HOW_PLAY,
};
Menus ActualMenu;

std::string To_String(Action _Action);

// options
bool OptionChangeKeys = false;
std::string ret;
#define ITEM(x) case sf::Keyboard:: ## x : ret = #x; break;
#define ITEM2(x) case gamepadPS4:: ## x : ret = #x; break;
int changeKeyChoice = 0;
bool changingkey = false;
Controle* ChangingControle = 0;
extern bool SoloGame;
bool Readys[2] = { false,false };


int ScoreBoardSeen = 1;
std::string SoloLines[5] = {"#1 - Nobody - 000","#2 - Nobody - 000","#3 - Nobody - 000","#4 - Nobody - 000","#5 - Nobody - 000"};
std::string DuoLines[5];

// Linenumber // playernumber
char ShipsColorsSolo[5] = { 'R','R','R','R','R'};
char ShipsColorsDuo[5][2] = { 'R','R','R','R','R',	'R','R','R','R','R' };

void UpdateMenu()
{
	switch (ActualMenu)
	{

	case Menus::MAIN:
		UpdateMainMenu();
		break;

	case Menus::SELECTION:
		UpdateShipMenu();
		break;

	case Menus::SCOREBOARDS:
		UpdateScoreBoardMenu();
		break;

	case Menus::OPTIONS:
		UpdateOptionMenu();
		break;

	case Menus::CREDITS:
		UpdateCredits();
		break;

	case Menus::HOW_PLAY:
		UpdateHowToPlay();
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

	if (isButtonPressed(Action::Up) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice > 0)
		{
			MenuChoice--;
		}
	}
	if (isButtonPressed(Action::Down) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice < 5)
		{
			MenuChoice++;
		}
	}
	
	for (int i = 0; i < 9; i++)
	{
		if (isButtonPressed(Action::Interact, i) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			switch (MenuChoice)
			{
			case 0:
				getSound("menu_click").play();
				Player1.setController(i);
				SoloGame = true;
				ActualMenu = Menus::SELECTION;
				break;
			case 1:
				getSound("menu_click").play();
				ActualMenu = Menus::SCOREBOARDS;
				break;
			case 2:
				getSound("menu_click").play();
				ActualMenu = Menus::OPTIONS;
				break;
			case 3:
				getSound("menu_click").play();
				ActualMenu = Menus::HOW_PLAY;
				break;
			case 4:
				getSound("menu_click").play();
				ActualMenu = Menus::CREDITS;
				break;

			case 5:
				getSound("menu_click").play();
				win.Window().close();
				break;

			default:
				break;
			}
		}
	}
}
void UpdateShipMenu()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	if (SoloGame)
	{
		for (int i = 0; i < 9; i++)
		{
			if (i != Player1.getController())
			{
				if (isButtonPressed(Action::Interact, i))
				{
					ActionTiming = 0;
					SoloGame = false;
					Player2.setController(i);
					if (Player1.getShip() == "JoueurB")
						Player2.setShip('R');
					else
						Player2.setShip('B');
				}
			}
		}

		if (isButtonPressed(Action::Right, Player1.getController()) && ActionTiming >= 0.3f)
		{
			ActionTiming = 0;
			if (Player1.getShip() == "JoueurR")
				Player1.setShip('B');
			else if (Player1.getShip() == "JoueurB")
				Player1.setShip('V');
			else if (Player1.getShip() == "JoueurV")
				Player1.setShip('G');
			else if (Player1.getShip() == "JoueurG")
				Player1.setShip('N');
		}

		if (isButtonPressed(Action::Left, Player1.getController()) && ActionTiming >= 0.3f)
		{
			ActionTiming = 0;
			if (Player1.getShip() == "JoueurN")
				Player1.setShip('G');
			else if (Player1.getShip() == "JoueurG")
				Player1.setShip('V');
			else if (Player1.getShip() == "JoueurV")
				Player1.setShip('B');
			else if (Player1.getShip() == "JoueurB")
				Player1.setShip('R');
		}
	
		if (isButtonPressed(Action::Interact, Player1.getController()) && ActionTiming >= 0.3f)
		{
			ActionTiming = 0;
			GameInit();
			ChangeState(State::GAME);

			// Menu Reset
			ActualMenu = Menus::MAIN;
			MenuChoice = 0;
		}

		if (isButtonPressed(Action::Return, Player1.getController()) && ActionTiming >= 0.3f)
		{
			ActionTiming = 0;
			
			getSound("menu_click").play();
			ActualMenu = Menus::MAIN;
		}
	}
	else
	{
		if (Readys[0] && Readys[1])
		{
			GameInit();
			ChangeState(State::GAME);

			// Menu Reset
			Readys[0] = false;
			Readys[1] = false;
			ActualMenu = Menus::MAIN;
			MenuChoice = 0;
		}

		for (int i = 0; i < 9; i++)
		{
			if (isButtonPressed(Action::Interact, i) && ActionTiming >= 0.3f)
			{
				if (i == Player1.getController() && !Readys[0])
				{
					ActionTiming = 0;
					Readys[0] = true;
				}
				else if (i == Player2.getController() && !Readys[1])
				{
					ActionTiming = 0;
					Readys[1] = true;
				}
			}

			if (isButtonPressed(Action::Return, i) && ActionTiming >= 0.3f)
			{
				ActionTiming = 0;
				if (i == Player1.getController())
				{
					if (Readys[0])
					{
						Readys[0] = false;
					}
					else
					{
						Readys[1] = false;
						getSound("menu_click").play();
						ActualMenu = Menus::MAIN;
					}
				}
				else if (i == Player2.getController())
				{
					if (Readys[1])
					{
						Readys[1] = false;
					}
					else
					{
						Readys[0] = false;
						getSound("menu_click").play();
						ActualMenu = Menus::MAIN;
					}
				}
			}
		}
	}
}
void UpdateScoreBoardMenu()
{
	static bool NeedReload = true;
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (isButtonPressed(Action::Return) && ActionTiming >= 0.3)
	{
		NeedReload = true;
		ActionTiming = 0;
		getSound("menu_click").play();
		ActualMenu = Menus::MAIN;
	}

	if (isButtonPressed(Action::Left) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (ScoreBoardSeen == 2)
			ScoreBoardSeen = 1;
	}

	if (isButtonPressed(Action::Right) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (ScoreBoardSeen == 1)
			ScoreBoardSeen = 2;
	}

	if (NeedReload)
	{
		NeedReload = false;

		std::ifstream FileRead("../Ressources/Score Solo.txt");

		if (FileRead.is_open())
		{
			std::string Names[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };
			int Scores[5] = { 0,0,0,0,0 };

			for (int i = 0; i < 5; i++)
			{
				std::getline(FileRead, SoloLines[i]);
				ShipsColorsSolo[i] = SoloLines[i].c_str()[0];
				SoloLines[i].erase(0, 2);
				Names[i] = SoloLines[i].substr(0, SoloLines[i].find(" "));
				SoloLines[i].erase(0, Names[i].size() + 1);
				Scores[i] = std::stoi(SoloLines[i]);

				SoloLines[i] = "#" + std::to_string(i + 1) + " - " + Names[i] + " - " + std::to_string(Scores[i]) + "\n";
			}
			FileRead.close();
		}

		FileRead.open("../Ressources/Score Duo.txt");
		if (FileRead.is_open())
		{
			std::string NamesP1[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };
			int ScoresP1[5] = { 0,0,0,0,0 };
			int ScoresTotal[5] = { 0,0,0,0,0 };
			int ScoresP2[5] = { 0,0,0,0,0 };
			std::string NamesP2[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };

			for (int i = 0; i < 5; i++)
			{
				std::getline(FileRead, DuoLines[i]);

				ShipsColorsDuo[i][0] = DuoLines[i].c_str()[0];
				DuoLines[i].erase(0, 2);

				NamesP1[i] = DuoLines[i].substr(0, DuoLines[i].find(" "));
				DuoLines[i].erase(0, NamesP1[i].size() + 1);

				ScoresP1[i] = std::stoi(DuoLines[i].substr(0, DuoLines[i].find(" ")));
				DuoLines[i].erase(0, std::to_string(ScoresP1[i]).size() + 1);

				ScoresTotal[i] = std::stoi(DuoLines[i].substr(0, DuoLines[i].find(" ")));
				DuoLines[i].erase(0, std::to_string(ScoresTotal[i]).size() + 1);

				ScoresP2[i] = std::stoi(DuoLines[i].substr(0, DuoLines[i].find(" ")));
				DuoLines[i].erase(0, std::to_string(ScoresP2[i]).size() + 1);

				NamesP2[i] = DuoLines[i].substr(0, DuoLines[i].find(" "));
				DuoLines[i].erase(0, NamesP2[i].size() + 1);

				ShipsColorsDuo[i][1] = DuoLines[i].c_str()[0];

				DuoLines[i] = "#" + std::to_string(i + 1) + "       " + NamesP1[i] + " - " + std::to_string(ScoresP1[i]) + " - " + std::to_string(ScoresTotal[i]) + " - " + std::to_string(ScoresP2[i]) + " - " + NamesP2[i] + "\n";
			}
		}
	}



}
void UpdateOptionMenu()
{
	static float ActionTiming = 0.f;
	static bool Save = false;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (ChangingControle != 0)
		ActionTiming = 0.f;

	if (isButtonPressed(Action::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		Save = true;
		changeKeyChoice = 0;
		getSound("menu_click").play();

		if (!OptionChangeKeys)
			ActualMenu = Menus::MAIN;
		else if(OptionChangeKeys && !changingkey)
			OptionChangeKeys = false;
	}

	if (OptionChangeKeys && !changingkey)
	{
		if (isButtonPressed(Action::Up) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (changeKeyChoice > 0)
				changeKeyChoice--;
		}

		if (isButtonPressed(Action::Down) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (changeKeyChoice < 9)
				changeKeyChoice++;
		}

		if (isButtonPressed(Action::Interact) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;

			int i = 0;
			for (Controle& ActualControle : controles)
			{
				if (i == changeKeyChoice)
				{
					ChangingControle = &ActualControle;
				}
				i++;
			}
			changingkey = true;
		}
	}
	else if (!OptionChangeKeys)
	{
		if (isButtonPressed(Action::Up) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (changeKeyChoice > 0)
				changeKeyChoice--;
		}

		if (isButtonPressed(Action::Down) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (changeKeyChoice < 5)
				changeKeyChoice++;
		}

		if (isButtonPressed(Action::Left) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			Save = true;

			switch (changeKeyChoice)
			{
			case 1:
				if (MusicMultip > 0)
					MusicMultip--;
				ActionTiming = 0.15f;
				break;
			case 2:
				if (SoundMultip > 0)
					SoundMultip--;
				ActionTiming = 0.15f;
				break;
			case 3:
				ResetButtonsPressed();
				if (win.getStyle() == sf::Style::Default)
					win.setStyle(sf::Style::Fullscreen);
				else if (win.getStyle() == sf::Style::None)
					win.setStyle(sf::Style::Default);
				else if (win.getStyle() == sf::Style::Fullscreen)
					win.setStyle(sf::Style::None);
				break;
			case 4:
				win.setVerticalSync(!win.getVerticalSync());
				break;
			case 5:
				if (win.getFrameRate() > 30)
					win.setFrameRate(win.getFrameRate() - 5);
				ActionTiming = 0.15f;
				break;

			default:
				Save = false;
				break;
			}
		}

		if (isButtonPressed(Action::Right) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			Save = true;

			switch (changeKeyChoice)
			{
			case 1:
				if (MusicMultip < 100)
					MusicMultip++;
				ActionTiming = 0.15f;
				break;
			case 2:
				if (SoundMultip < 100)
					SoundMultip++;
				ActionTiming = 0.15f;
				break;
			case 3:
				ResetButtonsPressed();
				if (win.getStyle() == sf::Style::Default)
					win.setStyle(sf::Style::None);
				else if (win.getStyle() == sf::Style::None)
					win.setStyle(sf::Style::Fullscreen);
				else if (win.getStyle() == sf::Style::Fullscreen)
					win.setStyle(sf::Style::Default);
				break;
			case 4:
				win.setVerticalSync(!win.getVerticalSync());
				break;
			case 5:
				if (win.getFrameRate() < 240)
					win.setFrameRate(win.getFrameRate() + 5);
				ActionTiming = 0.15f;
				break;

			default:
				Save = false;
				break;
			}
		}

		if (isButtonPressed(Action::Interact) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (changeKeyChoice == 0)
			{
				OptionChangeKeys = true;
			}
		}
	}


	if (Save)
	{
		std::ofstream FileWrite("../Ressources/Infos/Settings.bin", std::ofstream::binary);
		if (FileWrite.is_open())
		{
			std::string LineToWrite;

			for (Controle& actualControl : controles)
			{
				int name = (int)actualControl.name;
				int KeyBoard = actualControl.KeyBoard;
				int PadKey = (int)actualControl.PadKey;

				FileWrite.write((char*) &name, sizeof(int));
				FileWrite.write((char*) &KeyBoard, sizeof(int));
				FileWrite.write((char*) &PadKey, sizeof(int));
				FileWrite.write((char*) &actualControl.AxisDirection, sizeof(int));
			}
			
			int Style = win.getStyle();
			bool Vsync = win.getVerticalSync();
			int Frames = win.getFrameRate();

			FileWrite.write((char*)&MusicMultip, sizeof(int));
			FileWrite.write((char*)&SoundMultip, sizeof(int));
			FileWrite.write((char*)&Style, sizeof(int));
			FileWrite.write((char*)&Vsync, sizeof(bool));
			FileWrite.write((char*)&Frames, sizeof(int));

			FileWrite.close();
			Save = false;
		}
	}
}
void UpdateCredits()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (isButtonPressed(Action::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		ActualMenu = Menus::MAIN;
	}
}
void UpdateHowToPlay()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (isButtonPressed(Action::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		
		RemoveAllBuffs();
		RemoveAllEnnemies();
		RemoveAllEnnemiesShoots();
		RemoveAllExplosions();
		RemoveAllPlayerShoots();

		ActualMenu = Menus::MAIN;
	}

	PlayerShootsColisions();

	for (Buffs& ActualBuff : BuffsList)
		ActualBuff.Update();
	BuffsCollisions(Tutos[2]);
	RemoveDeadBuffs();

	Tutos[0].TimersUpdate(MainTime.GetTimeDeltaF());
	Tutos[1].TimersUpdate(MainTime.GetTimeDeltaF());
	Tutos[2].TimersUpdate(MainTime.GetTimeDeltaF());

	static float testtimer = 5.1f;
	testtimer += MainTime.GetTimeDeltaF();
	if (testtimer >= 5)
	{
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[1].getPosition().x + 70, Tutos[1].getPosition().y - 420), 2, 10));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[1].getPosition().x + 15, Tutos[1].getPosition().y - 575), 2, 10));

		Tutos[1].SetFireSin();
		Tutos[1].addSinShoot();
		testtimer = 0;
	}
	Tutos[1].FireSin();

	static float FirePissenlitTimer = 4.1f;
	FirePissenlitTimer += MainTime.GetTimeDeltaF();
	if (FirePissenlitTimer >= 4)
	{
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x + 130, Tutos[0].getPosition().y - 440), 5));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x, Tutos[0].getPosition().y - 420), 5));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x - 130, Tutos[0].getPosition().y - 440), 5));

		Tutos[0].FirePissenlit();
		Tutos[0].addPissenlitShoot();
		FirePissenlitTimer = 0;
	}
	 
	static float FireTimer = 0;
	static bool Fireshoot[2] = { false,false };
	FireTimer += MainTime.GetTimeDeltaF();
	if (FireTimer >= 0.4)
	{
		if (!Fireshoot[0])
		{
			if (!Tutos[2].isAtkSpeActive())
				ennemies.push_back(Ennemies(sf::Vector2f(Tutos[2].getPosition().x, Tutos[2].getPosition().y - 440), 1));
			
			Tutos[2].Fire();
			Fireshoot[0] = true;
			FireTimer = 0;
		}
		else if (!Fireshoot[1])
		{
			Tutos[2].Fire();
			FireTimer = -2;
			Fireshoot[0] = false;
		}
	}


	for (Ennemies& ActualEnnemie : ennemies)
	{
		if (ActualEnnemie.getLife() <= 0)
		{
			if (ActualEnnemie.getPos().x == Tutos[2].getPosition().x)
			{
				BuffsList.push_back(Buffs(1, ActualEnnemie.getPos()));
			}

			ennemies.remove(ActualEnnemie);
			break;
		}
	}

	RemoveDeadPlayerShoots();

	for (Explosion& ActualExplosion : Explosions)
		ActualExplosion.update();	
	RemoveDeadExplosions();



	static int direction = 0;
	if (Tutos[3].getPosition().x == 1550)
		direction = 1;
	else if (Tutos[3].getPosition().x == 1400)
		direction = 0;

	if (direction == 0)
	{
		if (Tutos[3].getPosition().x < 1550)
		{
			Tutos[3].addPositionX(150 * MainTime.GetTimeDeltaF());
			Tutos[3].setLRectFrame(2);
		}
		else
			Tutos[3].setPosition(1550, Tutos[3].getPosition().y);
	}
	else
	{
		if (Tutos[3].getPosition().x > 1400)
		{
			Tutos[3].addPositionX(-150 * MainTime.GetTimeDeltaF());
			Tutos[3].setLRectFrame(3);
		}
		else
			Tutos[3].setPosition(1400, Tutos[3].getPosition().y);
	}
}



void DisplayMenu()
{
	switch (ActualMenu)
	{
	case Menus::MAIN:
		DisplayMainMenu();
		break;

	case Menus::SELECTION:
		DisplayShipSelection();
		break;

	case Menus::SCOREBOARDS:
		DisplayScoreBoardMenu();
		break;

	case Menus::OPTIONS:
		DisplayOptionMenu();
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
	std::string Textyes[6]{ "Jouer","ScoreBoards","Options","How To Play","Credits","Quitter" };
	sf::Vector2f TextPos[6]{ sf::Vector2f(850,50),sf::Vector2f(975,235), sf::Vector2f(840,395), sf::Vector2f(960,580), sf::Vector2f(820,735), sf::Vector2f(990,900) };

	win.Window().draw(getSprite("Fond_menu2"));

	for (int i = 0; i < 6; i++)
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
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 170 * i + getSprite("Button").getGlobalBounds().height));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600.f + 250.f, 170.f * i ));
		}

		if (i == 1 || i == 3)
			buttons_text.setCharacterSize(50);
		else
			buttons_text.setCharacterSize(70);

		buttons_text.setString(Textyes[i]);
		buttons_text.setPosition(TextPos[i]);

		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}
}
void DisplayShipSelection()
{
	win.Window().draw(getSprite("Fond_menu2"));

	getSprite("JoueurR").setPosition(690,850);
	getSprite("JoueurB").setPosition(890,850);
	getSprite("JoueurV").setPosition(1090,850);
	getSprite("JoueurG").setPosition(1290,850);
	getSprite("JoueurN").setPosition(1490,850);
	
	win.Window().draw(getSprite("JoueurR"));
	win.Window().draw(getSprite("JoueurB"));
	win.Window().draw(getSprite("JoueurV"));
	win.Window().draw(getSprite("JoueurG"));
	win.Window().draw(getSprite("JoueurN"));

	sf::Text V("P1\nV", Font, 100);
	sf::Text V2("", Font, 100);


	V.setFillColor(sf::Color::Black);
	if (Player1.getShip() == "JoueurR")
		V.setPosition(670, 570);
	else if (Player1.getShip() == "JoueurB")
		V.setPosition(870, 570);
	else if (Player1.getShip() == "JoueurV")
		V.setPosition(1070, 570);
	else if (Player1.getShip() == "JoueurG")
		V.setPosition(1270, 570);
	else if (Player1.getShip() == "JoueurN")
		V.setPosition(1470, 570);

	if (!SoloGame)
	{
		V2.setString("P2\nV");
		V2.setFillColor(sf::Color::Black);
		if (Player2.getShip() == "JoueurR")
			V2.setPosition(670, 570);
		else if (Player2.getShip() == "JoueurB")
			V2.setPosition(870, 570);
		else if (Player2.getShip() == "JoueurV")
			V2.setPosition(1070, 570);
		else if (Player2.getShip() == "JoueurG")
			V2.setPosition(1270, 570);
		else if (Player2.getShip() == "JoueurN")
			V2.setPosition(1470, 570);

		sf::Text TReady("Ready", Font, 100);
		TReady.setFillColor(sf::Color::Black);

		if (Readys[0])
		{
			TReady.setPosition(V.getPosition().x, V.getPosition().y - 75);
			win.Window().draw(TReady);
		}
		if (Readys[1])
		{
			TReady.setPosition(V2.getPosition().x, V2.getPosition().y - 75);
			win.Window().draw(TReady);
		}
	}

	win.Window().draw(V);
	win.Window().draw(V2);

}
void DisplayScoreBoardMenu()
{
	sf::Text TLine("", Font, 80);
	static float PosX = 960;

	TLine.setFillColor(sf::Color::Color(180, 50, 0));

	if (ScoreBoardSeen == 1)
	{
		if (PosX < 960)
			PosX += 700 * MainTime.GetTimeDeltaF();
		else
			PosX = 960;
	}
	if (ScoreBoardSeen == 2)
	{
		if (PosX > -600)
			PosX -= 700 * MainTime.GetTimeDeltaF();
		else
			PosX = -600;
	}

	win.Window().draw(getSprite("Fond_menu2"));
			
	// Solo Board
	TLine.setString("Solo Scores");
	TLine.setOrigin(TLine.getLocalBounds().left + TLine.getLocalBounds().width / 2, TLine.getLocalBounds().top + TLine.getLocalBounds().height / 2);
	TLine.setPosition(PosX + 20.f, 150.f);
	win.Window().draw(TLine);
	for (int i = 0; i < 5; i++)
	{
		TLine.setString(SoloLines[i]);
		TLine.setOrigin(TLine.getLocalBounds().left + TLine.getLocalBounds().width / 2, TLine.getLocalBounds().top + TLine.getLocalBounds().height / 2);
		TLine.setPosition(PosX, 250.f + (125.f * (i + 1.f)));
		win.Window().draw(TLine);

		std::string SpriteToGet;
		SpriteToGet = "Joueur";
		SpriteToGet += ShipsColorsSolo[i];
		getSprite(SpriteToGet).setPosition(TLine.getPosition().x + TLine.getGlobalBounds().width / 2 + 50, TLine.getPosition().y - 35);
		win.Window().draw(getSprite(SpriteToGet));
	}
	// Duo Board 
	TLine.setString("Duo Scores");
	TLine.setOrigin(TLine.getLocalBounds().left + TLine.getLocalBounds().width / 2, TLine.getLocalBounds().top + TLine.getLocalBounds().height / 2);
	TLine.setPosition(PosX + 1515.f + 20.f, 150.f);
	win.Window().draw(TLine);
	for (int i = 0; i < 5; i++)
	{
		TLine.setString(DuoLines[i]);
		TLine.setOrigin(TLine.getLocalBounds().left + TLine.getLocalBounds().width / 2, TLine.getLocalBounds().top + TLine.getLocalBounds().height / 2);
		TLine.setPosition(PosX + 1515.f, 250.f + (125.f * (i + 1))); // 915
		win.Window().draw(TLine);


		for (int y = 0; y < 2; y++)
		{
			std::string SpriteToGet;
			SpriteToGet = "Joueur";
			SpriteToGet += ShipsColorsDuo[i][y];
			if (y == 0)
				getSprite(SpriteToGet).setPosition(TLine.getPosition().x - TLine.getGlobalBounds().width / 2 + 130, TLine.getPosition().y - 35);
			else
				getSprite(SpriteToGet).setPosition(TLine.getPosition().x + TLine.getGlobalBounds().width / 2 + 50, TLine.getPosition().y - 35);

			win.Window().draw(getSprite(SpriteToGet));
		}
	}


	win.Window().draw(getSprite("Bande_L"));
	getSprite("Bande_R").setPosition(1680, 0);
	win.Window().draw(getSprite("Bande_R"));

}
void DisplayOptionMenu()
{
	win.Window().draw(getSprite("Fond_menu2"));

	if (OptionChangeKeys)
	{
		sf::RectangleShape ActionKey(sf::Vector2f(400, 60));
		sf::RectangleShape KeyBoard(sf::Vector2f(200, 60));
		sf::RectangleShape KeyPad(sf::Vector2f(150, 60));
		sf::Text ActionName("", Font, 50);

		
		ActionKey.setFillColor(sf::Color::Transparent); ActionKey.setOutlineThickness(1); ActionKey.setOutlineColor(sf::Color::Black);
		KeyBoard.setFillColor(sf::Color::Transparent); KeyBoard.setOutlineThickness(1); KeyBoard.setOutlineColor(sf::Color::Black);
		KeyPad.setFillColor(sf::Color::Transparent); KeyPad.setOutlineThickness(1); KeyPad.setOutlineColor(sf::Color::Black);

		

		int i = 0;
		for (Controle& ActualControle : controles)
		{
			if (changeKeyChoice == i)
			{
				if (changingkey)
					ActionName.setFillColor(sf::Color::Red);
				else
					ActionName.setFillColor(sf::Color::Cyan);
			}
			else
				ActionName.setFillColor(sf::Color::Black);

			ActionKey.setPosition(575, 175.f + 61.f * i);
			KeyBoard.setPosition(ActionKey.getPosition().x + ActionKey.getSize().x + 1 , 175.f + 61.f * i);
			KeyPad.setPosition(KeyBoard.getPosition().x + KeyBoard.getSize().x + 1, 175.f + 61.f * i);

			win.Window().draw(ActionKey);
			win.Window().draw(KeyBoard);
			win.Window().draw(KeyPad);

			switch (ActualControle.name)
			{
			case Action::Up:
				ActionName.setString("Go Up");
				break;
			case Action::Down:
				ActionName.setString("Go Down");
				break;
			case Action::Left:
				ActionName.setString("Go Left");
				break;
			case Action::Right:
				ActionName.setString("Go Right");
				break;
			case Action::Interact:
				ActionName.setString("Interact");
				break;
			case Action::Return:
				ActionName.setString("Return");
				break;
			case Action::Start:
				ActionName.setString("Start");
				break;
			case Action::Fire:
				ActionName.setString("Fire");
				break;
			case Action::Fire_Spe1:
				ActionName.setString("Fire Spe 1");
				break;
			case Action::Fire_Spe2:
				ActionName.setString("Fire Spe 2");
				break;
			default:
				ActionName.setString("None (Bug)");
				break;
			}

			ActionName.setPosition(ActionKey.getPosition().x + 20, ActionKey.getPosition().y);
			win.Window().draw(ActionName);
			
			switch (ActualControle.KeyBoard)
			{
				ITEM(A);
				ITEM(B);
				ITEM(C);
				ITEM(D);
				ITEM(E);
				ITEM(F);
				ITEM(G);
				ITEM(H);
				ITEM(I);
				ITEM(J);
				ITEM(K);
				ITEM(L);
				ITEM(M);
				ITEM(N);
				ITEM(O);
				ITEM(P);
				ITEM(Q);
				ITEM(R);
				ITEM(S);
				ITEM(T);
				ITEM(U);
				ITEM(V);
				ITEM(W);
				ITEM(X);
				ITEM(Y);
				ITEM(Z);
				ITEM(Num0);
				ITEM(Num1);
				ITEM(Num2);
				ITEM(Num3);
				ITEM(Num4);
				ITEM(Num5);
				ITEM(Num6);
				ITEM(Num7);
				ITEM(Num8);
				ITEM(Num9);
				ITEM(Escape);
				ITEM(LControl);
				ITEM(LShift);
				ITEM(LAlt);
				ITEM(LSystem);
				ITEM(RControl);
				ITEM(RShift);
				ITEM(RAlt);
				ITEM(RSystem);
				ITEM(Menu);
				ITEM(LBracket);
				ITEM(RBracket);
				ITEM(Semicolon);
				ITEM(Comma);
				ITEM(Period);
				ITEM(Quote);
				ITEM(Slash);
				ITEM(Backslash);
				ITEM(Tilde);
				ITEM(Equal);
				ITEM(Hyphen);
				ITEM(Space);
				ITEM(Enter);
				ITEM(Backspace);
				ITEM(Tab);
				ITEM(PageUp);
				ITEM(PageDown);
				ITEM(End);
				ITEM(Home);
				ITEM(Insert);
				ITEM(Delete);
				ITEM(Add);
				ITEM(Subtract);
				ITEM(Multiply);
				ITEM(Divide);
				ITEM(Left);
				ITEM(Right);
				ITEM(Up);
				ITEM(Down);
				ITEM(Numpad0);
				ITEM(Numpad1);
				ITEM(Numpad2);
				ITEM(Numpad3);
				ITEM(Numpad4);
				ITEM(Numpad5);
				ITEM(Numpad6);
				ITEM(Numpad7);
				ITEM(Numpad8);
				ITEM(Numpad9);
				ITEM(F1);
				ITEM(F2);
				ITEM(F3);
				ITEM(F4);
				ITEM(F5);
				ITEM(F6);
				ITEM(F7);
				ITEM(F8);
				ITEM(F9);
				ITEM(F10);
				ITEM(F11);
				ITEM(F12);
				ITEM(F13);
				ITEM(F14);
				ITEM(F15);
				ITEM(Pause);

			default:
				ret = "NONE";
				break;
			}
			
			ActionName.setString(ret);
			ActionName.setPosition(KeyBoard.getPosition().x + 20, KeyBoard.getPosition().y);
			win.Window().draw(ActionName);

			switch (ActualControle.PadKey)
			{
				ITEM2(A);
				ITEM2(B);
				ITEM2(X);
				ITEM2(Y);

				ITEM2(L1);
				ITEM2(R1);
				ITEM2(Select);
				ITEM2(Start);
				ITEM2(BSTICKL);
				ITEM2(BSTICKR);
				ITEM2(PS);
				ITEM2(BTOUCHPAD);
				ITEM2(L2);
				ITEM2(R2);

				ITEM2(StickLX);
				ITEM2(StickLY);
				ITEM2(CROSSX);
				ITEM2(CROSSY);
				ITEM2(StickRX);
				ITEM2(StickRY);
				ITEM2(TriggerR2);
				ITEM2(TriggerL2);


			default:
				ret = "NONE";
				break;
			}
			
			if (ActualControle.PadKey < gamepadPS4::StickLX)
				getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, 0, 40, 40));
			else if (ActualControle.AxisDirection == -1)
				getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, 0, 40, 40));
			else if(ActualControle.AxisDirection == 1)
				getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, 1 * 40, 40, 40));

			getSprite("Icons").setPosition(KeyPad.getPosition().x + 50, KeyBoard.getPosition().y + 10);
			win.Window().draw(getSprite("Icons"));

			i++;
		}
	}
	else
	{
		sf::RectangleShape Boxs(sf::Vector2f(1000,60));
		sf::Text ButtonText("", Font, 50);
		
		Boxs.setFillColor(sf::Color::Transparent); Boxs.setOutlineThickness(1); Boxs.setOutlineColor(sf::Color::Black);
		ButtonText.setFillColor(sf::Color::Black);

		Boxs.setPosition(490,300);
		win.Window().draw(Boxs);

		if (changeKeyChoice == 0)
			ButtonText.setFillColor(sf::Color::Red);

		ButtonText.setString("Change KeyBinding");
		ButtonText.setPosition(Boxs.getPosition().x + 395, Boxs.getPosition().y);
		win.Window().draw(ButtonText);

		for (int i = 1; i < 6; i++)
		{
			Boxs.setSize(sf::Vector2f(300, 60));
			Boxs.setPosition(490, Boxs.getPosition().y + Boxs.getSize().y + 1);
			win.Window().draw(Boxs);

			ButtonText.setPosition(Boxs.getPosition().x + 10, Boxs.getPosition().y);
			if (changeKeyChoice == i)
				ButtonText.setFillColor(sf::Color::Red);
			else
				ButtonText.setFillColor(sf::Color::Black);

			if (i == 1)
				ButtonText.setString("Music");
			if (i == 2)
				ButtonText.setString("Sound");
			if (i == 3)
				ButtonText.setString("FullScreen");
			if (i == 4)
				ButtonText.setString("Vsync");
			if (i == 5)
				ButtonText.setString("FPS");


			ButtonText.setPosition(Boxs.getPosition().x + 10, Boxs.getPosition().y);
			win.Window().draw(ButtonText);


			Boxs.setSize(sf::Vector2f(699, 60));
			Boxs.setPosition(791, Boxs.getPosition().y);
			win.Window().draw(Boxs);
		}

		sf::RectangleShape BackgroundBars(sf::Vector2f(500, 30));
		BackgroundBars.setFillColor(sf::Color::Color(0, 0, 0, 25)); BackgroundBars.setOutlineThickness(1); BackgroundBars.setOutlineColor(sf::Color::Black);
		
		BackgroundBars.setPosition(891, 315 + (61 * 1));
		win.Window().draw(BackgroundBars);

		BackgroundBars.setPosition(891, 315 + (61 * 2));
		win.Window().draw(BackgroundBars);

		BackgroundBars.setPosition(891, 315 + (61 * 5));
		win.Window().draw(BackgroundBars);

		sf::RectangleShape Bars(sf::Vector2f(0, 30));
		sf::Text Values("", Font, 35);
		Bars.setFillColor(sf::Color::Color(sf::Color::Red));
		Values.setFillColor(sf::Color::Black);

		
		Bars.setSize(sf::Vector2f(500 * (MusicMultip / 100.f), 30));
		Bars.setPosition(891, 315 + (61 * 1));
		win.Window().draw(Bars);
		Values.setString(std::to_string(MusicMultip));
		Values.setPosition(Bars.getPosition().x, Bars.getPosition().y - 10);
		win.Window().draw(Values);

		Bars.setSize(sf::Vector2f(500 * (SoundMultip / 100.f), 30));
		Bars.setPosition(891, 315 + (61 * 2));
		win.Window().draw(Bars);
		Values.setString(std::to_string(SoundMultip));
		Values.setPosition(Bars.getPosition().x, Bars.getPosition().y - 10);
		win.Window().draw(Values);

		Bars.setSize(sf::Vector2f(500 * (win.getFrameRate() / 240.f), 30));
		Bars.setPosition(891, 315 + (61 * 5));
		win.Window().draw(Bars);
		Values.setString(std::to_string(win.getFrameRate()));
		Values.setPosition(Bars.getPosition().x , Bars.getPosition().y - 10);
		win.Window().draw(Values);

		// fullscreen
		if (win.getStyle() == sf::Style::Default)
			Values.setString("<\tWindowed\t>");
		if (win.getStyle() == sf::Style::None)
			Values.setString("<\tWindowed FullScreen\t>");
		if (win.getStyle() == sf::Style::Fullscreen)
			Values.setString("<\tFullScreen\t>");
		Values.setPosition(Bars.getPosition().x , 315 + 61 * 3 - 10);
		win.Window().draw(Values);


		// VSync
		if (win.getVerticalSync())
			Values.setString("<\tOn\t>");
		if (!win.getVerticalSync())
			Values.setString("<\tOff\t>");

		Values.setPosition(Bars.getPosition().x, 315 + 61 * 4 - 10);
		win.Window().draw(Values);

	}
	

}
void DisplayCredits()
{
	win.Window().draw(getSprite("Credits"));
}
void DisplayHowToPlay()
{			
	win.Window().draw(getSprite("Comment_jouer"));


	sf::IntRect XpRect(0, 0, 210, 88);
	XpRect.width = 52 + (int)((210 - 52) * ((float)Tutos[2].getAtkPoints() / 10 ));


	getSprite("XP").setTextureRect(XpRect);
	getSprite("XP").setPosition(1075, 910);
	win.Window().draw(getSprite("XP"));
	getSprite("XpBar").setPosition(1075, 910);
	win.Window().draw(getSprite("XpBar"));

	for (Buffs& ActualBuff : BuffsList)
	{
		getSprite("Power_Up").setOrigin(getSprite("Power_Up").getGlobalBounds().width / 2, getSprite("Power_Up").getGlobalBounds().height / 2);
		getSprite("Power_Up").setPosition(ActualBuff.getpos());
		win.Window().draw(getSprite("Power_Up"));
	}

	for (PlayerBullet& ActualShoot : Bullets)
		ActualShoot.Draw();

	for (Ennemies& ActualEnnemie : ennemies)
	{
		getSprite("E1").setRotation(0);
		getSprite("E1").setOrigin(getSprite("E1").getGlobalBounds().width / 2, getSprite("E1").getGlobalBounds().height / 2);
		getSprite("E1").setRotation(ActualEnnemie.getRotation());
		getSprite("E1").setPosition(ActualEnnemie.getPos());
		win.Window().draw(getSprite("E1"));
	}
		
	for (int i = 0; i < 4; i++)
	{
		Tutos[i].Draw();
	}

	for (Controle& ActualControle : controles)
	{
		int DirLine = 0;
		if (ActualControle.AxisDirection == -1)
			DirLine = 0;
		if (ActualControle.AxisDirection == 1)
			DirLine = 1;

		getSprite("Icons").setScale(1.5f, 1.5f);

		if (ActualControle.name == Action::Fire_Spe1)
		{
			getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, DirLine * 40, 40, 40));
			getSprite("Icons").setPosition(470, 75);
			win.Window().draw(getSprite("Icons"));
		}
		if (ActualControle.name == Action::Fire_Spe2)
		{
			getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, DirLine * 40, 40, 40));
			getSprite("Icons").setPosition(820, 75);
			win.Window().draw(getSprite("Icons"));
		}
		if (ActualControle.name == Action::Fire)
		{
			getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, DirLine * 40, 40, 40));
			getSprite("Icons").setPosition(1170, 75);
			win.Window().draw(getSprite("Icons"));
		}
		if (Tutos[3].getIntRect().left == 63 * 3)
		{
			if (ActualControle.name == Action::Left)
			{
				getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, DirLine * 40, 40, 40));
				getSprite("Icons").setPosition(1430, 75);
				win.Window().draw(getSprite("Icons"));
			}
		}
		else
		{
			if (ActualControle.name == Action::Right)
			{
				getSprite("Icons").setTextureRect(sf::IntRect((int)ActualControle.PadKey * 40, DirLine * 40, 40, 40));
				getSprite("Icons").setPosition(1430, 75);
				win.Window().draw(getSprite("Icons"));
			}
		}
	}
	getSprite("Icons").setScale(1, 1);
}



std::string To_String(Action _Action)
{
	switch (_Action)
	{
	case Action::Up:
		return "Up";
		break;
	case Action::Down:
		return "Down";
		break;
	case Action::Left:
		return "Left";
		break;
	case Action::Right:
		return "Right";
		break;
	case Action::Interact:
		return "Interact";
		break;
	case Action::Return:
		return "Return";
		break;
	case Action::Start:
		return "Start";
		break;
	case Action::Fire:
		return "Fire";
		break;
	case Action::Fire_Spe1:
		return "Fire_Spe1";
		break;
	case Action::Fire_Spe2:
		return "Fire_Spe2";
		break;

	default:
		return "";
		break;
	}
}