#include "ClickButton.h"
#include "Character.h"
#include <memory>

#ifndef OVERLAYCHARDISPLAY_H
#define OVERLAYCharDISPLAY_H

class OverlayCharDisplay
{
	private:
		sf::Font font;
		sf::Text name;
		sf::Text level;

		StatBar hp;
		StatBar mana;

		sf::RectangleShape cardWrap;
	public:
		//Run everytime party is changed (after battle, after removal of character)
		void setupDisplay(std::shared_ptr<Character>);
		void updatePosition(sf::View);
		void drawAll(sf::RenderWindow&);
};

#endif
