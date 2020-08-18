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
}