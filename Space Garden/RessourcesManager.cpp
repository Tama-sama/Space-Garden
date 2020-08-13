#include "Tools.hpp"
#include "RessourcesManager.hpp"
#include <filesystem>

std::list<Ressources> RessourcesList;


void RessourcesLoad(std::string path)
{
	namespace fs = std::filesystem;

	for (const fs::directory_entry& entry : fs::directory_iterator(path))
	{
		std::string tmpExtension;
		// take Name of the element (ex : ../Ressources/Background.png)
		std::string tmp = entry.path().string();

		// erase the path (ex : Background.png)
		tmp.erase(0, path.size());

		// erase the extention (ex : Background)
		size_t position = tmp.find(".");
		if (position != -1)
		{
			tmpExtension = tmp.substr(position);
			tmp.erase(position);
		}


		Ressources tmpRessource;
		tmpRessource.type = RessourceType::UNKNOWN;
		tmpRessource.name = tmp;
		tmpRessource.path = path + tmp + tmpExtension;
		std::string InfoPath = "";

		if (tmpExtension == ".wav")
		{
			tmpRessource.type = RessourceType::SOUNDFX;
			InfoPath = "../Ressources/Infos/Sound.load";
			//std::cout << tmpRessource.name << std::endl;
		}
		else if (tmpExtension == ".ogg")
		{
			tmpRessource.type = RessourceType::MUSIC;
		}


		if (InfoPath.size() != 0)
		{
			std::ifstream File(InfoPath);
			std::string Line;
			if (File.is_open())
			{
				while (std::getline(File, Line))
				{
					std::string FileName = "";
					FileName = Line.substr(0, Line.find(" "));
					//std::cout << FileName << std::endl;

					if (FileName == tmp)
					{
						std::cout << FileName;
						Line.erase(0, FileName.size() + 3);
						bool done = false;
						while (!done)
						{
							std::string ActiveStage = Line.substr(0, Line.find(" "));
							Line.erase(0, ActiveStage.size());
							std::cout << " | " << ActiveStage;

							if (ActiveStage == "Intro")
							{
								tmpRessource.state = State::INTRO;
								RessourcesList.push_back(tmpRessource);
							}

							if (Line.find("|") == -1)
								done = true;
							else
								Line.erase(0, 3);

						};
						std::cout << std::endl;
						break;

					}
				}

				File.close();
			}
			else
				std::cout << "Error Open File : " << InfoPath << std::endl;
		}

		// std::cout << tmp << "  extension : " << tmpExtension << std::endl;
	}
}