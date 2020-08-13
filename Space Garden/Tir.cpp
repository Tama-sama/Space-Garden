#include "Tir.hpp"

std::list<PlayerBullet> Bullets;

sf::Texture _texture_tire;
sf::Texture _texture_tire_spe;
sf::Texture _texture_tire_spe_sin;
bool one_pass = true;

PlayerBullet::PlayerBullet(sf::Vector2f _elemvector, int _type, int _player, int _damage)
{
	if (one_pass == true)
	{
		_texture_tire.loadFromFile("../Ressources/Tir basique.png");
		_texture_tire_spe.loadFromFile("../Ressources/Tir pissenlit.png");
		_texture_tire_spe_sin.loadFromFile("../Ressources/Tir poison.png");

		//_texture_tire = sfTexture_createFromFile("../Ressources/Tir basique.png", NULL);
		//_texture_tire_spe = sfTexture_createFromFile("../Ressources/Tir pissenlit.png", NULL);
		//_texture_tire_spe_sin = sfTexture_createFromFile("../Ressources/Tir poison.png", NULL);

		one_pass = false;
	}

	//PlayerBullet* tempBullet = (PlayerBullet*)calloc(1, sizeof(PlayerBullet));
	//tempBullet->sprite = sfSprite_create();
	
	if (_type == 2)
		sprite.setTexture(_texture_tire_spe); //sfSprite_setTexture(tempBullet->sprite, _texture_tire_spe, sfTrue);	
	else if (_type == 1)
	{
		//sfSprite_setTexture(tempBullet->sprite, _texture_tire_spe_sin, sfTrue);
		//sfSprite_setRotation(tempBullet->sprite, 180);
		//_elemvector.y += sfSprite_getGlobalBounds(tempBullet->sprite).height - 23;
		sprite.setTexture(_texture_tire_spe_sin);
		sprite.setRotation(180);

		_elemvector.y += sprite.getGlobalBounds().height - 23;
		_elemvector.x += 18;
	}
	else
		sprite.setTexture(_texture_tire); // sfSprite_setTexture(tempBullet->sprite, _texture_tire, sfTrue);
	
	DeltaY = -500;
	bul_pos = _elemvector;
	bul_vie = 1;
	sin_line = 0;
	type = _type;
	damage = _damage;
	player = _player;

	// ajouteListe(tempBullet);
}