#include "StateManager.hpp"
#include "Window.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"

#include "Menu.hpp"

State state = State::INTRO;


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
		FirstInit = true;
	}

	switch (state)
	{
	case State::MAIN_MENU:
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


	switch (state)
	{
	case State::MAIN_MENU :
		UpdateMenu();
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

	default:
		break;
	}

	// Display on window
	win.Window().display();
}



void EventsManager()
{
	while (win.Window().pollEvent(win.Events()))
	{
		if (win.Events().type == sf::Event::Closed)
			win.Window().close();
	}
}