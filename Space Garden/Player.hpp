#pragma once
#include "Tools.hpp"
#include "Tir.hpp"

class Player
{
public:
	Player(sf::Vector2f pos, int BaseDamages, int PlayerNumber);
	~Player() {};

	sf::Vector2f getPosition() const { return m_pos; };
	sf::IntRect getIntRect() const { return m_anim; };
	int getAtkPoints() const { return SpeAtkPts; };
	bool isAtkSpeActive() const { return SpeAtkActive; };

	void setPosition(sf::Vector2f Pos) { m_pos = Pos; };
	void setPosition(float x, float y) { m_pos = sf::Vector2f(x, y); };
	void addPositionX(float AddX) { m_pos = sf::Vector2f(m_pos.x + AddX, m_pos.y); };
	void addPositionY(float AddY) { m_pos = sf::Vector2f(m_pos.x, m_pos.y + AddY); };
	void setLRectFrame(int Frame) { m_anim.left = m_anim.width * Frame; };
	void addAtkPoint() { SpeAtkPts++; };

	void TimersUpdate(float TimingAdd);
	void SetFireSin();
	void FireSin();
	void FirePissenlit();
	void Fire();


private:
	int m_PlayerNumber;

	sf::IntRect m_anim;
	sf::Vector2f m_pos;
	
	int m_score;
	int m_vie;
	int m_damage;

	float m_firingTimer;
	int m_shootPissenlit;
	
	int SpeAtkPts;
	bool SpeAtkActive;
	bool shootingSin;
	int shootSinCounter;
	int m_shootSin;
	
	bool invulnerability;
	float InvuTimer;
};
