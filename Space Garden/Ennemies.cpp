#include "Ennemies.hpp"

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
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(180);
	sprite.setPosition(pos);

}


void Ennemies::TakeDamage(int Damage)
{
	vie -= Damage;
}