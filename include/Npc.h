#include <SFML/Graphics.hpp>

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		int posX;
		int posY;
	public:
		Npc(int, int);
		void autoMove();
		void moveAwayFromChar(int, int);
		void moveTowardChar(int, int);
		void setPosX(int);
		void setPosY(int);
		void speak(sf::String);
}

#endif
