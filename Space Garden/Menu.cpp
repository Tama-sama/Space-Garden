#include "Menu.hpp"

#include "Window.hpp"
#include "StateManager.hpp"

#include "Tir.hpp"
#include "Explosion.hpp"
#include "Ennemies.hpp"
#include "Player.hpp"
#include "Buffs.hpp"

#include "RessourcesManager.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"


int MenuChoice = 0;
Player Tutos[4]{ Player(sf::Vector2f(500,800), 1 ,0),Player(sf::Vector2f(850,800),1, 0),Player(sf::Vector2f(1200,800),1, 0),Player(sf::Vector2f(1400,800),1, 0) };

enum class Menus
{
	MAIN,
	PLAY,
	SCOREBOARDS,
	OPTIONS,
	CREDITS,

	HOW_PLAY,
};
Menus ActualMenu;

void UpdateMenu()
{
	switch (ActualMenu)
	{

	case Menus::MAIN:
		UpdateMainMenu();
		break;
	case Menus::PLAY:
		UpdatePlayMenu();
		break;
	case Menus::SCOREBOARDS:
		break;
	case Menus::OPTIONS:
		break;
	case Menus::CREDITS:
		UpdateCredits();
		break;
	case Menus::HOW_PLAY:
		UpdateHowToPlay();
		break;

	default:
		break;
	}
}

