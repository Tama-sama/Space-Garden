#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Game.hpp"
#include "SoundManager.hpp"
#include "Texture_SpriteManager.hpp"
#include "Explosion.hpp"
#include "Window.hpp"

std::list<Ennemies> ennemies;

sf::Image BossCollision;
CAnimations FogAnim(0, sf::Vector2i(1458, 412), 0.15f, 3);

bool Ennemies_one_pass = true;
Ennemies::Ennemies(sf::Vector2f Pos, int MoveType, int Life)
{
	if (Ennemies_one_pass)
	{
		BossCollision.loadFromFile("../Ressources/Boss_collision.png");
		Ennemies_one_pass = false;
	}
	vie = 1;

	if (MoveType == 1 || MoveType == 2 || MoveType == 5)
	{
		vie = 2;
	}
	else if (MoveType != 100)
	{
		vie = 3;
	}
	if (Life != -1)
	{
		vie = Life;
	}


	pos = Pos;
	Delta.x = -200;
	Delta.y = 300;
	Move_Type = MoveType;
	phase = 0;
	timer = 0;
	hit = false;
	timer_hit = 0;
	LastSwitch = pos;
	m_rotation = 180;

	if (MoveType == 100)
	{
		pos = sf::Vector2f(960, -400);
		Delta = sf::Vector2f(0, 133);
		vie = 100;
		m_rotation = 0;
	}

}


void Ennemies::TakeDamage(int Damage)
{
	if (Move_Type == 100)
	{
		if (vie > 50 && vie - Damage <= 50)
		{
			getSound("explosions").play();
			Explosions.push_back(Explosion(sf::Vector2f(560,210), 98));
			Explosions.push_back(Explosion(sf::Vector2f(560,230), 98));
			Explosions.push_back(Explosion(sf::Vector2f(1360,210), 99));
			Explosions.push_back(Explosion(sf::Vector2f(1360,230), 99));
		}
		if (vie > 0 && vie - Damage <= 0)
		{
			getSound("Explosion_Boss").play();
			Explosions.push_back(Explosion(sf::Vector2f(960 + 400, 0), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 425, 50), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 350, 75), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 375, 60), 99));

			Explosions.push_back(Explosion(sf::Vector2f(960 - 400, 0), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 425, 50), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 350, 75), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 375, 60), 98));

			Explosions.push_back(Explosion(sf::Vector2f(960 - 200, 0), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 225, 50), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 150, 75), 98));
			Explosions.push_back(Explosion(sf::Vector2f(960 - 175, 60), 98));

			Explosions.push_back(Explosion(sf::Vector2f(960 + 200, 0), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 225, 50), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 150, 75), 99));
			Explosions.push_back(Explosion(sf::Vector2f(960 + 175, 60), 99));
		}
	}

	vie -= Damage;
	hit = true;
	timer_hit = 0.0f;
}

