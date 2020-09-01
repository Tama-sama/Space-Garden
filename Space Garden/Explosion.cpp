#include "Explosion.hpp"
#include "Texture_SpriteManager.hpp"
#include "Window.hpp"

std::list<Explosion> Explosions;


Explosion::Explosion(sf::Vector2f _elemvector, int _type) 
{
	type = _type;
	if (_type == 1 || _type == 2 || _type == 5)
	{
		anim = sf::IntRect(0, 0, 256, 262);
	}
	else if (_type == 98)
	{
		anim = sf::IntRect(0, 0, 437, 343);
	}
	else if (_type == 99)
	{
		anim = sf::IntRect(0, 0, 437, 434);
	}
	else if (_type == 100)
	{
		anim = sf::IntRect(0, 0, 412, 428);
	}
	else
	{
		anim = sf::IntRect(0, 0, 325, 262);
	}

	animator.Initialitation(0, sf::Vector2i(anim.width, anim.height), 0.075f, 5);

	pos = _elemvector;
	timer = 0;
	life = 1;
}

void Explosion::update()
{
	if (animator.getXFrame() < animator.getMaxXFrame() - 1)
		animator.Animate();

	if (animator.getXFrame() >= animator.getMaxXFrame() - 1)
	{
		timer += MainTime.GetTimeDeltaF();
		if (timer >= 0.075f)
		{
			life = 0;
		}
	}
}

void Explosion::draw()
{
	if (type == 1 || type == 2 || type == 5)
	{
		getSprite("Explosion_E1").setTextureRect(animator.getAnimateRect());
		getSprite("Explosion_E1").setOrigin(getSprite("Explosion_E1").getGlobalBounds().width / 2, getSprite("Explosion_E1").getGlobalBounds().height / 2);
		getSprite("Explosion_E1").setPosition(pos);
		win.Window().draw(getSprite("Explosion_E1"));
	}
	else if (type == 98)
	{
		getSprite("Explosion_B1").setTextureRect(animator.getAnimateRect());
		getSprite("Explosion_B1").setOrigin(getSprite("Explosion_B1").getGlobalBounds().width / 2, getSprite("Explosion_B1").getGlobalBounds().height / 2);
		getSprite("Explosion_B1").setPosition(pos);
		win.Window().draw(getSprite("Explosion_B1"));
	}
	else if (type == 99)
	{
		getSprite("Explosion_B2").setTextureRect(animator.getAnimateRect());
		getSprite("Explosion_B2").setOrigin(getSprite("Explosion_B2").getGlobalBounds().width / 2, getSprite("Explosion_B2").getGlobalBounds().height / 2);
		getSprite("Explosion_B2").setPosition(pos);
		win.Window().draw(getSprite("Explosion_B2"));
	}
	else if (type == 100)
	{
		getSprite("Explosion_logo").setTextureRect(animator.getAnimateRect());
		getSprite("Explosion_logo").setOrigin(getSprite("Explosion_logo").getGlobalBounds().width / 2, getSprite("Explosion_logo").getGlobalBounds().height / 2);
		getSprite("Explosion_logo").setPosition(pos);
		win.Window().draw(getSprite("Explosion_logo"));
	}
	else
	{
		getSprite("Explosion_E2").setTextureRect(animator.getAnimateRect());
		getSprite("Explosion_E2").setOrigin(getSprite("Explosion_E2").getGlobalBounds().width / 2, getSprite("Explosion_E2").getGlobalBounds().height / 2);
		getSprite("Explosion_E2").setPosition(pos);
		win.Window().draw(getSprite("Explosion_E2"));
	}
}


void RemoveAllExplosions()
{
	while (Explosions.size() != 0)
		Explosions.pop_back();
}