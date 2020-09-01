#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
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
std::string To_String(Action _Action);
void OptionLoad()
{
	std::ifstream SettingFile("../Ressources/Infos/Settings.bin", std::ifstream::binary);
	if (SettingFile.is_open())
	{

		for (Controle& ActualControle : controles)
		{
			int name = 0;
			int KeyBoard = 0;
			int PadKey = 0;
			int Dir = 0;

			SettingFile.read((char*) &name, sizeof(int));
			SettingFile.read((char*) &KeyBoard, sizeof(int));
			SettingFile.read((char*) &PadKey, sizeof(int));
			SettingFile.read((char*) &Dir, sizeof(int));

			ActualControle.KeyBoard = (sf::Keyboard::Key)KeyBoard;
			ActualControle.PadKey = (gamepadPS4)PadKey;
			ActualControle.AxisDirection = Dir;

			ActualControle.isButton = true;
			if (Dir != 0)
				ActualControle.isButton = false;
		}

		int Style = 0;
		bool Vsync = true;
		int Frames = 0;

		SettingFile.read((char*)&MusicMultip, sizeof(int));
		SettingFile.read((char*)&SoundMultip, sizeof(int));
		SettingFile.read((char*)&Style, sizeof(int));
		SettingFile.read((char*)&Vsync, sizeof(bool));
		SettingFile.read((char*)&Frames, sizeof(int));

		win.setStyle(Style);
		win.setVerticalSync(Vsync);
		win.setFrameRate(Frames);


		SettingFile.close();
	}
	win.Window().setMouseCursorVisible(false);
}


Windows win(sf::VideoMode::getDesktopMode(), "Space Garden", 120, sf::Style::None);

int main(int argc, char** argv)
{
	LaunchArguments(argc, argv);

	ControlInit();
	OptionLoad();
	RessourcesLoad("../Ressources/Textures/");
	RessourcesLoad("../Ressources/SFX/");
	RessourcesLoad("../Ressources/Musics/");
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