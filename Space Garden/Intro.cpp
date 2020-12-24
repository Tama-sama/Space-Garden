#include "Intro.hpp"

#include "Window.hpp"
#include "StateManager.hpp"
#include "Tir.hpp"
#include "Explosion.hpp"
#include "Game.hpp"
#include "Controles.hpp"

#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"
#include "StringManager.hpp"

int speedmult = 1;
sf::Vector2f Name_pos = { 240,-70 };
sf::Vector2f ship_pos = { 960, 1300 };
sf::IntRect ship_rect(0, 0, 62, 101);
sf::Text buttons_text;

void UpdateIntro()
{
	bool changestate = false;

	// Speed Multiplier
	if (isButtonPressed(Action::Interact) || isButtonPressed(Action::Start))
		speedmult = 3;
	
	if (ship_pos.y > 950)
	{
		ship_pos.y += -150 * MainTime.GetTimeDeltaF() * speedmult;
		ship_rect.left = ship_rect.width;
	}
	else
	{
		ship_rect.left = 0;
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
					BulletList.Pos().y += -150 * MainTime.GetTimeDeltaF() * speedmult;

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
		ExplosionList.update();
	}
	RemoveDeadExplosions();

	if (Name_pos.x > 9000 && ship_pos.y > -150)
	{
		ship_pos.y += -250 * MainTime.GetTimeDeltaF() * speedmult;
		ship_rect.left = ship_rect.width;
	}
	else if (Name_pos.x > 9000 && ship_pos.y <= -150)
		changestate = true;
	
	if (changestate)
	{
		RemoveStateSounds(State::INTRO);
		RemoveStateStrings(State::INTRO);
		RemoveStateSprites(State::INTRO);
		state = State::MAIN_MENU;
	}
}



void DisplayIntro()
{
	win.Window().draw(getSprite("Fond_menu2"));

	for (PlayerBullet& BulletList : Bullets)
		BulletList.Draw();
	
	getSprite("Spaces_garden").setPosition(Name_pos);
	win.Window().draw(getSprite("Spaces_garden"));

	for (Explosion& ExplosionList : Explosions)
		ExplosionList.draw();	

	getSprite("JoueurR").setTextureRect(ship_rect);
	getSprite("JoueurR").setPosition(ship_pos);
	win.Window().draw(getSprite("JoueurR"));


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
			getSprite("Button").setPosition(sf::Vector2f(600 + 250, 170 * i + (ship_pos.y + 150)));
		}

		switch (i)
		{
		case 0:
			buttons_text.setString(getString("Play"));
			buttons_text.setPosition(sf::Vector2f(890, 110 + (ship_pos.y + 150)));
			break;
		case 1:
			buttons_text.setString(getString("ScoreBoards"));
			buttons_text.setPosition(sf::Vector2f(1040, 275 + (ship_pos.y + 150)));
			break;
		case 2:
			buttons_text.setString(getString("Settings"));
			buttons_text.setPosition(sf::Vector2f(890, 455 + (ship_pos.y + 150)));
			break;
		case 3:
			buttons_text.setString(getString("HowTP"));
			buttons_text.setPosition(sf::Vector2f(1040, 625 + (ship_pos.y + 150)));
			break;
		case 4:
			buttons_text.setString(getString("Credit"));
			buttons_text.setPosition(sf::Vector2f(890, 788 + (ship_pos.y + 150)));
			break;
		case 5:
			buttons_text.setString(getString("Quit"));
			buttons_text.setPosition(sf::Vector2f(1040, 956.5f + (ship_pos.y + 150.f)));
			break;
		}
		
		buttons_text.setFont(Font);
		buttons_text.setCharacterSize(70);
		buttons_text.setOrigin(buttons_text.getLocalBounds().left + buttons_text.getLocalBounds().width / 2, buttons_text.getLocalBounds().top + buttons_text.getLocalBounds().height / 2);
		while (buttons_text.getOrigin().x >= 85)
		{
			buttons_text.setCharacterSize(buttons_text.getCharacterSize() - 1);
			buttons_text.setOrigin(buttons_text.getLocalBounds().left + buttons_text.getLocalBounds().width / 2, buttons_text.getLocalBounds().top + buttons_text.getLocalBounds().height / 2);
		}		

		buttons_text.setFillColor(sf::Color::Black);
		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}
}