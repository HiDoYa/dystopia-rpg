#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
	public:
		Map(sf::String, int, int);
		void backgroundRender(sf::RenderWindow&);
		void getBitMap(sf::RenderWindow&);
		void foregroundRender(sf::RenderWindow&);
		void allMapRender(sf::RenderWindow&);
};

#endif
