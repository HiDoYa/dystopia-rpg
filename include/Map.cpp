#include "Map.h"
#include "Player.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Map::Map()
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

//Draw bitmap
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

void Map::drawBitmap(sf::RenderWindow& win)
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

void Map::drawCollision(sf::RenderWindow& win, Player& player)
{
	for(int j = 0; j < maxCords.y; j++)
	{
		for(int i = 0; i < maxCords.x; i++)
		{
			if(!(map[j][i].x == -1 && map[j][i].y == -1))
			{
				tileSprite.setPosition(i * 64, j * 64);
				tileSprite.setTextureRect(sf::IntRect(map[j][i].x * 64, map[j][i].y * 64, 64, 64));
				win.draw(tileSprite);
				player.collisionZones(i, j);
			}
			
			//	sf::RectangleShape tileRect(sf::Vector2f(64, 64));
			//	tileRect.setPosition(i * 64, j * 64);

			//	int playerCenterX, playerCenterY;
			//	playerCenterX = player.getGlobalBounds().left + player.getGlobalBounds().width / 2;
			//	playerCenterY = player.getGlobalBounds().top + player.getGlobalBounds().height / 2;

			//	if(tileRect.getGlobalBounds().contains(playerCenterX, playerCenterY))
			//	{
			//		std::cout << "Colliding\n";
			//	}

			//	tileSprite.setPosition(i * 64, j * 64);
			//	tileSprite.setTextureRect(sf::IntRect(map[j][i].x * 64, map[j][i].y * 64, 64, 64));
			//	win.draw(tileSprite);
			//}
			//else
			//{
			//	std::cout << "Not colliding\n";
			//}
		}
	}
}
