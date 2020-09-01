#include "EnnemiesShoots.hpp"
#include "Game.hpp"
#include "Texture_SpriteManager.hpp"
#include "Window.hpp"

std::list<EnnemiesShoots> EnnemiesShootsList;

EnnemiesShoots::EnnemiesShoots(sf::Vector2f pos, sf::Vector2f Delta, int type, float rotation)
{
	m_rotation = 0;

	//normal
	if (type == -1 || type == -2)
	{
		m_rotation = rotation;
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


		double angleCible = 1.570;

		if (random == 0)
			angleCible = Angle_calc(pos, Player1.getPosition());
		else if (random == 1)
			angleCible = Angle_calc(pos, Player2.getPosition());



		m_delta.x = Delta.x * (float)cos(angleCible);
		m_delta.y = Delta.y * (float)sin(angleCible);

		anim = sf::IntRect(0,0,30,45);
		m_rotation = (float)(angleCible * 180.0f / pi) - 90;
	}
	else
	{
		anim = sf::IntRect(0,0,63,45);

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
	timer_anim += MainTime.GetTimeDeltaF();
	m_pos += m_delta * MainTime.GetTimeDeltaF();
	

	if (!sf::IntRect(0, 0, 1920, 1080).contains(sf::Vector2i(m_pos)))
		m_life = 0;


	if (m_type != -1 && m_type != -2)
	{
		if (timer_anim >= 0.2f)
		{
			timer_anim = 0.f;

			if (anim.left != anim.width * 2)
				anim.left += anim.width;
			else
				anim.left = 0;
		}
	}

}


void EnnemiesShoots::draw()
{
	if (m_type == -1)
	{
		getSprite("Tir_E1").setRotation(0);
		getSprite("Tir_E1").setOrigin(getSprite("Tir_E1").getGlobalBounds().width / 2, getSprite("Tir_E1").getGlobalBounds().height / 2);
		getSprite("Tir_E1").setRotation(m_rotation);
		getSprite("Tir_E1").setPosition(m_pos);
		win.Window().draw(getSprite("Tir_E1"));
	}
	else if (m_type == -2)
	{
		getSprite("Tir_E2").setRotation(0);
		getSprite("Tir_E2").setOrigin(getSprite("Tir_E2").getGlobalBounds().width / 2, getSprite("Tir_E2").getGlobalBounds().height / 2);
		getSprite("Tir_E2").setRotation(m_rotation);
		getSprite("Tir_E2").setPosition(m_pos);
		win.Window().draw(getSprite("Tir_E2"));
	}
	// Boss
	else if (m_type == 4)
	{
		getSprite("Tir_B2").setRotation(0);
		getSprite("Tir_B2").setTextureRect(anim);
		getSprite("Tir_B2").setOrigin(getSprite("Tir_B2").getGlobalBounds().width / 2, getSprite("Tir_B2").getGlobalBounds().height / 2);
		getSprite("Tir_B2").setRotation(m_rotation);
		getSprite("Tir_B2").setPosition(m_pos);
		win.Window().draw(getSprite("Tir_B2"));
	}
	else
	{
		getSprite("Tir_B1").setRotation(0);
		getSprite("Tir_B1").setTextureRect(anim);
		getSprite("Tir_B1").setOrigin(getSprite("Tir_B1").getGlobalBounds().width / 2, getSprite("Tir_B1").getGlobalBounds().height / 2);
		getSprite("Tir_B1").setRotation(m_rotation);
		getSprite("Tir_B1").setPosition(m_pos);
		win.Window().draw(getSprite("Tir_B1"));
	}
}



void RemoveAllEnnemiesShoots()
{
	while (EnnemiesShootsList.size() != 0)
		EnnemiesShootsList.pop_back();
}