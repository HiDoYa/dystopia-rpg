#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
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
		void speak(sf::String);
};

#endif
