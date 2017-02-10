#include "Map.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

Map::Map()
{
}

void Map::backgroundRender(sf::RenderWindow& win)
{
}

//Draw bitmap
void Map::getBitmap(std::string currentFile, sf::RenderWindow& win)
{
	//Loads file
	std::ifstream mapFile;
	mapFile.open(currentFile);

	//Sets loadcounter to start at location 0 in map
	loadCounter = sf::Vector2i(0, 0);
	maxCords = sf::Vector2i(0, 0);

	if(mapFile.is_open())
	{
		//Gets spritesheet
		std::string tileTexturesLoc;
		mapFile >> tileTexturesLoc;
		tileTexture.loadFromFile(tileTexturesLoc);
		tileSprite.setTexture(tileTexture);

		//Initializes str and gets first string
		std::string str;
		mapFile >> str;

		std::vector<sf::Vector2i> newColumn;
		map.push_back(newColumn);

		while(!mapFile.eof())
		{
			//Gets first two numbers
			int x = (str[0] - '0') * 10 + (str[1] - '0');
			int y = (str[3] - '0') * 10 + (str[4] - '0');

			if(!isdigit(str[0]) || !isdigit(str[3]))
			{
				map.at(loadCounter.y).push_back(sf::Vector2i(-1, -1));
			}
			else
			{
				map.at(loadCounter.y).push_back(sf::Vector2i(x, y));
			}

			//Change counter
			if(mapFile.peek() == '\n')
			{
				map.push_back(newColumn);
				loadCounter.x = 0;
				loadCounter.y++;
			}
			else
			{
				loadCounter.x++;
			}

			//Sets the max height/width
			if(maxCords.x < loadCounter.x)
			{
				maxCords.x = loadCounter.x;
			}
			if(maxCords.y < loadCounter.y)
			{
				maxCords.y = loadCounter.y;
			}

			//Gets the next string
			mapFile >> str;
		}

		//Apparently the end of a text file has a new line so I have to increment x to make up for it
		maxCords.x++;
	}

	mapFile.close();
}

void Map::renderBitmap(sf::RenderWindow& win)
{
	for(int j = 0; j < maxCords.y; j++)
	{
		for(int i = 0; i < maxCords.x; i++)
		{
			if(map[j][i].x != -1 && map[j][i].y != -1)
			{
				tileSprite.setPosition(i * 64, j * 64);
				tileSprite.setTextureRect(sf::IntRect(map[j][i].x * 64, map[j][i].y * 64, 64, 64));
				win.draw(tileSprite);
			}
		}
	}

}

void Map::foregroundRender(sf::RenderWindow& win)
{
	//win.draw
}

void Map::allMapRender(sf::RenderWindow& win)
{
	backgroundRender(win);
	foregroundRender(win);
}
