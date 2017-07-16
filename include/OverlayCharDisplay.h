#include "ClickButton.h"
#include "Character.h"
#include "StatBar.h"
#include <memory>

#ifndef OVERLAYCHARDISPLAY_H
#define OVERLAYCHARDISPLAY_H

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
		OverlayCharDisplay();
		//Run everytime party is changed (after battle, after removal of character)
		void setupDisplay(std::shared_ptr<Character>);
		void updatePosition(sf::Vector2f, sf::View);
		void drawAll(sf::RenderWindow&);
};

#endif
