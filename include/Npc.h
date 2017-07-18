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

		int npcExistNum;
		bool npcExistCond;
	public:
		Npc();
		void npcExistCondition(int, bool);
		bool npcExists(std::vector<bool>);
		void speak(std::vector<bool>&, std::vector<int>&, std::vector<int>&, Textbox&, MapPlayer&, sf::RenderWindow&);
		void giveToPlayer(std::vector<int>&, std::vector<int>&, int, int);
		void ascendSort(std::vector<int>&);
		void removeDup(std::vector<int>&);
		void changeStateFlag(std::vector<bool>&, int, int);
		void collision(MapPlayer&);

		//****** MUTATORS **********
		void setName(std::string);

		//***** ACCESSORS ********
		bool getSpeaking();
		std::string getName();
};

#endif

