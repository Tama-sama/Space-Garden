#include "Save.hpp"

#include "Player.hpp"
#include "Texture_SpriteManager.hpp"
#include "StringManager.hpp"
#include "Window.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Controles.hpp"

std::string NameP1;
std::string NameP2;
char isModif = '_';
char isModif2 = '_';
bool NameDone[2] = { false,false };
extern bool SoloGame;

sf::Thread LoadMenu_2(&LoadNextState, State::MAIN_MENU);

void FileSave()
{
	if (SoloGame)
	{
		// Change scores if actual score is better
		for (int i = 0; i < 5; i++)
		{
			if (Player1.getScore() > SoloScores[i])
			{
				for (int y = 4; y > i; y--)
				{
					ShipsColorsSolo[y] = ShipsColorsSolo[y - 1];
					SoloNames[y] = SoloNames[y - 1];
					SoloScores[y] = SoloScores[y - 1];
				}

				ShipsColorsSolo[i] = Player1.getShip().c_str()[Player1.getShip().size() - 1];
				SoloNames[i] = NameP1;
				SoloScores[i] = Player1.getScore();
				break;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			SoloLines[i] = ShipsColorsSolo[i];
			SoloLines[i] += " " + SoloNames[i] + " " + std::to_string(SoloScores[i]);
		}

		// Write new scores
		std::ofstream FileWrite("../Ressources/Score Solo.txt");
		if (FileWrite.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				// rewrite fives bests scores
				FileWrite << SoloLines[i] << "\n";
			}
			FileWrite.close();
		}

		for (int i = 0; i < 5; i++)
		{
			SoloLines[i] = "#" + std::to_string(i + 1) + " - " + SoloNames[i] + " - " + std::to_string(SoloScores[i]) + "\n";
		}
	}
	else
	{
		// Change scores if actual score is better
		for (int i = 0; i < 5; i++)
		{
			if (Player1.getScore() + Player2.getScore() > DuoScoresTotal[i])
			{
				for (int y = 4; y > i; y--)
				{
					ShipsColorsDuo[y][0] = ShipsColorsDuo[y - 1][0];
					DuoNames[y][0] = DuoNames[y - 1][0];
					DuoScores[y][0] = DuoScores[y - 1][0];
					DuoScoresTotal[y] = DuoScoresTotal[y - 1];
					DuoScores[y][1] = DuoScores[y - 1][1];
					DuoNames[y][1] = DuoNames[y - 1][1];
					ShipsColorsDuo[y][1] = ShipsColorsDuo[y - 1][1];
				}

				ShipsColorsDuo[i][0] = Player1.getShip().c_str()[Player1.getShip().size() - 1];
				DuoNames[i][0] = NameP1;
				DuoScores[i][0] = Player1.getScore();
				DuoScoresTotal[i] = Player1.getScore() + Player2.getScore();
				DuoScores[i][1] = Player2.getScore();
				DuoNames[i][1] = NameP2;
				ShipsColorsDuo[i][1] = Player2.getShip().c_str()[Player2.getShip().size() - 1];
				break;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			DuoLines[i] = ShipsColorsDuo[i][0] + std::string(" ") + DuoNames[i][0] + " " + std::to_string(DuoScores[i][0]) + " " + std::to_string(DuoScoresTotal[i]) + " " + std::to_string(DuoScores[i][1]) + " " + DuoNames[i][1] + " " + ShipsColorsDuo[i][1];
		}

		std::ofstream FileWrite("../Ressources/Score Duo.txt");
		if (FileWrite.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				// rewrite fives bests scores
				FileWrite << DuoLines[i] << "\n";
			}
			FileWrite.close();
		}

		for (int i = 0; i < 5; i++)
		{
			DuoLines[i] = "#" + std::to_string(i + 1) + "       " + DuoNames[i][0] + " - " + std::to_string(DuoScores[i][0]) + " - " + std::to_string(DuoScoresTotal[i]) + " - " + std::to_string(DuoScores[i][1]) + " - " + DuoNames[i][1] + "\n";
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
		// if it's a gamepad and not a keyboard 
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
				if (NameP1.size() < 10 && isModif != '_')
				{
					NameP1 += isModif;
					isModif = '_';
				}
			}

			if (isButtonPressed(Action::Return, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (NameP1.size() > 0)
				{
					NameP1.pop_back();
					isModif = '_';
				}
			}

			if (isButtonPressed(Action::Start, Player1.getController()) && ActionTiming > 0.2)
			{
				ActionTiming = 0.f;
				if (NameP1.size() > 0)
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
				if (NameP1.size() > 0)
				{
					NameDone[0] = true;
				}
			}
		}
	}

	if (SoloGame)
	{
		NameDone[1] = true;
		NameP2 = "";
		isModif2 = '_';
	}
	else
	{
		if (!NameDone[1])
		{
			// if it's a gamepad and not a keyboard 
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
					if (NameP2.size() < 10 && isModif2 != '_')
					{
						NameP2 += isModif2;
						isModif = '_';
					}
				}

				if (isButtonPressed(Action::Return, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (NameP2.size() > 0)
					{
						NameP2.pop_back();
						isModif2 = '_';
					}
				}

				if (isButtonPressed(Action::Start, Player2.getController()) && ActionTimingP2 > 0.2)
				{
					ActionTimingP2 = 0.f;
					if (NameP2.size() > 0)
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
					if (NameP2.size() > 0)
					{
						NameDone[1] = true;
					}
				}
			}
		}
	}

	// if all players set ready -> load and leave
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
		NameP1 = "";
		NameP2 = "";
		isModif = '_';
		isModif2 = '_';

		RemoveStateSprites(State::SAVE);
		state = State::MAIN_MENU;
	}
}

