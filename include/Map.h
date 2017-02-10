#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		sf::Sprite tileSprite;
		sf::Texture tileTexture;
		std::vector<std::vector<sf::Vector2i>> map;
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
