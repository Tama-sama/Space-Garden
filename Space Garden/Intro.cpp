#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "Tir.hpp"
#include "Explosion.hpp"
#include "Game.hpp"

#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"

void Intro()
{
	getSprite("JoueurR").setTextureRect(sf::IntRect(0, 0, 62, 101));
	getSprite("JoueurR").setOrigin(getSprite("JoueurR").getGlobalBounds().width / 2, getSprite("JoueurR").getGlobalBounds().height / 2);
	getSprite("JoueurB").setTextureRect(sf::IntRect(0, 0, 62, 101));
	getSprite("JoueurB").setOrigin(getSprite("JoueurB").getGlobalBounds().width / 2, getSprite("JoueurB").getGlobalBounds().height / 2);


	static sf::Vector2f Name_pos = { 240,-70 };
	static sf::Vector2f ship_pos = { 960, 1200 };
	static sf::Text buttons_text[6];

	static bool one_pass = false;
	bool changestate = false;
	if (!one_pass)
	{
		for (int i = 0; i < 6; i++)
		{
			buttons_text[i].setFont(Font);
			buttons_text[i].setCharacterSize(70);
			buttons_text[i].setFillColor(sf::Color::Black);
		}

		buttons_text[0].setString("Jouer");
		buttons_text[1].setString("ScoreBoards");
		buttons_text[2].setString("Options");
		buttons_text[3].setString("How To Play");
		buttons_text[4].setString("Credits");
		buttons_text[5].setString("Quitter");

		buttons_text[1].setCharacterSize(50);
		buttons_text[3].setCharacterSize(50);

		one_pass = true;
	}

	win.Window().draw(getSprite("Fond_menu2"));

	if (ship_pos.y > 950)
		ship_pos.y += -150 * MainTime.GetTimeDeltaF();
	else
	{
		static bool one_pass2;
		if (!one_pass2)
		{
			Bullets.push_back(PlayerBullet(sf::Vector2f(ship_pos.x, ship_pos.y ), 0, 0, 5));
			getSound("shoot").play();
			
			one_pass2 = true;
		}


		if (Name_pos.x < 9000)
		{
			if (Bullets.size() != 0)
			{
				for (PlayerBullet& BulletList : Bullets)
				{
					BulletList.Pos().y += -150 * MainTime.GetTimeDeltaF();
					BulletList.Draw();

					if (BulletList.Pos().y < 630)
					{
						Bullets.remove(BulletList);
						break;
					}
				}
			}
			else
			{
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 5 + 430, Name_pos.y + 500), 100));
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 110 + 430, Name_pos.y + 500), 100));
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 220 + 430, Name_pos.y + 500), 100));
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 330 + 430, Name_pos.y + 500), 100));
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 440 + 430, Name_pos.y + 500), 100));
				Explosions.push_back(Explosion(sf::Vector2f(Name_pos.x + 545 + 430, Name_pos.y + 500), 100));
				
				getSound("explosions").play();

				Name_pos.x = 9999;
			}
		}
	}

	getSprite("Spaces_garden").setPosition(Name_pos);
	win.Window().draw(getSprite("Spaces_garden"));

	for (Explosion& ExplosionList : Explosions)
	{
		ExplosionList.update();
		ExplosionList.draw();		
	}
	RemoveDeadExplosions();

	if (Name_pos.x > 9000 && ship_pos.y > -150)
		ship_pos.y += -250 * MainTime.GetTimeDeltaF();
	else if (Name_pos.x > 9000 && ship_pos.y <= -150)
		changestate = true;
	
	getSprite("JoueurR").setPosition(ship_pos);
	win.Window().draw(getSprite("JoueurR"));

	buttons_text[0].setPosition(sf::Vector2f(850, 50 + (ship_pos.y + 150)));
	buttons_text[1].setPosition(sf::Vector2f(975, 235 + (ship_pos.y + 150)));
	buttons_text[2].setPosition(sf::Vector2f(840, 395 + (ship_pos.y + 150)));
	buttons_text[3].setPosition(sf::Vector2f(960, 580 + (ship_pos.y + 150)));
	buttons_text[4].setPosition(sf::Vector2f(820, 735 + (ship_pos.y + 150)));
	buttons_text[5].setPosition(sf::Vector2f(990, 900 + (ship_pos.y + 150)));


	for (int i = 0; i < 6; i++)
	{		
		getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 170 * i + (ship_pos.y + 150 + getSprite("Button").getGlobalBounds().height)));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250 , 170 * i + (ship_pos.y + 150 )));
		}

		buttons_text[i].setFillColor(sf::Color::Black);
		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text[i]);
	}

	if (changestate)
		ChangeState(State::MAIN_MENU);
}