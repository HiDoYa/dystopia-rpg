#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		sf::Sprite tileSprite;
		sf::Texture tileTexture;
		sf::Vector2i tiles[100][100];
		sf::Vector2i loadCounter;
		sf::Vector2i maxCords;
	public:
		Map();
		void backgroundRender(sf::RenderWindow&);
		void getBitmap(std::string, sf::RenderWindow&);
		void renderBitmap(sf::RenderWindow&);
		void foregroundRender(sf::RenderWindow&);
		void allMapRender(sf::RenderWindow&);
};

#endif
