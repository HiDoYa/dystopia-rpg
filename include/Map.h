#include <memory>
#include <SFML/Graphics.hpp>

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
		void midgroundRender(sf::RenderWindow&);
		std::unique_ptr<sf::RectangleShape[]> midgroundCollision(int);
		void midgroundCollisionBoxSet(int, int, int, int, int);
		void midgroundFrontRender(sf::RenderWindow&);
		void foregroundRender(sf::RenderWindow&);
		void allMapRender(sf::RenderWindow&);
};

#endif
