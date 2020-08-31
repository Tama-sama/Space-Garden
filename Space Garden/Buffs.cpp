#include "Buffs.hpp"

std::list<Buffs> BuffsList;

Buffs::Buffs(int type, sf::Vector2f pos)
{
	m_pos = pos;
	m_type = type;
	m_life = 1;
	m_delta.y = -65;
	m_delta.x = 0;
	m_timer = 0.f;
}

Buffs::~Buffs()
{
}


void Buffs::Update()
{
	m_timer += MainTime.GetTimeDeltaF();
	if (m_timer > 1)
		m_delta.y = 225;

	m_pos += m_delta * MainTime.GetTimeDeltaF();

	if (!sf::IntRect(0, -100, 1920, 1180).contains(sf::Vector2i(m_pos)))
		m_life = 0;
}


void RemoveAllBuffs()
{
	while (BuffsList.size() != 0)
		BuffsList.pop_back();
}