#include <SFML/Audio.hpp>

#include "ClickButton.h"
#include "SpriteManager.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu: public SpriteManager
{
	private:
		ClickButton startButton;
		ClickButton loadButton;
		ClickButton exitButton;

		sf::Color unselected;
		sf::Color selected;

		sf::Music scrollingMusic;
		sf::Music choosingMusic;
	public:
		MainMenu();
		int clickCheck(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);
};

#endif
