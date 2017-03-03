#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Player.h"

#include "Map.h"

Map::Map()
{
	newMapCounter = 0;
}


void Map::setupStatic(sf::String textureInp)
{
	tileTexture.loadFromFile(textureInp);
	tileSprite.setTexture(tileTexture);
}

void Map::drawStatic(sf::RenderWindow& win, sf::View view)
{
	int x = view.getCenter().x - view.getSize().x/2;
	int y = view.getCenter().y - view.getSize().y/2;
	tileSprite.setPosition(x, y);
	win.draw(tileSprite);
}

void Map::drawStatic(sf::RenderWindow& win, sf::View view, int yDisp)
{
	int x = view.getCenter().x - view.getSize().x/2;
	int y = view.getCenter().y - view.getSize().y/2 + yDisp;
	tileSprite.setPosition(x, y);
	win.draw(tileSprite);
}

//Draw bitmap
//Format for regular tile where 12 is the x, 34 is the y -> 12,34
//Format for new map where 1 is the zone, 23 is the map number -> n1,23 
//Format for nothing -> xx,xx
void Map::setupBitmap(std::string currentFile, sf::RenderWindow& win)
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

			if(!isdigit(str[0]) || !isdigit(str[3]))
			{
				map.at(loadCounter.y).push_back(sf::Vector2i(-1, -1));
			}
			else if(str[0] == 'n')
			{
				//TODO setup new map mechanic in player class
				newZoneNum.push_back(str[1] - '0');
				newMapNum.push_back(((str[3] - '0') * 10) + (str[4] - '0'));
				changeMapCords.push_back(sf::Vector2i(loadCounter.x, loadCounter.y));
				newMapCounter++;
				map.at(loadCounter.y).push_back(sf::Vector2i(-1, -1));
			}
			else
			{
				//Gets first two numbers
				int x = (str[0] - '0') * 10 + (str[1] - '0');
				int y = (str[3] - '0') * 10 + (str[4] - '0');
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

void Map::drawBitmap(sf::RenderWindow& win)
{
	for(int j = 0; j < maxCords.y; j++)
	{
		for(int i = 0; i < maxCords.x; i++)
		{
			//If the map index isn't empty
			if(map[j][i].x != -1 && map[j][i].y != -1)
			{
				//Draws tiles
				tileSprite.setPosition(i * 64, j * 64);
				tileSprite.setTextureRect(sf::IntRect(map[j][i].x * 64, map[j][i].y * 64, 64, 64));
				win.draw(tileSprite);
			}
		}
	}

}

void Map::drawCollision(sf::RenderWindow& win, Player& player)
{
	for(int j = 0; j < maxCords.y; j++)
	{
		for(int i = 0; i < maxCords.x; i++)
		{
			//If the map index isn't empty
			if(map[j][i].x != -1 && map[j][i].y != -1)
			{
				//Draws collision tiles
				tileSprite.setPosition(i * 64, j * 64);
				tileSprite.setTextureRect(sf::IntRect(map[j][i].x * 64, map[j][i].y * 64, 64, 64));
				win.draw(tileSprite);

				//Checks for collision for player movement
				player.collisionZones(i, j);
			}
		}
	}
}

//******* ACCESSORS FOR NEW MAPS ************

std::vector<sf::Vector2i> Map::getNewMapCords()
{
	return changeMapCords;
}

int Map::getNewMapCounter()
{
	return newMapCounter;
}

std::vector<int> Map::getNewZoneNum()
{
	return newZoneNum;
}

std::vector<int> Map::getNewMapNum()
{
	return newMapNum;
}
