#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		Environment(int, int, sf::String);
		void setScale(int);
		void setPosition(int, int);
		bool getColliding(sf::RectangleShape);
		bool getColliding(sf::Sprite);
		sf::Sprite getSprite();
};

#endif
