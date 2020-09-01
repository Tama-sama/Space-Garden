#include "Tir.hpp"
#include "Texture_SpriteManager.hpp"
#include "Window.hpp"

std::list<PlayerBullet> Bullets;

PlayerBullet::PlayerBullet(sf::Vector2f _elemvector, int _type, int _player, int _damage, float DirTir)
{
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

		double angleCible = Angle_calc(bul_pos + Delta, bul_pos);
		m_rotation = (float)(angleCible * 180.0f / pi - 90.f); //
	}
}


void PlayerBullet::Update()
{
	timer += MainTime.GetTimeDeltaF();
	bul_pos += Delta * MainTime.GetTimeDeltaF(); 
	
	if (type == 1) 
	{
		sin_line += 225 * MainTime.GetTimeDeltaF();	// vitesse entre chaque polarités
		bul_pos.x += (float)(sin((double)sin_line / 50) * MainTime.GetTimeDeltaF()) * 150; // vitesse //
		m_rotation = (float)(sin((double)sin_line / 50) * 20) + 180; //
	}


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