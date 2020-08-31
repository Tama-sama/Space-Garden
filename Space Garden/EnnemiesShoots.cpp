#include "EnnemiesShoots.hpp"
#include "Game.hpp"

std::list<EnnemiesShoots> EnnemiesShootsList;

sf::Texture TexEnnemies_shoot1;
sf::Texture TexEnnemies_shoot2;
sf::Texture TexBoss_shoot1;
sf::Texture TexBoss_shoot2;
bool EnnemieShoot_pass = true;

EnnemiesShoots::EnnemiesShoots(sf::Vector2f pos, sf::Vector2f Delta, int type, float rotation)
{
	if (EnnemieShoot_pass)
	{
		TexEnnemies_shoot1.loadFromFile("../Ressources/Tir_ennemi_1.png");
		TexEnnemies_shoot2.loadFromFile("../Ressources/Tir_ennemi_2.png");

		TexBoss_shoot1.loadFromFile("../Ressources/Tir_boss_anim_11.png");
		TexBoss_shoot2.loadFromFile("../Ressources/Tir_boss_2.png");

		EnnemieShoot_pass = false;
	}

	//normal
	if (type == -1)
	{
		m_sprite.setTexture(TexEnnemies_shoot1);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setRotation(rotation);
		m_delta = Delta;
	}
	else if (type == -2)
	{
		m_sprite.setTexture(TexEnnemies_shoot2);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setRotation(rotation);
		m_delta = Delta;
	}

	// Boss
	else if (type == 4)
	{
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



		m_delta.x = Delta.x * cos(angleCible);
		m_delta.y = Delta.y * sin(angleCible);

		anim = sf::IntRect(0,0,30,45);
		m_sprite.setTexture(TexBoss_shoot2);
		m_sprite.setTextureRect(anim);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setRotation((angleCible * 180.0f / pi) - 90);
	}
	else
	{
		anim = sf::IntRect(0,0,63,45);
		m_sprite.setTexture(TexBoss_shoot1);
		m_sprite.setTextureRect(anim);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

		m_delta.x = Delta.x;
		m_delta.y = Delta.y;
	}

	m_pos = pos;
	m_life = 1;
	m_type = type;
	m_timer = 0;
	timer_anim = 0;
}


EnnemiesShoots::~EnnemiesShoots()
{

}


void EnnemiesShoots::update()
{
	m_timer += MainTime.GetTimeDeltaF();
	m_pos += m_delta * MainTime.GetTimeDeltaF();
	
	m_sprite.setPosition(m_pos);

	if (!sf::IntRect(0, 0, 1920, 1080).contains(sf::Vector2i(m_pos)))
		m_life = 0;
}






void RemoveAllEnnemiesShoots()
{
	while (EnnemiesShootsList.size() != 0)
		EnnemiesShootsList.pop_back();
}