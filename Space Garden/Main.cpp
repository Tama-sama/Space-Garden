#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "RessourcesManager.hpp"

#include "Controles.hpp"


void ControlInit()
{
	controles.push_back(Controle(Action::Up, sf::Keyboard::Z, false, gamepadPS4::StickLY, -1));
	controles.push_back(Controle(Action::Down, sf::Keyboard::S, false, gamepadPS4::StickLY, 1));
	controles.push_back(Controle(Action::Left, sf::Keyboard::Q, false, gamepadPS4::StickLX, -1));
	controles.push_back(Controle(Action::Right, sf::Keyboard::D, false, gamepadPS4::StickLX, 1));

	controles.push_back(Controle(Action::Interact, sf::Keyboard::Return , true, gamepadPS4::A));
	controles.push_back(Controle(Action::Return, sf::Keyboard::Escape , true, gamepadPS4::B));
	controles.push_back(Controle(Action::Start, sf::Keyboard::Escape , true, gamepadPS4::Start));

	controles.push_back(Controle(Action::Fire, sf::Keyboard::Space , false, gamepadPS4::TriggerR2, 1));
	controles.push_back(Controle(Action::Fire_Spe1, sf::Keyboard::LShift , true, gamepadPS4::L1));
	controles.push_back(Controle(Action::Fire_Spe2, sf::Keyboard::LControl , true, gamepadPS4::R1));
}



Windows win(sf::VideoMode::getDesktopMode(), "Space Garden", 120, sf::Style::None);


int main(int argc, char** argv)
{
	LaunchArguments(argc, argv);

	ControlInit();
	RessourcesLoad("../Ressources/");
	ChangeState(State::ALL);
	ChangeState(State::INTRO);

	while (!win.isDone())
	{
		UpdateManager();
		DisplayManager();
	}
		
	ProgramEnd();

	return 0;
}