#include "StringManager.hpp"
#include "RessourcesManager.hpp"

std::list<Strings*> StringsList;
//std::string Lang("fr_fr");
std::string Lang("En_us");

void LoadStrings(State _state)
{
	std::string NeedState;
	switch (_state)
	{
	case State::ALL:
		NeedState = "All";
		break;
	case State::INTRO:
		NeedState = "Intro";
		break;
	case State::MAIN_MENU:
		NeedState = "Menu";
		break;
	case State::GAME:
		NeedState = "Game";
		break;
	case State::SAVE:
		NeedState = "Save";
		break;

	default:
		break;
	}


	for (Ressources& ActualRessource : RessourcesList)
	{
		if (ActualRessource.type == RessourceType::LANG && ActualRessource.name == Lang)
		{
			std::string path("../Ressources/Langs/" + Lang + ".lang");

			std::ifstream Langfile(path);
			std::string Line;
			if (Langfile.is_open())
			{
				while (std::getline(Langfile, Line))
				{
					std::string StringName = "";
					StringName = Line.substr(0, Line.find(" "));
					Line.erase(0, StringName.size() + 3);

					std::string StringStr = "";
					StringStr = Line.substr(0, Line.find("|") - 1);
					Line.erase(0, StringStr.size() + 3);



					bool done = false;
					while (!done)
					{
						std::string ActiveStage = Line.substr(0, Line.find(" "));
						Line.erase(0, ActiveStage.size());

						if (ActiveStage == NeedState)
						{
							Strings* tmpString = new Strings;
							tmpString->Construct(StringName, StringStr, _state);

							StringsList.push_back(tmpString);
							break;
						}

						if (Line.find("|") == -1)
							done = true;
						else
							Line.erase(0, 3);

					}
				}
				Langfile.close();
			}
		}
	}
}



std::string getString(std::string Name)
{
	for (Strings* ActualString : StringsList)
	{
		if (ActualString->getName() == Name)
		{
			return ActualString->getString();
		}
	}


	// if it not find in the selected language search in english language
	std::string NeedState;
	switch (state)
	{
	case State::ALL:
		NeedState = "All";
		break;
	case State::INTRO:
		NeedState = "Intro";
		break;
	case State::MAIN_MENU:
		NeedState = "Menu";
		break;
	case State::GAME:
		NeedState = "Game";
		break;
	case State::SAVE:
		NeedState = "Save";
		break;

	default:
		break;
	}

	std::string path("../Ressources/Langs/en_us.lang");
	std::ifstream Langfile(path);
	std::string Line;
	if (Langfile.is_open())
	{
		while (std::getline(Langfile, Line))
		{
			std::string StringName = "";
			StringName = Line.substr(0, Line.find(" "));
			Line.erase(0, StringName.size() + 3);

			if (StringName == Name)
			{
				std::string StringStr = "";
				StringStr = Line.substr(0, Line.find("|") - 1);
				Line.erase(0, StringStr.size() + 3);


				bool done = false;
				while (!done)
				{
					std::string ActiveStage = Line.substr(0, Line.find(" "));
					Line.erase(0, ActiveStage.size());

					if (ActiveStage == NeedState)
					{
						Strings* tmpString = new Strings;
						tmpString->Construct(StringName, StringStr, state);

						StringsList.push_back(tmpString);

						return tmpString->getString();
						break;
					}

					if (Line.find("|") == -1)
						done = true;
					else
						Line.erase(0, 3);

				}
			}
		}
	}
}


void RemoveStateStrings(State _state)
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Strings* ActualString : StringsList)
		{
			if (ActualString->getState() == _state && _state != State::ALL)
			{
				delete ActualString;
				StringsList.remove(ActualString);
				Removed = true;
				break;
			}
		}
	}
}


void RemoveAllStrings()
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Strings* ActualString : StringsList)
		{
			if (ActualString->getState() != State::ALL)
			{
				delete ActualString;
				StringsList.remove(ActualString);
				Removed = true;
				break;
			}
		}
	}
}