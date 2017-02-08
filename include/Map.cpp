#include "Map.h"
#include <iostream>
#include <memory>

Map::Map(sf::String textureStr, int x, int y)
{
	texture.loadFromFile(textureStr);

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Map::backgroundRender(sf::RenderWindow& win)
{
}

void Map::midgroundRender(sf::RenderWindow& win)
{
	win.draw(sprite);
}

std::unique_ptr<sf::RectangleShape[]> Map::midgroundCollision(int numRect)
{
	//Dynamically allocate RectangleShape (based on how many squares are going to be needed)
	std::unique_ptr<sf::RectangleShape[]> rectArrPtr( new sf::RectangleShape[numRect]);
	return rectArrPtr;
}

void Map::midgroundCollisionBoxSet(int arrNum, int startX, int startY, int width, int height)
{
	//Sets each box
}

void Map::midgroundFrontRender(sf::RenderWindow& win)
{
	//win.draw
}

void Map::foregroundRender(sf::RenderWindow& win)
{
	//win.draw
}

void Map::allMapRender(sf::RenderWindow& win)
{
	backgroundRender(win);
	midgroundRender(win);
	midgroundFrontRender(win);
	foregroundRender(win);
}
