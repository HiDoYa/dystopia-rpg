#include "Npc.h"

Npc::Npc(int x, int y, sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Npc::setTexture(sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}
}

void Npc::setScale(double num)
{
	sprite.setScale(sf::Vector2f(num, num));
}

void Npc::setPos(int x, int y)
{
	sprite.setPosition(x, y);
}

sf::Texture Npc::getTexture()
{
	return texture;
}

sf::Sprite Npc::getSprite()
{
	return sprite;
}

void Npc::autoMove()
{
}

void Npc::moveAwayFromChar(int charPosX, int charPosY)
{
}

void Npc::moveTowardChar(int charPosX, int charPosY)
{
}

void Npc::speak(sf::String)
{
	//if mouse pressed and char is within certain range of posX, posY, talk
}
