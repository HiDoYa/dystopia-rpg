#include "Map.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

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
void Map::getBitmap(sf::String currentFile, sf::RenderWindow& win)
{
	std::ifstream mapFile;
	mapFile.open(currentMap);

	std::string currentLine;

	sf::Vector2f tiles[100][100];

	if(mapFile.is_open())
	{
		std::string tileTexturesLoc;
		mapFile >> tileTexturesLoc;
		tileTexture.loadFromFile(tileTexturesLoc);
		tileSprite.setTexture(tileTexture);

		while(!mapFile.eof())
		{
			mapFile >> currentLine;
			for(int i = 0; i < currentLine.length(); i++)
			{
				if(isdigit(currentLine[i]))
				{
				}
			}
		}
	}
	win.draw(sprite);
}

void Map::renderBitmap()
{
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
