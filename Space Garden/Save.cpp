#include "Tools.hpp"
#include "Player.hpp"
#include "Texture_SpriteManager.hpp"
#include "Window.hpp"
#include "Game.hpp"
#include "Controles.hpp"

std::string a;
std::string b;
char isModif = '_';
char isModif2 = '_';
bool NameDone[2] = { false,false };
extern bool SoloGame;

sf::Thread LoadMenu_2(&LoadNextState, State::MAIN_MENU);

void FileSave()
{
	if (SoloGame)
	{
		std::ifstream FileRead("../Ressources/Score Solo.txt");
		std::string Line[5];
		char Colors[5] = { 'R','R','R','R','R' };
		std::string Names[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };
		int Scores[5] = { 0,0,0,0,0 };

		if (FileRead.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				// Color Name Score
				std::getline(FileRead, Line[i]);
				Colors[i] = Line[i].c_str()[0];
				Line[i].erase(0, 2);
				Names[i] = Line[i].substr(0, Line[i].find(" "));
				Line[i].erase(0, Names[i].size() + 1);
				Scores[i] = std::stoi(Line[i]);
			}

			FileRead.close();
		}
		else
			std::cout << "Error Opening File" << std::endl;

		for (int i = 0; i < 5; i++)
		{
			if (Player1.getScore() > Scores[i])
			{
				for (int y = 4; y > i; y--)
				{
					Colors[y] = Colors[y - 1];
					Names[y] = Names[y - 1];
					Scores[y] = Scores[y - 1];
				}

				Colors[i] = Player1.getShip().c_str()[Player1.getShip().size() - 1];
				Names[i] = a;
				Scores[i] = Player1.getScore();
				break;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			Line[i] = Colors[i];
			Line[i] += " " + Names[i] + " " + std::to_string(Scores[i]);
		}


		std::ofstream FileWrite("../Ressources/Score Solo.txt");
		if (FileWrite.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				FileWrite << Line[i] << "\n";
			}
			FileWrite.close();
		}
	}
	else
	{
		std::ifstream FileRead("../Ressources/Score Duo.txt");
		std::string Line[5];

		char ColorsP1[5] = { 'R','R','R','R','R' };
		std::string NamesP1[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };
		int ScoresP1[5] = { 0,0,0,0,0 };
		int ScoresTotal[5] = { 0,0,0,0,0 };
		int ScoresP2[5] = { 0,0,0,0,0 };
		std::string NamesP2[5] = { "NoBody","NoBody","NoBody","NoBody","NoBody" };
		char ColorsP2[5] = { 'R','R','R','R','R' };

		if (FileRead.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				// Color1 Name1 Score1 ScoreTotal Score2 Name2 Color2 
				std::getline(FileRead, Line[i]);

				ColorsP1[i] = Line[i].c_str()[0];		
				Line[i].erase(0, 2);

				NamesP1[i] = Line[i].substr(0, Line[i].find(" "));
				Line[i].erase(0, NamesP1[i].size() + 1);

				ScoresP1[i] = std::stoi(Line[i].substr(0, Line[i].find(" ")));
				Line[i].erase(0, std::to_string(ScoresP1[i]).size() + 1);

				ScoresTotal[i] = std::stoi(Line[i].substr(0, Line[i].find(" ")));
				Line[i].erase(0, std::to_string(ScoresTotal[i]).size() + 1);

				ScoresP2[i] = std::stoi(Line[i].substr(0, Line[i].find(" ")));
				Line[i].erase(0, std::to_string(ScoresP2[i]).size() + 1);

				NamesP2[i] = Line[i].substr(0, Line[i].find(" "));
				Line[i].erase(0, NamesP2[i].size() + 1);

				ColorsP2[i] = Line[i].c_str()[0];

				std::cout << ColorsP1[i] << "|" << NamesP1[i] << "|" << std::to_string(ScoresP1[i]) << "|" << std::to_string(ScoresTotal[i]) << "|" << std::to_string(ScoresP2[i]) << "|" << NamesP2[i] << "|" << ColorsP1[i] << std::endl;
			}

			FileRead.close();
		}
		else
			std::cout << "Error Opening File" << std::endl;

		for (int i = 0; i < 5; i++)
		{
			if (Player1.getScore() + Player2.getScore() > ScoresTotal[i])
			{
				for (int y = 4; y > i; y--)
				{
					ColorsP1[y] = ColorsP1[y - 1];
					NamesP1[y] = NamesP1[y - 1];
					ScoresP1[y] = ScoresP1[y - 1];
					ScoresTotal[y] = ScoresTotal[y - 1];
					ScoresP2[y] = ScoresP2[y - 1];
					NamesP2[y] = NamesP2[y - 1];
					ColorsP2[y] = ColorsP2[y - 1];
				}

				ColorsP1[i] = Player1.getShip().c_str()[Player1.getShip().size() - 1];
				NamesP1[i] = a;
				ScoresP1[i] = Player1.getScore();
				ScoresTotal[i] = Player1.getScore() + Player2.getScore();
				ScoresP2[i] = Player2.getScore();
				NamesP2[i] = b;
				ColorsP2[i] = Player2.getShip().c_str()[Player2.getShip().size() - 1];
				break;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			Line[i] = ColorsP1[i] + std::string(" ") + NamesP1[i] + " " + std::to_string(ScoresP1[i]) + " " + std::to_string(ScoresTotal[i]) + " " + std::to_string(ScoresP2[i]) + " " + NamesP2[i] + " " + ColorsP2[i];
		}

		std::ofstream FileWrite("../Ressources/Score Duo.txt");
		if (FileWrite.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				FileWrite << Line[i] << "\n";
			}
			FileWrite.close();
		}
	}
}


