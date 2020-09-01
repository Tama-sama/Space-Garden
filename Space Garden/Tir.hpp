#pragma once
#include "Tools.hpp"

///////////////////////
// Class tir joueur  //
///////////////////////
class PlayerBullet
{
public:
	PlayerBullet(sf::Vector2f _elemvector, int _type, int _player, int _damage, float DirTir = 0);
	~PlayerBullet() {};

	//sf::Sprite& Sprite() { return sprite; };
	sf::Vector2f& Pos() { return bul_pos; };
	int getLife() { return bul_vie; };
	int getDamages() { return damage; };
	int getType() { return type; };
	int getOwner() { return player; };
	float getTimer() { return timer; };
	float getRotation() { return m_rotation; }

	void Update(); 
	void TakeDamage();
	void Draw();

	bool operator == (const PlayerBullet& s) const { return Delta == s.Delta && bul_vie == s.bul_vie && sin_line == s.sin_line && type == s.type && damage == s.damage && player == s.player && timer == s.timer; };
	bool operator != (const PlayerBullet& s) const { return !operator==(s); }

private:
	//sf::Sprite sprite;
	float m_rotation;
	sf::Vector2f bul_pos;
	sf::Vector2f Delta;
	int bul_vie;
	float sin_line;
	int type;
	int damage;
	int player;
	float timer;
};


extern std::list<PlayerBullet> Bullets;
void RemoveAllPlayerShoots();