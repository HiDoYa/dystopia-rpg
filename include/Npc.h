#include "Textbox.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		bool openBox;
		bool closeBox;
		int textNum;
		sf::Clock clk;
		sf::Time tme;
		std::vector<std::string> sVec;
		
		//Stores whether player is next to npc
		bool colliding;
	public:
		Npc(int, int, sf::String);
		void setTexture(sf::String);
		void setPosition(int, int);
		sf::Sprite getSprite();
		void speak(sf::String, sf::String, Textbox&);
		void collision(Player&);
};

#endif

