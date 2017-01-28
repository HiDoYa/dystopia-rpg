#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::RectangleShape collisionRectangle;
		sf::Clock clk;
		sf::Time tme;
		double lastTime;
		double currentTime;
	public:
		Player(int, int, sf::String);
		void setTexture(sf::String);
		void setScale(double);
		void setPos(int, int);
		void movePos(int);
		void mouseAndCharAngle(sf::Vector2i);
		void rotatePos(int);
		sf::Texture getTexture();
		sf::Sprite getSprite();
		sf::RectangleShape getCollisionRectangle();
};

#endif
