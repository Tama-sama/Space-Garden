#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Game.hpp"
#include "SoundManager.hpp"
#include "Explosion.hpp"

std::list<Ennemies> ennemies;

sf::Texture Ennemi1;
sf::Texture Ennemi2;
sf::Texture Boss;
sf::Texture Boss2;
sf::Image BossCollision;

bool Ennemies_one_pass = true;
Ennemies::Ennemies(sf::Vector2f Pos, int MoveType, int Life)
{
	if (Ennemies_one_pass)
	{
		Ennemi1.loadFromFile("../Ressources/E1.png");
		Ennemi2.loadFromFile("../Ressources/E2.png");
		Boss.loadFromFile("../Ressources/Boss.png");
		Boss2.loadFromFile("../Ressources/Boss2.png");
		BossCollision.loadFromFile("../Ressources/Boss_collision.png");
		Ennemies_one_pass = false;
	}


	if (MoveType == 1 || MoveType == 2 || MoveType == 5)
	{
		sprite.setTexture(Ennemi1);
		vie = 2;
	}
	else if (MoveType != 100)
	{
		sprite.setTexture(Ennemi2);
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
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(180);
	sprite.setPosition(pos);

	if (MoveType == 100)
	{
		pos = sf::Vector2f(960, -400);
		Delta = sf::Vector2f(0, 133);
		vie = 100;
		sprite.setRotation(0);
		sprite.setTexture(Boss);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, 0);
		sprite.setPosition(pos);
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

			sprite.setTexture(Boss2);
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


			float angleCible = 1.570;

			if (random == 0)
				angleCible = Angle_calc(pos, Player1.getPosition());
			else if (random == 1)
				angleCible = Angle_calc(pos, Player2.getPosition());

			sf::Vector2f tmpDelta(350 * cos(angleCible), 350 * sin(angleCible));

			EnnemiesShootsList.push_back(EnnemiesShoots(temppos, tmpDelta, -1, (angleCible * 180.0f / pi) - 90));

		}
	}
	else if (Move_Type == 3 || Move_Type == 4)
	{
		sf::Vector2f temppos(pos.x ,pos.y + 40);
		sf::Vector2f tmpDelta(0, 200);
		for (int i = -1; i < 2; i++)
		{
			tmpDelta.x = 100 * i;

			EnnemiesShootsList.push_back(EnnemiesShoots(temppos, tmpDelta, -2, -35 * i));
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
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(1392, 412), sf::Vector2f(0, 300 + (rand() % 50)), 2));
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(580, 412), sf::Vector2f(0, 300 + (rand() % 50)), 3));

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
					EnnemiesShootsList.push_back(EnnemiesShoots(sf::Vector2f(960, 160), sf::Vector2f(rand() % 450 - 250, 250), 5));
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
	if (hit)
	{
		timer_hit += MainTime.GetTimeDeltaF();
		sprite.setColor(sf::Color::Color(255,0,0,200));
		if (timer_hit >= 0.075f)
		{
			sprite.setColor(sf::Color::White);
			hit = false;
			timer_hit = 0;
		}
	}


	pos = sf::Vector2f(pos.x + Delta.x * MainTime.GetTimeDeltaF(), pos.y + Delta.y * MainTime.GetTimeDeltaF());
	sprite.setPosition(pos);

	if (!sf::IntRect(0, -410, 1920, 1490).contains(sf::Vector2i(pos)))
	{
		vie = 0;
	}
}

void RemoveAllEnnemies()
{
	while (ennemies.size() != 0)
		ennemies.pop_back();
}