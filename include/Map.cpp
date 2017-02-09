#include "Map.h"
#include <fstream>
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

//Draw bitmap
void Map::getBitMap(sf::String mapFile, sf::RenderWindow& win)
{
	ifstream mapFile;
	mapFile.open(currentMap);
	mapFile >> mapLength >> mapHeight;
	for(int x = 0; x < mapLength; i++)
	{
		for(int y = 0; i y < mapHeight; y++)
		{
		}
	}
	win.draw(sprite);
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
