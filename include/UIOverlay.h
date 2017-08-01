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

		//Currency and other data
		sf::Text currencyText;

		//Button
		ClickButton charButton;
		ClickButton battleButton;
		ClickButton questButton;
		ClickButton saveButton;
		sf::Color menuSelected;
		sf::Color menuDeselected;


	public:
		UIOverlay();

		void setPartyMember(std::vector<int>, std::vector<std::shared_ptr<Character>>);

		//Mutators
		void setPosition(sf::View);
		void setCurrency(int);

		//Etc
		bool checkForMapMenu(int&, sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);
};

#endif