void Ennemies::Fire()
{
	if (Move_Type == 1 || Move_Type == 2 || Move_Type == 5)
	{
		for (int i = -1; i < 2; i += 2)
		{
			sf::Vector2f temppos = { pos.x + (-32 * i),pos.y + 60 };

			int random = -1;

			if (Player1.getLife() > 0 && Player2.getLife() > 0)
				random = rand() % 2;
			else if (Player1.getLife() > 0)
				random = 0;
			else if (Player2.getLife() > 0)
				random = 1;


			double angleCible = 1.570;

			if (random == 0)
				angleCible = Angle_calc(pos, Player1.getPosition());
			else if (random == 1)
				angleCible = Angle_calc(pos, Player2.getPosition());

			sf::Vector2f tmpDelta(350.f * (float)cos(angleCible), 350.f * (float)sin(angleCible));

			EnnemiesShootsList.push_back(EnnemiesShoots(temppos, tmpDelta, -1, (float)(angleCible * 180.0f / pi) - 90.f));

		}
	}
	else if (Move_Type == 3 || Move_Type == 4)
	{
		sf::Vector2f temppos(pos.x ,pos.y + 40);
		sf::Vector2f tmpDelta(0, 200);
		for (int i = -1; i < 2; i++)
		{
			tmpDelta.x = 100.f * i;

			EnnemiesShootsList.push_back(EnnemiesShoots(temppos, tmpDelta, -2, -35.f * i));
		}
	}
	else if (Move_Type == 100)
	{
		if (vie > 50)
		{
			static float timer_spawn1 = 0;
			timer_spawn1 += MainTime.GetTimeDeltaF();
			if (timer_spawn1 >= 1.25)
			{
				static int number_bul;
				static float timer_spawn_2;
				timer_spawn_2 += MainTime.GetTimeDeltaF();

				if (timer_spawn_2 >= 0.15 && number_bul < 5)
				{
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(960, 165) , sf::Vector2f(500,500), 4));
					timer_spawn_2 = 0;
					number_bul++;
				}
				else if (number_bul >= 5)
				{
					number_bul = 0;
					timer_spawn_2 = 0;
					timer_spawn1 = 0;
				}
			}

			static float timer_spawn = 0;
			timer_spawn += MainTime.GetTimeDeltaF();
			if (timer_spawn >= 3)
			{
				static int number_bul;
				static float timer_spawn_2;
				timer_spawn_2 += MainTime.GetTimeDeltaF();

				if (timer_spawn_2 >= 0.15 && number_bul < 3)
				{
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(1392, 412), sf::Vector2f(0.f, 300.f + (rand() % 50)), 2));
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(580, 412), sf::Vector2f(0.f, 300.f + (rand() % 50)), 3));

					timer_spawn_2 = 0;
					number_bul++;
				}
				else if (number_bul == 3)
				{
					number_bul = 0;
					timer_spawn_2 = 0;
					timer_spawn = 0;
				}
			}
		}
		else
		{
			static float timer_spawn1 = 0;
			timer_spawn1 += MainTime.GetTimeDeltaF();
			if (timer_spawn1 >= 1.25)
			{
				static int number_bul;
				static float timer_spawn_2 = 0;
				timer_spawn_2 += MainTime.GetTimeDeltaF();

				if (timer_spawn_2 >= 0.15 && number_bul < 4)
				{
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(960 - 280, 160), sf::Vector2f(500, 500), 4));
					timer_spawn_2 = 0;
					number_bul++;
				}
				else if (number_bul == 4)
				{
					number_bul = 0;
					timer_spawn_2 = 0;
					timer_spawn1 = 0;
				}
			}

			static float timer_spawn1_ = -0.625;
			timer_spawn1_ += MainTime.GetTimeDeltaF();
			if (timer_spawn1_ >= 1.25)
			{
				static int number_bul2;
				static float timer_spawn_3 = 0;
				timer_spawn_3 += MainTime.GetTimeDeltaF();

				if (timer_spawn_3 >= 0.15 && number_bul2 < 4)
				{
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(960 + 310, 160), sf::Vector2f(500, 500), 4));
					timer_spawn_3 = 0;
					number_bul2++;
				}
				else if (number_bul2 == 4)
				{
					number_bul2 = 0;
					timer_spawn_3 = 0;
					timer_spawn1_ = 0;
				}
			}

			static float timer_spawn3 = 0;
			timer_spawn3 += MainTime.GetTimeDeltaF();
			if (timer_spawn3 >= 1)
			{
				static int number_bul;
				static float timer_spawn_2 = 0;
				timer_spawn_2 += MainTime.GetTimeDeltaF();

				if (timer_spawn_2 >= 0.3 && number_bul < 5)
				{
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(960, 160), sf::Vector2f((float)(rand() % 450 - 250), 250.f), 5));
					timer_spawn_2 = 0;
					number_bul++;
				}
				else if (number_bul == 5)
				{
					number_bul = 0;
					timer_spawn_2 = 0;
					timer_spawn3 = 0;
				}
			}
		}
	}
}

