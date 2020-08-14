#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "RessourcesManager.hpp"

Windows win(sf::VideoMode::getDesktopMode(), "SFML");

int main(int argc, char** argv)
{
	LaunchArguments(argc, argv);

	RessourcesLoad("../Ressources/");
	ChangeState(State::INTRO);

	while (!win.isDone())
	{
		UpdateManager();
		DisplayManager();
	}
		
	ProgramEnd();

	return 0;
}