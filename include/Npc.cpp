#include "Npc.h"

Npc::Npc(int x, int y, sf::String nameTexture)
{
	texture.loadFromFile(nameTexture);

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Npc::setTexture(sf::String nameTexture)
{
	texture.loadFromFile(nameTexture);
}

void Npc::setScale(float num)
{
	sprite.setScale(sf::Vector2f(num, num));
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

void Npc::setPos(int x, int y)
{
	sprite.setPosition(x, y);
}

void Npc:speak(sf::String)
{
	//if mouse pressed and char is within certain range of posX, posY, talk
}