void DisplaySave()
{
	sf::Text TxtPlayerOne(NameP1 + isModif, Font, 65);
	sf::Text TxtPlayerTwo(NameP2 + isModif2, Font, 65);

	TxtPlayerOne.setFillColor(sf::Color::Black);
	TxtPlayerTwo.setFillColor(sf::Color::Black);

	TxtPlayerOne.setPosition(20, 325);
	TxtPlayerTwo.setPosition(1720, 325);

	if (NameDone[0])
	{
		TxtPlayerOne.setString(NameP1);
		TxtPlayerOne.setFillColor(sf::Color::Blue);
		TxtPlayerOne.setStyle(sf::Text::Style::Bold);
	}
	if (NameDone[1])
	{
		TxtPlayerTwo.setString(NameP2);
		TxtPlayerTwo.setFillColor(sf::Color::Blue);
		TxtPlayerTwo.setStyle(sf::Text::Style::Bold);
	}


	win.Window().draw(getSprite("Fond_menu2"));

	win.Window().draw(TxtPlayerOne);
	win.Window().draw(TxtPlayerTwo);





	// some text
	sf::Text AditionalText("", Font, 75);
	AditionalText.setFillColor(sf::Color::Black);
	AditionalText.setString(getString("Names"));
	AditionalText.setOrigin(AditionalText.getLocalBounds().left + AditionalText.getLocalBounds().width / 2, AditionalText.getLocalBounds().top + AditionalText.getLocalBounds().height / 2);
	AditionalText.setPosition(960.f, 200.f);

	win.Window().draw(AditionalText);



	// ScoresBoards
	std::string ScoreLines[5];
	int actual_pos = 5;

	if (SoloGame)
	{
		for (int i = 0; i < 5; i++)
		{
			ScoreLines[i] = SoloLines[i];
		}

		for (int i = 0; i < 5; i++)
		{	
			if (Player1.getScore() > SoloScores[i])
			{
				for (int y = 4; y > i; y--)
				{
					ScoreLines[y] = ScoreLines[y - 1];
				}
				
				ScoreLines[i] = "#" + std::to_string(i + 1) + " - " + SoloNames[i] + " - " + std::to_string(SoloScores[i]) + "\n";
				actual_pos = i;
				break;
			}		
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			ScoreLines[i] = DuoLines[i];
		}

		for (int i = 0; i < 5; i++)
		{
			if (Player1.getScore() + Player2.getScore() > DuoScoresTotal[i])
			{
				for (int y = 4; y > i; y--)
				{
					ScoreLines[y] = ScoreLines[y - 1];
				}

				ScoreLines[i] = "#" + std::to_string(i + 1) + "       " + DuoNames[i][0] + " - " + std::to_string(DuoScores[i][0]) + " - " + std::to_string(DuoScoresTotal[i]) + " - " + std::to_string(DuoScores[i][1]) + " - " + DuoNames[i][1] + "\n";
				actual_pos = i;
				break;
			}
		}
	}

	int forloop = 6;
	if (actual_pos != 5)
		forloop = 5;

	for (int i = 0; i < forloop; i++)
	{
		if (i != actual_pos)
		{
			AditionalText.setString(ScoreLines[i]);
		}
		else
		{
			if (SoloGame)
				AditionalText.setString(std::string("#" + std::to_string(i + 1) + " - " + NameP1 + " - " + std::to_string(Player1.getScore()) + "\n"));
			else
				AditionalText.setString(std::string("#" + std::to_string(i + 1) + "       " + NameP1 + " - " + std::to_string(Player1.getScore()) + " - " + std::to_string(Player1.getScore() + Player2.getScore()) + " - " + std::to_string(Player2.getScore()) + " - " + NameP2 + "\n"));
		}

		AditionalText.setOrigin(AditionalText.getLocalBounds().left + AditionalText.getLocalBounds().width / 2, AditionalText.getLocalBounds().top + AditionalText.getLocalBounds().height / 2);
		AditionalText.setPosition(960.f, 350.f + (110.f * i));
		win.Window().draw(AditionalText);



		if (i == actual_pos)
		{
			sf::Text Arrows("->", Font, 75);
			Arrows.setFillColor(sf::Color::Black);

			Arrows.setOrigin(Arrows.getLocalBounds().left + Arrows.getLocalBounds().width / 2, Arrows.getLocalBounds().top + Arrows.getLocalBounds().height / 2);
			Arrows.setPosition(AditionalText.getPosition().x - AditionalText.getOrigin().x - 60, AditionalText.getPosition().y - AditionalText.getOrigin().y / 2);
			win.Window().draw(Arrows);

			Arrows.setString("<-");
			Arrows.setOrigin(Arrows.getLocalBounds().left + Arrows.getLocalBounds().width / 2, Arrows.getLocalBounds().top + Arrows.getLocalBounds().height / 2);
			Arrows.setPosition(AditionalText.getPosition().x + AditionalText.getOrigin().x + 120, AditionalText.getPosition().y - AditionalText.getOrigin().y / 2);
			win.Window().draw(Arrows);
		}




		if (SoloGame)
		{
			std::string SpriteToGet;
			SpriteToGet = "Joueur";
			if (i == actual_pos)
				SpriteToGet = Player1.getShip();
			else
				SpriteToGet += ShipsColorsSolo[i];


			getSprite(SpriteToGet).setPosition(AditionalText.getPosition().x + AditionalText.getGlobalBounds().width / 2 + 50, AditionalText.getPosition().y - 35);
			win.Window().draw(getSprite(SpriteToGet));
		}
		else
		{
			for (int y = 0; y < 2; y++)
			{
				std::string SpriteToGet;
				SpriteToGet = "Joueur";
				if (i == 5 && y == 0)
					SpriteToGet = Player1.getShip();
				else if (i == 5 && y == 1)
					SpriteToGet = Player2.getShip();
				else
					SpriteToGet += ShipsColorsDuo[i][y];

				if (y == 0)
					getSprite(SpriteToGet).setPosition(AditionalText.getPosition().x - AditionalText.getGlobalBounds().width / 2 + 130, AditionalText.getPosition().y - 35);
				else
					getSprite(SpriteToGet).setPosition(AditionalText.getPosition().x + AditionalText.getGlobalBounds().width / 2 + 50, AditionalText.getPosition().y - 35);

				win.Window().draw(getSprite(SpriteToGet));
			}
		}
	} 



	// some text again
	AditionalText.setCharacterSize(38);
	if (Player1.getController() != 8)
		AditionalText.setString(getString("GamePad") + "\n" + getString("Pad_Up_Down") + "\n" + getString("Pad_Interact") + "\n" + getString("Pad_Start"));
	else
		AditionalText.setString(getString("KeyBoard") + "\n" + getString("Key_write") + "\n" + getString("Key_Interact"));

	AditionalText.setOrigin(0, AditionalText.getLocalBounds().top + AditionalText.getLocalBounds().height / 2);
	AditionalText.setPosition(5.f, 200.f);
	win.Window().draw(AditionalText);

	if (!SoloGame)
	{
		if (Player2.getController() != 8)
			AditionalText.setString(getString("GamePad") + "\n" + getString("Pad_Up_Down") + "\n" + getString("Pad_Interact") +"\n" + getString("Pad_Start"));
		else
			AditionalText.setString(getString("KeyBoard") + "\n" + getString("Key_write") + "\n" + getString("Key_Interact"));

		AditionalText.setOrigin(0, AditionalText.getLocalBounds().top + AditionalText.getLocalBounds().height / 2);
		AditionalText.setPosition(1685.f, 200.f);
		win.Window().draw(AditionalText);
	}
}