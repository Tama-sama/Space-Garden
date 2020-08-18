#pragma once
#include "Tools.hpp"

/////////////////////
// Class Ennemies  //
/////////////////////
class Ennemies
{
public:
	Ennemies(sf::Vector2f Pos, int MoveType, int Life = -1);
	~Ennemies() {};


	int getLife() const { return vie; };
	sf::Vector2f getPos() const { return pos; };

	sf::Sprite& getSprite() { return sprite; };
	void setPosition(sf::Vector2f _pos) { pos = _pos; sprite.setPosition(pos); };
	void TakeDamage(int Damage);

	bool operator == (const Ennemies& s) const { return Delta == s.Delta && pos == s.pos && vie == s.vie; };
	bool operator != (const Ennemies& s) const { return !operator==(s); }

private:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f Delta;
	int vie;
	float timer;
	int Move_Type;
	int phase;

	float timer_hit;
	bool hit;
};

extern std::list<Ennemies> ennemies;
