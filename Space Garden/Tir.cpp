#include "Tir.hpp"
#include "Texture_SpriteManager.hpp"
#include "Window.hpp"

std::list<PlayerBullet> Bullets;

//sf::Texture _texture_tire;
//sf::Texture _texture_tire_spe1;
//sf::Texture _texture_tire_spe2;
//sf::Texture _texture_tire_spe_sin;
//bool one_pass = true;

PlayerBullet::PlayerBullet(sf::Vector2f _elemvector, int _type, int _player, int _damage, float DirTir)
{
	//if (one_pass == true)
	//{
	//	_texture_tire.loadFromFile("../Ressources/Tir basique.png");
	//	_texture_tire_spe1.loadFromFile("../Ressources/Tir pissenlit.png");
	//	_texture_tire_spe2.loadFromFile("../Ressources/TirPissenlitPetale.png");
	//	_texture_tire_spe_sin.loadFromFile("../Ressources/Tir poison.png");

	//	one_pass = false;
	//}

	/*if (_type == 2)
		sprite.setTexture(_texture_tire_spe1);
	else if (_type == 1)
	{
		sprite.setTexture(_texture_tire_spe_sin);
		sprite.setRotation(180);
	}
	else
		sprite.setTexture(_texture_tire);
	
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);*/

	Delta.y = -500;
	bul_pos = _elemvector;
	bul_vie = 1;
	sin_line = 0;
	timer = 0;
	type = _type;
	damage = _damage;
	player = _player;
	m_rotation = 0;

	if (_type == 1)
	{
		m_rotation = 180;
	}

	if (_type == 3)
	{
		Delta.x = 80.f * cos(DirTir);
		Delta.y = 80.f * sin(DirTir);
		//sprite.setTexture(_texture_tire_spe2);

		float angleCible = Angle_calc(bul_pos + Delta, bul_pos);
		//sprite.setRotation(angleCible * 180.0f / pi - 90.f);
		m_rotation = (angleCible * 180.0f / pi - 90.f);
	}

	//sprite.setPosition(bul_pos);
}


void PlayerBullet::Update()
{
	timer += MainTime.GetTimeDeltaF();
	bul_pos += Delta * MainTime.GetTimeDeltaF(); 
	
	if (type == 1)
	{
		sin_line += 225 * MainTime.GetTimeDeltaF();	// vitesse entre chaque polarités
		bul_pos.x += (sin((double)sin_line / 50) * MainTime.GetTimeDeltaF()) * 150; // vitesse
		m_rotation = (sin((double)sin_line / 50) * 20) + 180;
		//sprite.setRotation((sin((double)sin_line / 50) * 20) + 180);
	}

	//sprite.setPosition(bul_pos);

	if (!sf::IntRect(0, 0, 1920, 1080).contains(sf::Vector2i(bul_pos)))
		bul_vie = 0;
}



void PlayerBullet::TakeDamage()
{
	bul_vie = 0;
}

void PlayerBullet::Draw()
{
	if (type == 2)
	{
		getSprite("Tir_Pissenlit").setRotation(0);
		getSprite("Tir_Pissenlit").setOrigin(getSprite("Tir_Pissenlit").getGlobalBounds().width / 2, getSprite("Tir_Pissenlit").getGlobalBounds().height / 2);
		getSprite("Tir_Pissenlit").setRotation(m_rotation);
		getSprite("Tir_Pissenlit").setPosition(bul_pos);
		win.Window().draw(getSprite("Tir_Pissenlit"));
	}
	else if (type == 1)
	{
		getSprite("Tir_Sinu").setRotation(0);
		getSprite("Tir_Sinu").setOrigin(getSprite("Tir_Sinu").getGlobalBounds().width / 2, getSprite("Tir_Sinu").getGlobalBounds().height / 2);
		getSprite("Tir_Sinu").setRotation(m_rotation);
		getSprite("Tir_Sinu").setPosition(bul_pos);
		win.Window().draw(getSprite("Tir_Sinu"));
	}
	else if (type == 3)
	{
		getSprite("Tir_Pissenlit2").setRotation(0);
		getSprite("Tir_Pissenlit2").setOrigin(getSprite("Tir_Pissenlit2").getGlobalBounds().width / 2, getSprite("Tir_Pissenlit2").getGlobalBounds().height / 2);
		getSprite("Tir_Pissenlit2").setRotation(m_rotation);
		getSprite("Tir_Pissenlit2").setPosition(bul_pos);
		win.Window().draw(getSprite("Tir_Pissenlit2"));
	}
	else
	{
		getSprite("Tir_Default").setRotation(0);
		getSprite("Tir_Default").setOrigin(getSprite("Tir_Default").getGlobalBounds().width / 2, getSprite("Tir_Default").getGlobalBounds().height / 2);
		getSprite("Tir_Default").setRotation(m_rotation);
		getSprite("Tir_Default").setPosition(bul_pos);
		win.Window().draw(getSprite("Tir_Default"));
	}
}



void RemoveAllPlayerShoots()
{
	while (Bullets.size() != 0)
		Bullets.pop_back();
}