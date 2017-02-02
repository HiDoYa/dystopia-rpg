#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		sf::Texture texture;
		//Top and bottom of sprite
		sf::Sprite sprite-fore;
		sf::Sprite sprite-mid;
		sf::RectangleShape collisionRectangle;
		bool isMouseOver;
		bool openBox;
		bool closeBox;
		int textNum;
		sf::Clock clk;
		sf::Time tme;
		std::vector<std::string> sVec;
	public:
		Npc(int, int, sf::String);
		void setTexture(sf::String);
		void setScale(float);
		void setPos(int, int);
		sf::Texture getTexture();
		sf::Sprite getSprite();
		void autoMove();
		void moveAwayFromChar(int, int);
		void moveTowardChar(int, int);
		bool mouseOver(sf::Sprite);
		bool getColliding(sf::Sprite);
		bool getColliding(sf::RectangleShape);
		void speak(sf::String, sf::String, Textbox&);
};

#endif
