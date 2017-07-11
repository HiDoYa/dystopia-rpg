#include "ClickButton.h"

#ifndef UIOVERLAY_H
#define UIOVERLAY_H

class UIOverlay
{
	private:
		//Font Used
		sf::Font font;

		//Mainwrapper
		sf::Texture mainWrapperTexture;
		sf::Sprite mainWrapperSprite;

		//Level indicator
		sf::CircleShape levelNumWrapper;
		sf::Text levelText;

		//Currency and other data
		sf::Text currencyText;

		//Button
		ClickButton menuOpen;
		sf::Color menuSelected;
		sf::Color menuDeselected;

	public:
		UIOverlay();

		//Mutators
		void setPosition(sf::View);
		void setCurrency(int);
		void setLevel(int);

		//Etc
		void checkForMapMenu(int&, sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);
};

#endif
