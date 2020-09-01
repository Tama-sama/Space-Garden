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
	int getLife() const { return m_vie; };
	bool isAtkSpeActive() const { return SpeAtkActive; };
	int getScore() const { return m_score; };
	int getPissenlitShoot() const { return m_shootPissenlit; };
	int getSinShoot() const { return m_shootSin; };
	bool isInvulnerable() const { return invulnerability; };
	int getController() const { return GameControler; };
	std::string getShip() const 
	{ 
		std::string Ship("Joueur"); 
		Ship += m_Ship; 
		return Ship; 
	};

	void setPosition(sf::Vector2f Pos) { m_pos = Pos; };
	void setPosition(float x, float y) { m_pos = sf::Vector2f(x, y); };
	void addPositionX(float AddX) { m_pos = sf::Vector2f(m_pos.x + AddX, m_pos.y); };
	void addPositionY(float AddY) { m_pos = sf::Vector2f(m_pos.x, m_pos.y + AddY); };
	void setLRectFrame(int Frame) { m_anim.left = 63 * Frame; };
	void TakeDamage(int Damage);
	void TimersUpdate(float TimingAdd);
	void setController(int controller) { GameControler = controller; };
	void setShip(char ShipColo) { m_Ship = ShipColo; };
	void addScore(int addition) { m_score += addition; };

	void addAtkPoint() { SpeAtkPts++; };
	void Heal() { m_vie++; };
	void addSinShoot() { m_shootSin++; };
	void addPissenlitShoot() { m_shootPissenlit++; };
	void SetFireSin();
	void FireSin();
	void FirePissenlit();
	void Fire();
	void Update();
	void Reset();
	void Draw();

private:
	int m_PlayerNumber;

	sf::IntRect m_anim;
	sf::Vector2f m_pos;
	
	int m_score;
	int m_vie;
	int m_damage;

	float m_firingTimer;
	float m_speTimer;
	int m_shootPissenlit;
	
	int SpeAtkPts;
	bool SpeAtkActive;
	bool shootingSin;
	int shootSinCounter;
	int m_shootSin;
	int GameControler;
	
	bool invulnerability;
	float InvuTimer;
	char m_Ship;
};