void UpdateSave()
{
	static float ActionTiming = 0.f;
	static float ActionTimingP2 = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	ActionTimingP2 += MainTime.GetTimeDeltaF();

	if (!NameDone[0])
	{
		if (Player1.getController() != 8)
		{
			if (isButtonPressed(Action::Up, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if ((isModif > 'A' && isModif <= 'Z') || (isModif > 'a' && isModif <= 'z'))
					isModif--;

				else if (isModif == 'a' || isModif == '_')
					isModif = 'Z';
			}

			if (isButtonPressed(Action::Down, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if ((isModif >= 'A' && isModif < 'Z') || (isModif >= 'a' && isModif < 'z'))
					isModif++;

				else if (isModif == 'Z' || isModif == '_')
					isModif = 'a';

			}

			if (isButtonPressed(Action::Interact, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (a.size() < 10 && isModif != '_')
				{
					a += isModif;
					isModif = '_';
				}
			}

			if (isButtonPressed(Action::Return, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (a.size() > 0)
				{
					a.pop_back();
					isModif = '_';
				}
			}

			if (isButtonPressed(Action::Start, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (a.size() > 0)
				{
					NameDone[0] = true;
				}
			}
		}
		else
		{
			if (isButtonPressed(Action::Interact, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (a.size() > 0)
				{
					NameDone[0] = true;
				}
			}
		}
	}

	if (SoloGame)
	{
		NameDone[1] = true;
		b = "";
		isModif2 = '_';
	}
	else
	{
		if (!NameDone[1])
		{
			if (Player2.getController() != 8)
			{
				if (isButtonPressed(Action::Up, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if ((isModif2 > 'A' && isModif2 <= 'Z') || (isModif2 > 'a' && isModif2 <= 'z'))
						isModif2--;

					else if (isModif2 == 'a' || isModif2 == '_')
						isModif2 = 'Z';
				}

				if (isButtonPressed(Action::Down, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if ((isModif2 >= 'A' && isModif2 < 'Z') || (isModif2 >= 'a' && isModif2 < 'z'))
						isModif2++;

					else if (isModif2 == 'Z' || isModif2 == '_')
						isModif2 = 'a';

				}

				if (isButtonPressed(Action::Interact, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (b.size() < 10 && isModif2 != '_')
					{
						b += isModif2;
						isModif = '_';
					}
				}

				if (isButtonPressed(Action::Return, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (b.size() > 0)
					{
						b.pop_back();
						isModif2 = '_';
					}
				}

				if (isButtonPressed(Action::Start, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (b.size() > 0)
					{
						NameDone[1] = true;
					}
				}
			}
			else
			{
				if (isButtonPressed(Action::Interact, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (b.size() > 0)
					{
						NameDone[1] = true;
					}
				}
			}
		}
	}

	if (NameDone[0] && NameDone[1] && ActionTimingP2 > 0.2)
	{
		LoadMenu_2.launch();
	}
}
 
void UpdateSaveToMenu()
{
	if (can_Switch && !Loading)
	{
		can_Switch = false;

		NameDone[0] = false;
		NameDone[1] = false;
		FileSave();
		a = "";
		b = "";
		isModif = '_';
		isModif2 = '_';

		RemoveStateSprites(State::SAVE);
		state = State::MAIN_MENU;
	}
}

void DisplaySave()
{
	sf::Text TxtPlayerOne(a + isModif, Font, 65);
	sf::Text TxtPlayerTwo(b + isModif2, Font, 65);

	TxtPlayerOne.setFillColor(sf::Color::Black);
	TxtPlayerTwo.setFillColor(sf::Color::Black);

	TxtPlayerOne.setPosition(20, 325);
	TxtPlayerTwo.setPosition(1720, 325);

	if (NameDone[0])
	{
		TxtPlayerOne.setString(a);
		TxtPlayerOne.setFillColor(sf::Color::Blue);
		TxtPlayerOne.setStyle(sf::Text::Style::Bold);
	}
	if (NameDone[1])
	{
		TxtPlayerTwo.setString(b);
		TxtPlayerTwo.setFillColor(sf::Color::Blue);
		TxtPlayerTwo.setStyle(sf::Text::Style::Bold);
	}



	win.Window().draw(getSprite("Fond_menu2"));

	win.Window().draw(TxtPlayerOne);
	win.Window().draw(TxtPlayerTwo);
}