#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::RectangleShape collisionRectangle;
		bool isMouseOver;
		bool openBox;
		bool closeBox;
		int textNum;
		sf::Clock clk;
		sf::Time tme;
	public:
		Npc(int, int, sf::String);
		void setTexture(sf::String);
		void setScale(double);
		void setPos(int, int);
		sf::Texture getTexture();
		sf::Sprite getSprite();
		void autoMove();
		void moveAwayFromChar(int, int);
		void moveTowardChar(int, int);
		bool mouseOver(sf::Sprite&, sf::Texture&, sf::Texture&);
		void speak(sf::String, sf::String, Textbox&);
};

#endif
