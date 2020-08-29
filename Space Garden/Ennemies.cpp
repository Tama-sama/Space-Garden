#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Game.hpp"

std::list<Ennemies> ennemies;

sf::Texture Ennemi1;
sf::Texture Ennemi2;

bool Ennemies_one_pass = true;
Ennemies::Ennemies(sf::Vector2f Pos, int MoveType, int Life)
{
	if (Ennemies_one_pass)
	{
		Ennemi1.loadFromFile("../Ressources/E1.png");
		Ennemi2.loadFromFile("../Ressources/E2.png");

		Ennemies_one_pass = false;
	}


	if (MoveType == 1 || MoveType == 2 || MoveType == 5)
	{
		sprite.setTexture(Ennemi1);
		vie = 2;
	}
	else
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

}


void Ennemies::TakeDamage(int Damage)
{
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
}

void Ennemies::Update()
{
	if (hit)
	{
		timer_hit += MainTime.GetTimeDeltaF();
		sprite.setColor(sf::Color::Color(255,0,0,200));
		if (timer_hit >= 0.1f)
		{
			sprite.setColor(sf::Color::White);
			hit = false;
			timer_hit = 0;
		}
	}


	pos = sf::Vector2f(pos.x + Delta.x * MainTime.GetTimeDeltaF(), pos.y + Delta.y * MainTime.GetTimeDeltaF());
	sprite.setPosition(pos);

	if (!sf::IntRect(0, -100, 1920, 1080).contains(sf::Vector2i(pos)))
		vie = 0;
}

void RemoveAllEnnemies()
{
	while (ennemies.size() != 0)
		ennemies.pop_back();
}