void Ennemies::Update()
{
	addTimer(MainTime.GetTimeDeltaF());



	if (getType() == 1)
	{
		if (getPhase() == 0)
		{
			setRotation(135);
			setDelta(225, 150);
			if (getTimer() > 2)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 2, getLastSwitch().y + getDelta().y * 2);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getRotation() < 180 && getTimer() > 0.2)
				rotate(140 * MainTime.GetTimeDeltaF());

			if (getTimer() > 0.5)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 0.5, getLastSwitch().y + getDelta().y * 0.5);
				setPosition(getLastSwitch());
				setRotation(180);
				setDelta(0, 0);
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getTimer() > 0.2)
			{
				Fire();
				setPhase(3);
				resetTimer();
			}
		}
		else if (getPhase() == 3)
		{
			if (getTimer() > 0.3)
			{
				Fire();
				setPhase(4);
				resetTimer();
			}
		}
		else if (getPhase() == 4)
		{
			if (getTimer() > 1.2)
			{
				Fire();
				setPhase(5);
				resetTimer();
			}
		}
		else if (getPhase() == 5)
		{
			if (getTimer() > 0.8)
			{
				if (getRotation() < 210)
					rotate(140 * MainTime.GetTimeDeltaF());
				else
					setRotation(210);

				setDelta(75, -100);
			}
		}
	}
	else if (getType() == 2)
	{
		if (getPhase() == 0)
		{
			setRotation(225);
			setDelta(-225, 150);
			if (getTimer() > 2)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 2, getLastSwitch().y + getDelta().y * 2);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getRotation() > 180 && getTimer() > 0.2)
				rotate(-140 * MainTime.GetTimeDeltaF());

			if (getTimer() > 0.5)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 0.5, getLastSwitch().y + getDelta().y * 0.5);
				setPosition(getLastSwitch());
				setRotation(180);
				setDelta(0, 0);
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getTimer() > 0.2)
			{
				Fire();
				setPhase(3);
				resetTimer();
			}
		}
		else if (getPhase() == 3)
		{
			if (getTimer() > 0.3)
			{
				Fire();
				setPhase(4);
				resetTimer();
			}
		}
		else if (getPhase() == 4)
		{
			if (getTimer() > 1.2)
			{
				Fire();
				setPhase(5);
				resetTimer();
			}
		}
		else if (getPhase() == 5)
		{
			if (getTimer() > 0.8)
			{
				if (getRotation() > 150)
					rotate(-25 * MainTime.GetTimeDeltaF());
				else
					setRotation(150);

				setDelta(-75, -100);
			}
		}
	}
	else if (getType() == 3)
		{
		if (getPhase() == 0)
		{
			setRotation(90);
			setDelta(300, 0);
			if (getTimer() > 1.75)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 1.75, getLastSwitch().y + getDelta().y * 1.75);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getRotation() < 180)
				rotate(125 * MainTime.GetTimeDeltaF());
			else
				setRotation(180);

			if (getTimer() > 0.25)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 0.25, getLastSwitch().y + getDelta().y * 0.25);
				setPosition(getLastSwitch());
				setDelta(0, 0);
			}

			if (getTimer() > 0.75)
			{
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getTimer() > 0.5)
			{
				Fire();
				setPhase(3);
				resetTimer();
			}
		}
		else if (getPhase() == 3)
		{
			if (getTimer() > 1.5)
			{
				Fire();
				setPhase(4);
				resetTimer();
			}
		}
		else if (getPhase() == 4)
		{
			if (getTimer() > 1)
			{
				setDelta(0, -150);
				setPhase(5);
				resetTimer();
			}
		}
		}
	else if (getType() == 4)
		{
		if (getPhase() == 0)
		{
			setRotation(270);
			setDelta(-300, 0);
			if (getTimer() > 1.75)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 1.75, getLastSwitch().y + getDelta().y * 1.75);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getRotation() > 180)
				rotate(-125 * MainTime.GetTimeDeltaF());
			else
				setRotation(180);

			if (getTimer() > 0.25)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 0.25, getLastSwitch().y + getDelta().y * 0.25);
				setPosition(getLastSwitch());
				setDelta(0, 0);
			}

			if (getTimer() > 1.75)
			{
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getTimer() > 0.5)
			{
				Fire();
				setPhase(3);
				resetTimer();
			}
		}
		else if (getPhase() == 3)
		{
			if (getTimer() > 1.5)
			{
				Fire();
				setPhase(4);
				resetTimer();
			}
		}
		else if (getPhase() == 4)
		{
			if (getTimer() > 1)
			{
				setDelta(0, -150);
				setPhase(5);
				resetTimer();
			}
		}
		}
	else if (getType() == 5)
		{
		if (getPhase() == 0)
		{
			setRotation(180);
			setDelta(0, 300);
			if (getTimer() > 1)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 1, getLastSwitch().y + getDelta().y * 1);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			setDelta(0, 0);

			if (getTimer() > 1)
			{
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getTimer() > 0.25)
			{
				Fire();
				setPhase(3);
				resetTimer();
			}
		}
		else if (getPhase() == 3)
		{
			if (getTimer() > 1.25)
			{
				setDelta(0, -100);
				setPhase(4);
				resetTimer();
			}
		}
		}
	else if (getType() == 6)
		{
		if (getPhase() == 0)
		{
			setRotation(180);
			setDelta(0, 400);
			if (getTimer() > 1.5)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 1.5, getLastSwitch().y + getDelta().y * 1.5);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getDelta().x < 400)
				setDelta(getDelta().x + 375 * MainTime.GetTimeDeltaF(), getDelta().y);
			else
				setDelta(400.f, getDelta().y);

			if (getDelta().y > 0)
				setDelta(getDelta().x, getDelta().y - 375 * MainTime.GetTimeDeltaF());
			else
				setDelta(getDelta().x, 0.f);

			if (getRotation() > 90)
				rotate(-85 * MainTime.GetTimeDeltaF());
			else
				setRotation(90);

			if (getTimer() > 2)
			{
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getDelta().x > 0)
				setDelta(getDelta().x - 375 * MainTime.GetTimeDeltaF(), getDelta().y);
			else
				setDelta(0.f, getDelta().y);

			if (getDelta().y > -250)
				setDelta(getDelta().x, getDelta().y - 375 * MainTime.GetTimeDeltaF());
			else
				setDelta(getDelta().x, -250.f);

			if (getRotation() > 0 && getRotation() < 340)
				rotate(-85 * MainTime.GetTimeDeltaF());
			else
				setRotation(0);

		}
		}
	else if (getType() == 7)
		{
		if (getPhase() == 0)
		{
			setRotation(180);
			setDelta(0, 400);
			if (getTimer() > 1.5)
			{
				NewLastSwitch(getLastSwitch().x + getDelta().x * 1.5, getLastSwitch().y + getDelta().y * 1.5);
				setPosition(getLastSwitch());
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			if (getDelta().x > -400)
				setDelta(getDelta().x + -375 * MainTime.GetTimeDeltaF(), getDelta().y);
			else
				setDelta(-400.f, getDelta().y);

			if (getDelta().y > 0)
				setDelta(getDelta().x, getDelta().y - 375 * MainTime.GetTimeDeltaF());
			else
				setDelta(getDelta().x, 0.f);

			if (getRotation() < 270)
				rotate(85 * MainTime.GetTimeDeltaF());
			else
				setRotation(270);

			if (getTimer() > 2)
			{
				setPhase(2);
				resetTimer();
			}
		}
		else if (getPhase() == 2)
		{
			if (getDelta().x < 0)
				setDelta(getDelta().x + 375 * MainTime.GetTimeDeltaF(), getDelta().y);
			else
				setDelta(0.f, getDelta().y);

			if (getDelta().y > -250)
				setDelta(getDelta().x, getDelta().y - 375 * MainTime.GetTimeDeltaF());
			else
				setDelta(getDelta().x, -250.f);

			if (getRotation() < 360 && getRotation() > 20)
				rotate(85 * MainTime.GetTimeDeltaF());
			else
				setRotation(0);

		}
		}
	else if (getType() == 100)
	{
		if (getPhase() == 0)
		{
			if (getPos().y > 0)
			{
				setPosition(960, 0);
				setDelta(0, 0);
				setPhase(1);
				resetTimer();
			}
		}
		else if (getPhase() == 1)
		{
			Fire();
		}
	}




	if (hit)
	{
		timer_hit += MainTime.GetTimeDeltaF();
		if (timer_hit >= 0.075f)
		{
			hit = false;
			timer_hit = 0;
		}
	}

	pos = sf::Vector2f(pos.x + Delta.x * MainTime.GetTimeDeltaF(), pos.y + Delta.y * MainTime.GetTimeDeltaF());

	if (!sf::IntRect(0, -410, 1920, 1490).contains(sf::Vector2i(pos)))
	{
		vie = 0;
	}
}

