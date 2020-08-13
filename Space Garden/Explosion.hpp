#include "Tools.hpp"

///////////////////////
// Class Explosions  //
///////////////////////
class Explosion
{
public:
	Explosion(sf::Vector2f _elemvector, int _type);
	~Explosion() {};

	float getTimer() const { return timer; };
	sf::Vector2f getPos() const { return pos; };

	void setTimer(float Time) { timer = Time; };
	void addTimer(float AddTime) { timer += AddTime; };


	sf::Sprite& getSprite() { return sprite; };
	CAnimations& getAnimator() { return animator; };


	bool operator == (const Explosion& s) const { return pos == s.pos && anim == s.anim && timer == s.timer; };
	bool operator != (const Explosion& s) const { return !operator==(s); };
private:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::IntRect anim;
	CAnimations animator;
	float timer;
};



extern std::list<Explosion> Explosions;