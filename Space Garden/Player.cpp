#include "Player.hpp"
#include "StateManager.hpp"
#include "SoundManager.hpp"

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
	SpeAtkPts = 0;
	SpeAtkActive = false;
	shootSinCounter = 0;
	m_speTimer = 3;
	GameControler = -2;
	m_Ship = 'R';
}

void Player::TimersUpdate(float TimingAdd)
{
	m_firingTimer += TimingAdd;
	m_speTimer += TimingAdd;
	InvuTimer += TimingAdd;
}

void Player::TakeDamage(int Damage)
{
	if (!invulnerability)
	{
		invulnerability = true;
		InvuTimer = 0;
		m_vie -= Damage;
	}

	if (m_vie < 0) 
		m_vie = 0;
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

			if (state != State::MAIN_MENU)
				getSound("shoot").play();
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
				getSound("shoot").play();
			}
			else
			{
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x - 25, m_pos.y + 10), 0, m_PlayerNumber, 0));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 0, m_PlayerNumber, 0));
				Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x + 25, m_pos.y + 10), 0, m_PlayerNumber, 0));
			}
			

			SpeAtkPts--;
			if (numbersOfShoots >= 2)
			{
				numbersOfShoots = 0;
			}
			m_firingTimer = 0.f;
		}
	}
}

void Player::FirePissenlit()
{
	if (m_speTimer >= 2 && m_shootPissenlit > 0)
	{
		m_speTimer = 0;
		m_shootPissenlit--;
		Bullets.push_back(PlayerBullet(sf::Vector2f(m_pos.x, m_pos.y), 2, m_PlayerNumber, 5));
	}
}

void Player::SetFireSin()
{
	if (m_speTimer >= 2 && m_shootSin > 0)
	{
		m_speTimer = 0;
		m_shootSin--;
		shootingSin = true;
	}
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

void Player::Update()
{
	if (invulnerability)
	{
		InvuTimer += MainTime.GetTimeDeltaF();
		if (InvuTimer > 2.f)
		{
			InvuTimer = 0;
			invulnerability = false;
		}
	}
}

void Player::Reset()
{
	m_anim = sf::IntRect(0, 0, 62, 101);

	m_vie = 3;
	m_score = 0;
	m_firingTimer = 0;
	m_shootPissenlit = 3;
	shootingSin = false;
	m_shootSin = 3;
	invulnerability = false;
	InvuTimer = 0;
}