void UpdateMainMenu()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	for (Sound& ActualSound : SoundList)
		ActualSound.update();
	// musics
	/*if (sfMusic_getStatus(Menu_music.music) == sfStopped)
	{
		sfMusic_stop(Boss_music.music);
		sfMusic_stop(Game_music.music);
		sfMusic_play(Menu_music.music);
		sfMusic_setLoop(Menu_music.music, sfTrue);
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice > 0)
		{
			MenuChoice--;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice < 4)
		{
			MenuChoice++;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		switch (MenuChoice)
		{
		case 0:
			getSound("menu_click").play();
			ActualMenu = Menus::PLAY;
			break;
		case 1:
			getSound("menu_click").play();
			//ActualMenu = Menus::SCOREBOARDS;
			break;
		case 2:
			getSound("menu_click").play();
			//ActualMenu = Menus::OPTIONS;
			break;
		case 3:
			getSound("menu_click").play();
			ActualMenu = Menus::CREDITS;
			break;
		case 4:
			getSound("menu_click").play();
			win.Window().close();
			break;

		default:
			break;
		}
	}
}
void UpdatePlayMenu()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	for (Sound& ActualSound : SoundList)
		ActualSound.update();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice > 0)
		{
			MenuChoice--;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		if (MenuChoice < 2)
		{
			MenuChoice++;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		switch (MenuChoice)
		{
		case 0:
			getSound("menu_click").play();
			break;
		case 1:
			getSound("menu_click").play();
			break;
		case 2:
			getSound("menu_click").play();
			ActualMenu = Menus::HOW_PLAY;
			break;

		default:
			break;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		MenuChoice = 0;
		ActualMenu = Menus::MAIN;
	}
}
void UpdateCredits()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && ActionTiming >= 0.3)
	{
		ActionTiming = 0;
		getSound("menu_click").play();
		ActualMenu = Menus::MAIN;
	}
}
void UpdateHowToPlay()
{
	for (PlayerBullet& ActualShoot : Bullets)
	{
		ActualShoot.Update();

		for (Ennemies& ActualEnnemie : ennemies)
		{
			if (Circle_Rect_Collision(ActualShoot.Pos(), sf::Vector2f(ActualEnnemie.getSprite().getGlobalBounds().left, ActualEnnemie.getSprite().getGlobalBounds().top), 3, sf::Vector2f(ActualEnnemie.getSprite().getGlobalBounds().width, ActualEnnemie.getSprite().getGlobalBounds().height)))
			{
				if (ActualShoot.getLife() > 0 && ActualEnnemie.getLife() > 0)
				{
					ActualEnnemie.TakeDamage(ActualShoot.getDamages());
					ActualShoot.TakeDamage();
					break;
				}
			}
		}

		if (ActualShoot.getType() == 3 && ActualShoot.getLife() > 0 && ActualShoot.getTimer() > 4.f)
		{
			ActualShoot.TakeDamage();
		}
	}

	for (Buffs& ActualBuff : BuffsList)
	{
		ActualBuff.Update();

		getSprite("Power_Up").setPosition(ActualBuff.getpos());
		getSprite("Joueur1").setTextureRect(Tutos[2].getIntRect());
		getSprite("Joueur1").setPosition(Tutos[2].getPosition());

		if (getSprite("Power_Up").getGlobalBounds().intersects(getSprite("Joueur1").getGlobalBounds()))
		{
			if (ActualBuff.Exist())
			{
				if (Tutos[2].getAtkPoints() < 10)
					Tutos[2].addAtkPoint();

				ActualBuff.Kill();
			}
		}
	}


	for (Buffs& ActualBuff : BuffsList)
	{
		if (!ActualBuff.Exist())
		{
			BuffsList.remove(ActualBuff);
			break;
		}
	}

	Tutos[0].TimersUpdate(MainTime.GetTimeDeltaF());
	Tutos[1].TimersUpdate(MainTime.GetTimeDeltaF());
	Tutos[2].TimersUpdate(MainTime.GetTimeDeltaF());

	static float testtimer = 5.1;
	testtimer += MainTime.GetTimeDeltaF();
	if (testtimer >= 5)
	{
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[1].getPosition().x + 70, Tutos[1].getPosition().y - 420), 2, 10));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[1].getPosition().x + 15, Tutos[1].getPosition().y - 575), 2, 10));

		Tutos[1].SetFireSin();
		testtimer = 0;
	}
	Tutos[1].FireSin();

	static float FirePissenlitTimer = 4.1;
	FirePissenlitTimer += MainTime.GetTimeDeltaF();
	if (FirePissenlitTimer >= 4)
	{
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x + 110, Tutos[0].getPosition().y - 440), 5));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x, Tutos[0].getPosition().y - 420), 5));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x, Tutos[0].getPosition().y - 525), 5));
		ennemies.push_back(Ennemies(sf::Vector2f(Tutos[0].getPosition().x - 110, Tutos[0].getPosition().y - 440), 5));

		Tutos[0].FirePissenlit();
		FirePissenlitTimer = 0;
	}
	 
	static float FireTimer = 0;
	static bool Fireshoot[2] = { false,false };
	FireTimer += MainTime.GetTimeDeltaF();
	if (FireTimer >= 0.4)
	{
		if (!Fireshoot[0])
		{
			if (!Tutos[2].isAtkSpeActive())
				ennemies.push_back(Ennemies(sf::Vector2f(Tutos[2].getPosition().x, Tutos[2].getPosition().y - 440), 1));
			
			Tutos[2].Fire();
			Fireshoot[0] = true;
			FireTimer = 0;
		}
		else if (!Fireshoot[1])
		{
			Tutos[2].Fire();
			FireTimer = -2;
			Fireshoot[0] = false;
		}
	}


	for (Ennemies& ActualEnnemie : ennemies)
	{
		if (ActualEnnemie.getLife() <= 0)
		{
			if (ActualEnnemie.getPos().x == Tutos[2].getPosition().x)
			{
				BuffsList.push_back(Buffs(1, ActualEnnemie.getPos()));
			}

			ennemies.remove(ActualEnnemie);
			break;
		}
	}

	bool shootRemove = true;
	while (shootRemove)
	{
		shootRemove = false;
		for (PlayerBullet& ActualShoot : Bullets)
		{
			if (ActualShoot.getLife() <= 0)
			{
				if (ActualShoot.getType() == 2)
				{
					for (int i = 0; i < 16; i++)
					{
						float Dir_Tir = (i * (pi / 8));

						Bullets.push_back(PlayerBullet(sf::Vector2f(ActualShoot.Pos().x, ActualShoot.Pos().y), 3, ActualShoot.getOwner(), 1, Dir_Tir));
					}
				}

				shootRemove = true;
				Bullets.remove(ActualShoot);

				break;
			}
		}
	}



	static int direction = 0;
	if (Tutos[3].getPosition().x == 1550)
		direction = 1;
	else if (Tutos[3].getPosition().x == 1400)
		direction = 0;

	if (direction == 0)
	{
		if (Tutos[3].getPosition().x < 1550)
		{
			Tutos[3].addPositionX(150 * MainTime.GetTimeDeltaF());
			Tutos[3].setLRectFrame(2);
		}
		else
			Tutos[3].setPosition(1550, Tutos[3].getPosition().y);
	}
	else
	{
		if (Tutos[3].getPosition().x > 1400)
		{
			Tutos[3].addPositionX(-150 * MainTime.GetTimeDeltaF());
			Tutos[3].setLRectFrame(3);
		}
		else
			Tutos[3].setPosition(1400, Tutos[3].getPosition().y);
	}
}





void DisplayMenu()
{
	switch (ActualMenu)
	{

	case Menus::MAIN:
		DisplayMainMenu();
		break;
	case Menus::PLAY:
		DisplayPlayMenu();
		break;
	case Menus::SCOREBOARDS:
		break;
	case Menus::OPTIONS:
		break;
	case Menus::CREDITS:
		DisplayCredits();
		break;
	case Menus::HOW_PLAY:
		DisplayHowToPlay();
		break;

	default:
		break;
	}
}

void DisplayMainMenu()
{
	sf::Text buttons_text("", Font, 70);
	std::string Textyes[5]{ "Jouer","ScoreBoards","Options","Credits","Quitter" };
	sf::Vector2f TextPos[5]{ sf::Vector2f(850,50),sf::Vector2f(975,265), sf::Vector2f(850,450), sf::Vector2f(1000,650), sf::Vector2f(845,850) };

	win.Window().draw(getSprite("Fond_menu2"));

	for (int i = 0; i < 5; i++)
	{
		if (i == MenuChoice)
		{
			getSprite("Button").setTextureRect(sf::IntRect(477, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Color(180, 50, 0));
		}
		else
		{
			getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Black);
		}

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 200 * i + getSprite("Button").getGlobalBounds().height));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250, 200 * i ));
		}

		if (i == 1)
			buttons_text.setCharacterSize(50);
		else
			buttons_text.setCharacterSize(70);

		buttons_text.setString(Textyes[i]);
		buttons_text.setPosition(TextPos[i]);

		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}
}
void DisplayPlayMenu()
{
	sf::Text buttons_text("", Font, 70);
	std::string Textyes[3]{ "Solo","Coop","Comment jouer" };
	sf::Vector2f TextPos[3]{ sf::Vector2f(850,55),sf::Vector2f(1020,245), sf::Vector2f(800,450) };
	sf::Text Return("B Retour", Font, 75);

	win.Window().draw(getSprite("Fond_menu2"));

	for (int i = 0; i < 3; i++)
	{
		if (i == MenuChoice)
		{
			getSprite("Button").setTextureRect(sf::IntRect(477, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Color(180, 50, 0));
		}
		else
		{
			getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));
			buttons_text.setFillColor(sf::Color::Black);
		}

		if (i % 2 == 0)
		{
			getSprite("Button").setRotation(180);
			getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 200 * i + getSprite("Button").getGlobalBounds().height));
		}
		else
		{
			getSprite("Button").setRotation(0);
			getSprite("Button").setPosition(sf::Vector2f(600 + 250, 200 * i));
		}

		buttons_text.setString(Textyes[i]);
		buttons_text.setPosition(TextPos[i]);

		win.Window().draw(getSprite("Button"));
		win.Window().draw(buttons_text);
	}

	
	Return.setFillColor(sf::Color::Color(180, 50, 0));
	Return.setPosition(1300, 800);
	win.Window().draw(Return);
}
void DisplayCredits()
{
	sf::Text Return("B Retour", Font, 75);
	Return.setFillColor(sf::Color::Color(180, 50, 0));
	Return.setPosition(1500,940);

	win.Window().draw(getSprite("Credits"));
	win.Window().draw(Return);

}
void DisplayHowToPlay()
{			
	win.Window().draw(getSprite("Comment_jouer"));


	sf::IntRect XpRect(0, 0, 210, 88);
	XpRect.width = 52 + (210 - 52) * ((float)Tutos[2].getAtkPoints() / 10 );


	getSprite("XP").setTextureRect(XpRect);
	getSprite("XP").setPosition(1075, 910);
	win.Window().draw(getSprite("XP"));
	getSprite("XpBar").setPosition(1075, 910);
	win.Window().draw(getSprite("XpBar"));

	for (Buffs& ActualBuff : BuffsList)
	{
		getSprite("Power_Up").setOrigin(getSprite("Power_Up").getGlobalBounds().width / 2, getSprite("Power_Up").getGlobalBounds().height / 2);
		getSprite("Power_Up").setPosition(ActualBuff.getpos());
		win.Window().draw(getSprite("Power_Up"));
	}

	for (PlayerBullet& ActualShoot : Bullets)
		win.Window().draw(ActualShoot.Sprite());

	for (Ennemies& ActualEnnemie : ennemies)
		win.Window().draw(ActualEnnemie.getSprite());
		
	for (int i = 0; i < 4; i++)
	{
		getSprite("Joueur1").setTextureRect(Tutos[i].getIntRect());
		getSprite("Joueur1").setOrigin(getSprite("Joueur1").getGlobalBounds().width / 2, getSprite("Joueur1").getGlobalBounds().height / 2);
		getSprite("Joueur1").setPosition(Tutos[i].getPosition());
		win.Window().draw(getSprite("Joueur1"));
	}

	static float LB_RBTimer = 0;
	sf::IntRect LB_RBRect(0, 0, 280, 113);
	sf::IntRect RTRect(0, 0, 145, 113);
	sf::IntRect JoystickRect(0, 0, 113, 113);
	LB_RBTimer += MainTime.GetTimeDeltaF();
	if (LB_RBTimer < 1.5f)
	{
		LB_RBRect.left = 0;
		RTRect.left = 0;
	}
	else if (LB_RBTimer > 1.5f && LB_RBTimer < 3)
	{
		LB_RBRect.left = LB_RBRect.width;
		RTRect.left = RTRect.width;
	}
	else
		LB_RBTimer = 0;
	
	if (Tutos[3].getIntRect().left == Tutos[3].getIntRect().width * 3)
		JoystickRect.left = JoystickRect.width * 1;
	else
		JoystickRect.left = JoystickRect.width * 2;

	getSprite("LB").setTextureRect(LB_RBRect);
	getSprite("LB").setPosition(375, 20);
	win.Window().draw(getSprite("LB"));

	getSprite("RB").setTextureRect(LB_RBRect);
	getSprite("RB").setPosition(700,20);
	win.Window().draw(getSprite("RB"));

	getSprite("RT").setTextureRect(RTRect);
	getSprite("RT").setPosition(1140, 20);
	win.Window().draw(getSprite("RT"));

	getSprite("Joystick").setTextureRect(JoystickRect);
	getSprite("Joystick").setPosition(1420, 20);
	win.Window().draw(getSprite("Joystick"));
}