#include "Player.h"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		//Used to setup bitmaps
		sf::Sprite tileSprite;
		sf::Texture tileTexture;
		std::vector<std::vector<sf::Vector2i>> map;
		sf::Vector2i loadCounter;

		//Used to load maps
		sf::Vector2i maxCords;
	public:
		Map();
		void setupStatic(sf::String textureInp);
		void drawStatic(sf::RenderWindow&, sf::View);
		void setupBitmap(std::string, sf::RenderWindow&);
		void drawBitmap(sf::RenderWindow&);
		void drawCollision(sf::RenderWindow&, Player&);
};

#endif