void Ennemies::Draw()
{
	std::string EnnemieToLoad = "E1";
	sf::Vector2f OriginToSet;

	if (Move_Type == 1 || Move_Type == 2 || Move_Type == 5)
	{
		EnnemieToLoad = "E1";
		getSprite(EnnemieToLoad).setRotation(0);
		OriginToSet = sf::Vector2f(getSprite(EnnemieToLoad).getGlobalBounds().width / 2, getSprite(EnnemieToLoad).getGlobalBounds().height / 2);
	}
	else if (Move_Type != 100)
	{
		EnnemieToLoad = "E2";
		getSprite(EnnemieToLoad).setRotation(0);
		OriginToSet = sf::Vector2f(getSprite(EnnemieToLoad).getGlobalBounds().width / 2, getSprite(EnnemieToLoad).getGlobalBounds().height / 2);
	}
	else
	{
		if (vie > 50)
		{
			EnnemieToLoad = "Boss1";
			getSprite(EnnemieToLoad).setRotation(0);
			OriginToSet = sf::Vector2f(getSprite(EnnemieToLoad).getGlobalBounds().width / 2, 0);
		}
		else
		{
			EnnemieToLoad = "Boss2";
			getSprite(EnnemieToLoad).setRotation(0);
			OriginToSet = sf::Vector2f(getSprite(EnnemieToLoad).getGlobalBounds().width / 2, 0);
		}
	}


	getSprite(EnnemieToLoad).setColor(sf::Color::White);
	if (hit)
		getSprite(EnnemieToLoad).setColor(sf::Color::Color(255, 0, 0, 200));

	
	getSprite(EnnemieToLoad).setOrigin(OriginToSet);
	getSprite(EnnemieToLoad).setRotation(m_rotation);
	getSprite(EnnemieToLoad).setPosition(pos);
	win.Window().draw(getSprite(EnnemieToLoad));


	if (Move_Type == 100)
	{
		FogAnim.Animate(getSprite("Fog_Anim"));
		getSprite("Fog_Anim").setOrigin(729, 0);
		getSprite("Fog_Anim").setPosition(pos);
		win.Window().draw(getSprite("Fog_Anim"));
	}
}


void RemoveAllEnnemies()
{
	while (ennemies.size() != 0)
		ennemies.pop_back();
}