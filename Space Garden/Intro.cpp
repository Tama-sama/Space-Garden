#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "Tir.hpp"
#include "Explosion.hpp"


#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
void Intro()
{


	static sf::Texture TexBackground;
	static sf::Sprite Background;
	
	static sf::Texture TexName;
	static sf::Sprite Name;
	static sf::Vector2f Name_pos = { 240,-70 };

	static sf::Texture TexShip;
	static sf::Sprite ship;
	static sf::Vector2f ship_pos = { 950, 1200 };

	static sf::Sprite _buttons[5];
	static sf::IntRect _buttons_rect[5];
	static sf::Text buttons_text[5];
	static sf::Texture TexButtons1;
	static sf::Texture TexButtons2;

	static sf::Font Font;

	static bool one_pass = false;
	if (!one_pass)
	{
		RessourcesLoad("../Ressources/");
		LoadSounds(State::INTRO);

		Font.loadFromFile("../Ressources/Otto.ttf");

		TexBackground.loadFromFile("../Ressources/Fond_menu2.png");
		Background.setTexture(TexBackground);

		TexName.loadFromFile("../Ressources/Spaces_garden.png");
		Name.setTexture(TexName);

		TexShip.loadFromFile("../Ressources/Test.png");
		ship.setTexture(TexShip);

		TexButtons1.loadFromFile("../Ressources/Quitter - Copie.png");
		TexButtons2.loadFromFile("../Ressources/Quitter.png");



		for (int i = 0; i < 5; i++)
		{
			buttons_text[i].setFont(Font);
			buttons_text[i].setCharacterSize(50);
			buttons_text[i].setFillColor(sf::Color::Black);
		}

		buttons_text[0].setString("Jouer");
		buttons_text[1].setString("ScoreBoard Solo");
		buttons_text[2].setString("ScoreBoard Duo");
		buttons_text[3].setString("Credits");
		buttons_text[4].setString("Quitter");

		buttons_text[0].setCharacterSize(70);
		buttons_text[3].setCharacterSize(70);
		buttons_text[4].setCharacterSize(70);

		for (int i = 0; i < 5; i += 2)
		{
			_buttons[i].setTexture(TexButtons1);
			_buttons_rect[i] = sf::IntRect(0, 0, 477, 217);
			if (i + 1 < 5)
			{
				_buttons[i + 1].setTexture(TexButtons2);
				_buttons_rect[i + 1] = sf::IntRect(0, 0, 477, 217);
			}
		}

		one_pass = true;
	}

	for (Sound& ActualSound : SoundList)
	{
		ActualSound.update();
	}


	win.Window().draw(Background);

	Name.setPosition(Name_pos);
	win.Window().draw(Name);

	if (ship_pos.y > 950)
		ship_pos.y += -150 * MainTime.GetTimeDeltaF();
	else
	{
		static bool one_pass2;
		if (!one_pass2)
		{
			Bullets.push_back(PlayerBullet(sf::Vector2f(ship_pos.x + 22, ship_pos.y ), 0, 0, 5));

			//
			//
			//sfSound_play(shoot_sound.sound);
			getSound("shoot").play();
			//
			//
			
			one_pass2 = true;
		}


		if (Name_pos.x < 9000)
		{
			if (Bullets.size() != 0)
			{
				for (PlayerBullet& BulletList : Bullets)
				{
					BulletList.Pos().y += -150 * MainTime.GetTimeDeltaF();
					BulletList.Sprite().setPosition(BulletList.Pos());
					win.Window().draw(BulletList.Sprite());

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
				
				//
				//
				
				//sfSound_play(explosion_sound.sound);
				getSound("explosions").play();
				//
				//

				Name_pos.x = 9999;
			}
		}
	}

	for (Explosion& ExplosionList : Explosions)
	{
		if (ExplosionList.getAnimator().getXFrame() < ExplosionList.getAnimator().getMaxXFrame() - 1)
			ExplosionList.getAnimator().Animate(ExplosionList.getSprite());

		ExplosionList.getSprite().setPosition(ExplosionList.getPos());
		win.Window().draw(ExplosionList.getSprite());
		
		if (ExplosionList.getAnimator().getXFrame() >= ExplosionList.getAnimator().getMaxXFrame() - 1)
		{
			ExplosionList.addTimer(MainTime.GetTimeDeltaF());
			if (ExplosionList.getTimer() >= 0.075f)
			{
				Explosions.remove(ExplosionList);
				break;
			}
		}

	}


	if (Name_pos.x > 9000 && ship_pos.y > -150)
		ship_pos.y += -250 * MainTime.GetTimeDeltaF();
	else if (Name_pos.x > 9000 && ship_pos.y <= -150)
	{
		state = State::MAIN_MENU;
	}

	ship.setPosition(ship_pos);
	win.Window().draw(ship);


	for (int i = 0; i < 5; i += 2)
	{
		_buttons[i].setPosition(sf::Vector2f(600, 200 * i + (ship_pos.y + 150)));
			
		if (i + 1 < 5)
		{
			_buttons[i + 1].setPosition(sf::Vector2f(600 + 250, 200 * (i + 1) + (ship_pos.y + 150)));
		}
	}

	buttons_text[0].setPosition(sf::Vector2f(850, 50 + (ship_pos.y + 150)));
	buttons_text[1].setPosition(sf::Vector2f(950, 265 + (ship_pos.y + 150)));
	buttons_text[2].setPosition(sf::Vector2f(800, 470 + (ship_pos.y + 150)));
	buttons_text[3].setPosition(sf::Vector2f(1000, 650 + (ship_pos.y + 150)));
	buttons_text[4].setPosition(sf::Vector2f(845, 850 + (ship_pos.y + 150)));

	for (int i = 0; i < 5; i++)
	{

		_buttons_rect[i].left = 0;
		
		buttons_text[i].setFillColor(sf::Color::Black);
		_buttons[i].setTextureRect(_buttons_rect[i]);
		win.Window().draw(_buttons[i]);
		win.Window().draw(buttons_text[i]);
	}
}