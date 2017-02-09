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
	public:
		Map(sf::String, int, int);
		void backgroundRender(sf::RenderWindow&);
		void getBitmap(sf::String currentFile, sf::RenderWindow&);
		void renderBitmap()
		void foregroundRender(sf::RenderWindow&);
		void allMapRender(sf::RenderWindow&);
};

#endif
