#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Player.h"

#include "Map.h"

Map::Map()
{
	newMapCounter = 0;
}

//Tile-based: (Ground, collision, foreground)
//Static: (Background)

void Map::setupAll(sf::String mainFileNm)
{

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
	map.clear();
	loadCounter = sf::Vector2i(0, 0);
	maxCords = sf::Vector2i(0, 0);

	//Resets change map
	changeMapCords.clear();
	newMapCounter = 0;
	newZoneNum.clear();
	newMapNum.clear();

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
			if(str[0] == 'n')
			{
				//TODO setup new map mechanic in player class
				newZoneNum.push_back(str[1] - '0');
				newMapNum.push_back(((str[3] - '0') * 10) + (str[4] - '0'));
				changeMapCords.push_back(sf::Vector2i(loadCounter.x * 64, loadCounter.y * 64));
				newMapCounter++;
				map.at(loadCounter.y).push_back(sf::Vector2i(-1, -1));
			}
			else if(!isdigit(str[0]) || !isdigit(str[3]))
			{
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

//TODO Add foreground
//TODO Perhaps delete along with changeMap?
bool Map::newMap(Map& collision, Player& player, sf::RenderWindow& win)
{
	sf::Vector2i playerPos = sf::Vector2i(player.getPosition());

	for(int i = 0; i < newMapCounter; i++)
	{
		if(changeMapCords[i] == playerPos)
		{
			//collision.changeMap(newZoneNum[i], newMapNum[i], 1, win);
			//changeMap(newZoneNum[i], newMapNum[i], 0, win);
			return true;
		}
	}
	return false;
}

//TODO Refactor to process through a main map file which links to each individual map
//type indicates whether it is ground, collision, or foreground
void Map::changeMap(int zone, int map, int type, sf::RenderWindow& win)
{
	std::string fileAccString = "data/maps/";

	fileAccString += "z" + std::to_string(zone);

	switch (type)
	{
		case 0:
			fileAccString += "/ground/";
			break;
		case 1:
			fileAccString += "/collision/";
			break;
		case 2: 
			fileAccString += "/foreground/";
			break;
	}

	fileAccString += "m" + std::to_string(map);

	setupBitmap(fileAccString, win);
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
