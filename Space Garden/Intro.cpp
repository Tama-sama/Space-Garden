#include "Tools.hpp"
#include "Window.hpp"
#include "StateManager.hpp"
#include "Tir.hpp"
#include "Explosion.hpp"


#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"

void Intro()
{
	static sf::Vector2f Name_pos = { 240,-70 };
	static sf::Vector2f ship_pos = { 950, 1200 };
	static sf::Text buttons_text[5];

	static bool one_pass = false;
	bool changestate = false;
	if (!one_pass)
	{
		for (int i = 0; i < 5; i++)
		{
			buttons_text[i].setFont(Font);
			buttons_text[i].setCharacterSize(70);
			buttons_text[i].setFillColor(sf::Color::Black);
		}

		buttons_text[0].setString("Jouer");
		buttons_text[1].setString("ScoreBoards");
		buttons_text[2].setString("Options");
		buttons_text[3].setString("Credits");
		buttons_text[4].setString("Quitter");

		buttons_text[1].setCharacterSize(50);

		one_pass = true;
	}

	for (Sound& ActualSound : SoundList)
		ActualSound.update();

	win.Window().draw(getSprite("Fond_menu2"));

	getSprite("Spaces_garden").setPosition(Name_pos);
	win.Window().draw(getSprite("Spaces_garden"));

	if (ship_pos.y > 950)
		ship_pos.y += -150 * MainTime.GetTimeDeltaF();
	else
	{
		static bool one_pass2;
		if (!one_pass2)
		{
			Bullets.push_back(PlayerBullet(sf::Vector2f(ship_pos.x + 22, ship_pos.y ), 0, 0, 5));
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
				
				getSound("explosions").play();

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
		changestate = true;
	

	getSprite("Test").setPosition(ship_pos);
	win.Window().draw(getSprite("Test"));

	buttons_text[0].setPosition(sf::Vector2f(850, 50 + (ship_pos.y + 150)));
	buttons_text[1].setPosition(sf::Vector2f(975, 265 + (ship_pos.y + 150)));
	buttons_text[2].setPosition(sf::Vector2f(850, 450 + (ship_pos.y + 150)));
	buttons_text[3].setPosition(sf::Vector2f(1000, 650 + (ship_pos.y + 150)));
	buttons_text[4].setPosition(sf::Vector2f(845, 850 + (ship_pos.y + 150)));


	for (int i = 0; i < 5; i++)
	{		
		getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 200 * i + (ship_pos.y + 150 + getSprite("Button").getGlobalBounds().height)));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250 , 200 * i + (ship_pos.y + 150 )));
		}

		buttons_text[i].setFillColor(sf::Color::Black);
		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text[i]);
	}

	if (changestate)
		ChangeState(State::MAIN_MENU);
}