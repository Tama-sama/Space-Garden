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
	float getTimer() const { return timer; };
	float getRotation() const { return m_rotation; };
	int getType() const { return Move_Type; };
	int getPhase() const { return phase; };
	sf::Vector2f getDelta() const { return Delta; };
	sf::Vector2f getLastSwitch() const { return LastSwitch; };
	bool isHit() const { return hit; };

	//sf::Sprite& getSprite() { return sprite; };
	void setRotation(float rotation) { m_rotation = rotation; };
	void rotate(float rotation) { m_rotation += rotation; };
	void setPosition(sf::Vector2f _pos) { pos = _pos;  };
	void setPosition(float X, float Y) { pos = sf::Vector2f(X, Y); };
	void TakeDamage(int Damage);
	void addTimer(float TimeToAdd) { timer += TimeToAdd; };
	void resetTimer() { timer = 0; };
	void setPhase(int NewPhase) { phase = NewPhase; };
	void setDelta(sf::Vector2f NewDelta) { Delta = NewDelta; };
	void setDelta(float X, float Y) { Delta = sf::Vector2f(X, Y); };
	void NewLastSwitch(sf::Vector2f NewSwitch) { LastSwitch = NewSwitch; };
	void NewLastSwitch(float X, float Y) { LastSwitch = sf::Vector2f(X, Y); };
	void Draw();

	void Update();
	void Fire();

	bool operator == (const Ennemies& s) const { return Delta == s.Delta && pos == s.pos && vie == s.vie; };
	bool operator != (const Ennemies& s) const { return !operator==(s); }

private:
	//sf::Sprite sprite;
	float m_rotation;
	sf::Vector2f pos;
	sf::Vector2f Delta;
	int vie;
	float timer;
	int Move_Type;
	int phase;

	float timer_hit;
	bool hit;
	sf::Vector2f LastSwitch;
};

extern std::list<Ennemies> ennemies;
void RemoveAllEnnemies();