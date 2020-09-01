#pragma once
#include "Tools.hpp"

class EnnemiesShoots
{
public:
	EnnemiesShoots(sf::Vector2f pos, sf::Vector2f Delta, int type, float rotation = -1);
	~EnnemiesShoots();

	sf::Vector2f getpos() const { return m_pos; };
	int getLife() const { return m_life; };
	float getRotation() const { return m_rotation; };

	void update();
	void draw();
	void TakeDamage() { m_life = 0; };

	//sf::Sprite& getSprite() { return m_sprite; };

	bool operator==(const EnnemiesShoots& s) const { return m_pos == s.m_pos && m_delta == s.m_delta && m_life == s.m_life; };
	bool operator!=(const EnnemiesShoots& s) const { return !operator==(s); };

private:
	//sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	sf::Vector2f m_delta;
	int m_life;
	float m_timer;
	int m_type;
	sf::IntRect anim;
	float timer_anim;
	float m_rotation;
};

extern std::list<EnnemiesShoots> EnnemiesShootsList;
void RemoveAllEnnemiesShoots();