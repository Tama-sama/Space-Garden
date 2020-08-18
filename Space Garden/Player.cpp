#include "Player.hpp"
#include "StateManager.hpp"

Player::Player(sf::Vector2f pos, int BaseDamages, int PlayerNumber)
{
	m_PlayerNumber = PlayerNumber;
	m_anim = sf::IntRect(0, 0, 62, 101);
	m_pos = sf::Vector2f(pos);
	m_damage = BaseDamages;
	m_vie = 3;
	m_score = 0;
	m_firingTimer = 0;
	m_shootPissenlit = 3;
	shootingSin = false;
	m_shootSin = 3;
	invulnerability = false;
	InvuTimer = 0;
}

void Player::TimersUpdate(float TimingAdd)
{
	m_firingTimer += TimingAdd;
	InvuTimer += TimingAdd;

}

void Player::Fire()
{
	if (SpeAtkPts == 10)
		SpeAtkActive = true;
	else if (SpeAtkPts == 0)
		SpeAtkActive = false;

	if (!SpeAtkActive)
	{
		if (m_firingTimer >= 0.3)
		{
			Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 0, m_PlayerNumber, m_damage));
			m_firingTimer = 0.f;
		}
	}
	else
	{
		if (m_firingTimer >= 0.3)
		{
			static int numbersOfShoots = 0;
			numbersOfShoots++;

			if (state != State::MAIN_MENU)
			{
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x - 25, m_pos.y + 10), 0, m_PlayerNumber, m_damage));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 0, m_PlayerNumber, m_damage));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x + 25, m_pos.y + 10), 0, m_PlayerNumber, m_damage));
			}
			else
			{
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x - 25, m_pos.y + 10), 0, m_PlayerNumber, 0));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 0, m_PlayerNumber, 0));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x + 25, m_pos.y + 10), 0, m_PlayerNumber, 0));
			}
			

			if (numbersOfShoots >= 2)
			{
				SpeAtkPts--;
				numbersOfShoots = 0;
			}
			m_firingTimer = 0.f;
		}
	}
}

void Player::FirePissenlit()
{
	Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 2, m_PlayerNumber, 5));
}

void Player::SetFireSin()
{
	shootingSin = true;
}

void Player::FireSin()
{
	if (shootingSin)
	{
		if (m_firingTimer >= 0.06 && shootSinCounter < 20)
		{
			Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 1, m_PlayerNumber, 1));
			shootSinCounter++;
			m_firingTimer = 0;
		}
		else if (shootSinCounter >= 20)
		{
			shootSinCounter = 0;
			shootingSin = false;
		}
	}
}