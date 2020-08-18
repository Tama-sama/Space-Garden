#include "Explosion.hpp"

sf::Texture _exposion_1;
sf::Texture _exposion_2;
sf::Texture _exposion_Boss1;
sf::Texture _exposion_Boss2;
sf::Texture _exposion_logo;
bool Explo_one_pass = true;

Explosion::Explosion(sf::Vector2f _elemvector, int _type) 
{
	if (Explo_one_pass)
	{
		_exposion_1.loadFromFile("../Ressources/Explosion_ennemi_1.png");
		_exposion_2.loadFromFile("../Ressources/Explosion_ennemi_2.png");
		_exposion_Boss1.loadFromFile("../Ressources/Explosion_boss_1.png");
		_exposion_Boss2.loadFromFile("../Ressources/Explosion_boss_2.png");
		_exposion_logo.loadFromFile("../Ressources/LOGO_explo.png");

		Explo_one_pass = false;
	}


	if (_type == 1 || _type == 2 || _type == 5)
	{
		sprite.setTexture(_exposion_1);
		anim = sf::IntRect(0, 0, 256, 262);
	}
	else if (_type == 98)
	{
		sprite.setTexture(_exposion_Boss1);
		anim = sf::IntRect(0, 0, 437, 343);
	}
	else if (_type == 99)
	{
		sprite.setTexture(_exposion_Boss2);
		anim = sf::IntRect(0, 0, 437, 434);
	}
	else if (_type == 100)
	{
		sprite.setTexture(_exposion_logo);
		anim = sf::IntRect(0, 0, 412, 428);
	}
	else
	{
		sprite.setTexture(_exposion_2);
		anim = sf::IntRect(0, 0, 325, 262);
	}

	animator.Initialitation(0, sf::Vector2i(anim.width, anim.height), 0.075f, 5);

	sprite.setOrigin(anim.width / 2, anim.height / 2);
	pos = _elemvector;
	timer = 0;
}


std::list<Explosion> Explosions;