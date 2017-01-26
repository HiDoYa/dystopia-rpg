#include "Npc.h"

Npc::Npc(int x, int y)
{
	//Load sprite?

	posX = x;
	posY = y;
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

void Npc::setPosX(int x)
{
	posX = x;
}

void Npc::setPosY(int y)
{
	posY = y;
}

void Npc:speak(sf::String)
{
	//if mouse pressed and char is within certain range of posX, posY, talk
}
