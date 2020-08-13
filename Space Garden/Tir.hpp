#include "Tools.hpp"

///////////////////////
// Class tir joueur  //
///////////////////////
class PlayerBullet
{
public:
	PlayerBullet(sf::Vector2f _elemvector, int _type, int _player, int _damage);
	~PlayerBullet() {};

	sf::Sprite& Sprite() { return sprite; };
	sf::Vector2f& Pos() { return bul_pos; };

	bool operator == (const PlayerBullet& s) const { return DeltaX == s.DeltaX && DeltaY == s.DeltaY && bul_vie == s.bul_vie && sin_line == s.sin_line && type == s.type && damage == s.damage && player == s.player && timer == s.timer; };
	bool operator != (const PlayerBullet& s) const { return !operator==(s); }

private:
	sf::Sprite sprite;
	sf::Vector2f bul_pos;
	float DeltaX;
	float DeltaY;
	int bul_vie;
	float sin_line;
	int type;
	int damage;
	int player;
	float timer;
};


extern std::list<PlayerBullet> Bullets;
