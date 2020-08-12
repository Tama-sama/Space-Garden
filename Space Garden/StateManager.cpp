#include "StateManager.hpp"
#include "Window.hpp"

State state = State::MAIN_MENU;


void UpdateManager()
{
	// Events
	EventsManager();

	//restart of the clock (time per frame)
	MainTime.RestartClock();


	switch (state)
	{
	case State::MAIN_MENU :
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
	case State::MAIN_MENU:
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