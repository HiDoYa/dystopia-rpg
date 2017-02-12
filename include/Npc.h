#include "Textbox.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		//Texture and sprite of npc
		sf::Texture texture;
		sf::Sprite sprite;
		
		//Textbox management
		bool openBox;
		bool closeBox;

		//Used to store the text that the character will speak (separated into different lines). Textnum stores number for the current sVec element that is being displayed
		std::vector<std::string> sVec;
		int textNum;

		//Stores whether npc is speaking or not
		bool speaking;
		
		//Stores whether player is next to npc
		bool colliding;
	public:
		Npc(int, int, sf::String);
		void setTexture(sf::String);
		void setPosition(int, int);
		sf::Sprite getSprite();
		void speak(sf::String, sf::String, Textbox&);
		bool getSpeaking();
		void collision(Player&);
};

#endif

