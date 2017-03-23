#include "SpriteManage.h"

class Textbox;

#ifndef NPC_H
#define NPC_H

class Npc: public SpriteManage
{
	private:
		std::string name;
		//Stores whether npc is speaking or not
		bool speaking;
		
		//Stores whether player is next to npc
		bool colliding;
	public:
		Npc();
		void speak(sf::String, sf::String, Textbox&, Player&);
		void collision(Player&);

		//****** MUTATORS **********
		void setName(std::string);

		//***** ACCESSORS ********
		bool getSpeaking();
		std::string getName();
};

#endif

