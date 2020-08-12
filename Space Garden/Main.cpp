#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"

Windows win(sf::VideoMode::getDesktopMode(), "SFML");

int main(int argc, char** argv)
{
	LaunchArguments(argc, argv);

	while (!win.isDone())
	{
		UpdateManager();
		DisplayManager();
	}
		
	ProgramEnd();

	return 0;
}