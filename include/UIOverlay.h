#include "ClickButton.h"
#include "Character.h"
#include "OverlayCharDisplay.h"

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

		//Currently In Party
		sf::Text inParty;
		std::vector<std::shared_ptr<OverlayCharDisplay>> partyCards;

		//Level indicator
		sf::Text levelText;

		//Currency and other data
		sf::Text currencyText;

		//Button
		ClickButton charButton;
		ClickButton skillButton;
		ClickButton itemButton;
		ClickButton battlePosButton;
		sf::Color menuSelected;
		sf::Color menuDeselected;


	public:
		UIOverlay();

		void setPartyMember(std::vector<int>, std::vector<std::shared_ptr<Character>>);

		//Mutators
		void setPosition(sf::View);
		void setCurrency(int);
		void setLevel(int);

		//Etc
		bool checkForMapMenu(int&, sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);
};

#endif
