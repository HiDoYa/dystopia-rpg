#include <SFML/Audio.hpp>

#include "SpriteManager.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu: public SpriteManager
{
	private:
		int currentlySelected;
		int numButtons;

		sf::Font font;
		
		sf::Text start;
		sf::Text load;
		sf::Text exit;

		sf::RectangleShape startButton;
		sf::RectangleShape loadButton;
		sf::RectangleShape exitButton;

		sf::Color unselected;
		sf::Color selected;

		sf::Music scrollingMusic;
		sf::Music choosingMusic;

		bool wNotPressed;
		bool sNotPressed;
	public:
		MainMenu();
		void scroll();
		void currentlySelectedIndicate();
		int selection();
		void drawAll(sf::RenderWindow&);
};

#endif
