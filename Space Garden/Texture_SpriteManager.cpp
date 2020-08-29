#include "Texture_SpriteManager.hpp"

std::list<Sprite> SpriteList;

void LoadSprite(State _state)
{
	for (Ressources& ActualRessource : RessourcesList)
	{
		if (ActualRessource.state == _state)
		{
			if (ActualRessource.type == RessourceType::TEXTURE)
			{
				SpriteList.push_back(Sprite(ActualRessource.name, ActualRessource.state, ActualRessource.path));
			}

		}
	}
}

sf::Sprite& getSprite(std::string Name)
{
	for (Sprite& ActualSprite : SpriteList)
	{
		if (ActualSprite.getName() == Name)
		{
			ActualSprite.getSprite().setTexture(ActualSprite.getTexture());
			return ActualSprite.getSprite();
		}
	}
}

sf::Texture& getTexture(std::string Name)
{
	for (Sprite& ActualSprite : SpriteList)
	{
		if (ActualSprite.getName() == Name)
		{
			return ActualSprite.getTexture();
		}
	}
}

void RemoveAllSprites()
{
	bool Removed = true;
	while (Removed)
	{
		Removed = false;
		for (Sprite& ActualSprite : SpriteList)
		{
			if (ActualSprite.getState() != State::ALL)
			{
				SpriteList.remove(ActualSprite);
				Removed = true;
				break;
			}
		}
	}
}