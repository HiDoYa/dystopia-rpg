#include "Dialogue.h"
#include "MapPlayer.h"
#include "SpriteManager.h"

class Textbox;

#ifndef NPC_H
#define NPC_H

class Npc: public SpriteManager, public Dialogue
{
	private:
		std::string name;
		//Stores whether npc is speaking or not
		bool speaking;
		//Stores whether player is next to npc
		bool colliding;
	public:
		Npc();
		void speak(std::vector<bool>&, Textbox&, MapPlayer&, sf::RenderWindow&);
		void collision(MapPlayer&);

		//****** MUTATORS **********
		void setName(std::string);

		//***** ACCESSORS ********
		bool getSpeaking();
		std::string getName();
};

#endif

