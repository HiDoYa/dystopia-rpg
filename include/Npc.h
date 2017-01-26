#include <SFML/Graphics.hpp>

#ifndef NPC_H
#define NPC_H

class Npc
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		Npc(int, int);
		void autoMove();
		void moveAwayFromChar(int, int);
		void moveTowardChar(int, int);
		void setPos(int, int);
		void speak(sf::String);
}

#endif
