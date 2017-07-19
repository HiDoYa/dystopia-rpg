#include <SFML/Graphics.hpp>
#include <iostream>

#include "UIOverlay.h"

UIOverlay::UIOverlay()
{
	//TODO Mainwrapper
	mainWrapperTexture.loadFromFile("images/ui/mapUi.png");
	mainWrapperSprite.setTexture(mainWrapperTexture);

	//Font
	font.loadFromFile("font/Ubuntu.ttf");
	currencyText.setCharacterSize(15);

	//Currency Text
	currencyText.setFont(font);
	
	//level Text
	levelText.setFont(font);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(25);

	//Button
	charButton.getRect()->setSize(sf::Vector2f(150, 50));
	charButton.getText()->setString("Characters");
	charButton.getText()->setCharacterSize(15);

	battleButton.getRect()->setSize(sf::Vector2f(150, 50));
	battleButton.getText()->setString("Battle");
	battleButton.getText()->setCharacterSize(15);

	itemButton.getRect()->setSize(sf::Vector2f(150, 50));
	itemButton.getText()->setString("Items");
	itemButton.getText()->setCharacterSize(15);

	saveButton.getRect()->setSize(sf::Vector2f(150, 50));
	saveButton.getText()->setString("Save");
	saveButton.getText()->setCharacterSize(15);

	menuSelected = sf::Color::Red;
	menuDeselected = sf::Color::Black;

	inParty.setFont(font);
	inParty.setCharacterSize(10);
	inParty.setColor(sf::Color::Black);
	inParty.setString("Party Members");
}

void UIOverlay::setPartyMember(std::vector<int> partyMembers,
				std::vector<std::shared_ptr<Character>> ally)
{
	partyCards.clear();
	for(int i = 0; i < partyMembers.size(); i++)
	{
		std::shared_ptr<Character>currentAllyPtr = ally[partyMembers[i]];
		partyCards.push_back(std::shared_ptr<OverlayCharDisplay>(new OverlayCharDisplay));
		partyCards[i]->setupDisplay(currentAllyPtr);
	}
}

//********** MUTATORS ************** 

void UIOverlay::setPosition(sf::View view)
{
	int x = view.getCenter().x - (view.getSize().x / 2);
	int y = view.getCenter().y - (view.getSize().y / 2);
	mainWrapperSprite.setPosition(x, y);

	currencyText.setPosition(sf::Vector2f(x + 900, y + 30));

	levelText.setPosition(sf::Vector2f(x + 33, y + 40));

	inParty.setPosition(sf::Vector2f(x + 10, y + 20));
	for(int i = 0; i < partyCards.size(); i++)
	{
		partyCards[i]->updatePosition(sf::Vector2f(20, 130 * i + 50), view);
	}

	charButton.updatePositionMap(25, 700, view);
	battleButton.updatePositionMap(225, 700, view);
	itemButton.updatePositionMap(425, 700, view);
	saveButton.updatePositionMap(625, 700, view);
}

void UIOverlay::setCurrency(int cur)
{
	currencyText.setString("Gold: " + std::to_string(cur));
}

void UIOverlay::setLevel(int lvl)
{
	levelText.setString(std::to_string(lvl));
}

//********* ETC ***********

bool UIOverlay::checkForMapMenu(int& menuOption, sf::RenderWindow& win)
{
	bool charBool = charButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	bool battleBool = battleButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	bool itemBool = itemButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	bool saveBool = saveButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	if(charBool)
	{
		menuOption = 0;
		return true;
	}
	else if(battleBool)
	{
		menuOption = 1;
		return true;
	}
	else if(itemBool)
	{
		menuOption = 2;
		return true;
	}
	else if(saveBool)
	{
		menuOption = 3;
		return true;
	}
	return false;
}

void UIOverlay::drawAll(sf::RenderWindow& win)
{
	win.draw(mainWrapperSprite);

	win.draw(levelText);

	win.draw(currencyText);

	for(int i = 0; i < partyCards.size(); i++)
	{
		partyCards[i]->drawAll(win);
	}

	win.draw(inParty);

	charButton.drawAll(win);
	battleButton.drawAll(win);
	itemButton.drawAll(win);
	saveButton.drawAll(win);
}
