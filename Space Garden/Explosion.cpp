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
		//_exposion_1 = sfTexture_createFromFile("../Ressources/Explosion_ennemi_1.png", NULL);
		//_exposion_2 = sfTexture_createFromFile("../Ressources/Explosion_ennemi_2.png", NULL);
		//_exposion_Boss1 = sfTexture_createFromFile("../Ressources/Explosion_boss_1.png", NULL);
		//_exposion_Boss2 = sfTexture_createFromFile("../Ressources/Explosion_boss_2.png", NULL);
		//_exposion_logo = sfTexture_createFromFile("../Ressources/LOGO_explo.png", NULL);

		_exposion_1.loadFromFile("../Ressources/Explosion_ennemi_1.png");
		_exposion_2.loadFromFile("../Ressources/Explosion_ennemi_2.png");
		_exposion_Boss1.loadFromFile("../Ressources/Explosion_boss_1.png");
		_exposion_Boss2.loadFromFile("../Ressources/Explosion_boss_2.png");
		_exposion_logo.loadFromFile("../Ressources/LOGO_explo.png");

		Explo_one_pass = false;
	}





	//explosion* tempExposion = (explosion*)calloc(1, sizeof(explosion));
	//tempExposion->sprite = sfSprite_create();

	if (_type == 1 || _type == 2 || _type == 5)
	{
		//sfSprite_setTexture(tempExposion->sprite, _exposion_1, sfTrue);
		//tempExposion->anim = (sfIntRect){ 0,0,256,262 };
		sprite.setTexture(_exposion_1);
		anim = sf::IntRect(0, 0, 256, 262);
	}
	else if (_type == 98)
	{
		//sfSprite_setTexture(tempExposion->sprite, _exposion_Boss1, sfTrue);
		//tempExposion->anim = (sfIntRect){ 0,0,437,343 };
		sprite.setTexture(_exposion_Boss1);
		anim = sf::IntRect(0, 0, 437, 343);
	}
	else if (_type == 99)
	{
		//sfSprite_setTexture(tempExposion->sprite, _exposion_Boss2, sfTrue);
		//tempExposion->anim = (sfIntRect){ 0,0,437,434 };
		sprite.setTexture(_exposion_Boss2);
		anim = sf::IntRect(0, 0, 437, 434);
	}
	else if (_type == 100)
	{
		//sfSprite_setTexture(tempExposion->sprite, _exposion_logo, sfTrue);
		//tempExposion->anim = (sfIntRect){ 0,0,412,428 };
		sprite.setTexture(_exposion_logo);
		anim = sf::IntRect(0, 0, 412, 428);
	}
	else
	{
		//sfSprite_setTexture(tempExposion->sprite, _exposion_2, sfTrue);
		//tempExposion->anim = (sfIntRect){ 0,0,325,262 };
		sprite.setTexture(_exposion_2);
		anim = sf::IntRect(0, 0, 325, 262);
	}

	animator.Initialitation(0, sf::Vector2i(anim.width, anim.height), 0.075f, 5);
	//sfSprite_setTextureRect(tempExposion->sprite, tempExposion->anim);
	//sfSprite_setOrigin(tempExposion->sprite, (sfVector2f) { sfSprite_getGlobalBounds(tempExposion->sprite).width / 2, sfSprite_getGlobalBounds(tempExposion->sprite).height / 2 });
	//tempExposion->pos = _elemvector;
	//sprite.setTextureRect(anim);
	sprite.setOrigin(anim.width / 2, anim.height / 2);
	pos = _elemvector;
	timer = 0;

	//Exposion_Ajout(tempExposion);

}


std::list<Explosion> Explosions;