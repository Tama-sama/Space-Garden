#pragma once
#include "Tools.hpp"

class Buffs
{
public:
	Buffs(int type, sf::Vector2f pos);
	~Buffs();

	sf::Vector2f getpos() const { return m_pos; };
	bool Exist() const { return m_life > 0; }
	int getType() const { return m_type; };

	void Update();
	void Kill() { m_life = 0; };

	bool operator == (const Buffs& s) const { return m_pos == s.m_pos && m_delta == s.m_delta && m_life == s.m_life && m_type == s.m_type && m_timer == s.m_timer; };
	bool operator != (const Buffs& s) const { return !operator==(s); };

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_delta;
	int m_life;
	int m_type;
	float m_timer;
};

extern std::list<Buffs> BuffsList;

void RemoveAllBuffs();