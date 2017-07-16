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
	charButton.getRect()->setSize(sf::Vector2f(200, 50));
	charButton.getText()->setString("Characters");
	charButton.getText()->setCharacterSize(15);

	skillButton.getRect()->setSize(sf::Vector2f(200, 50));
	skillButton.getText()->setString("Battle");
	skillButton.getText()->setCharacterSize(15);

	battlePosButton.getRect()->setSize(sf::Vector2f(200, 50));
	battlePosButton.getText()->setString("Save");
	battlePosButton.getText()->setCharacterSize(15);

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
	skillButton.updatePositionMap(275, 700, view);
	battlePosButton.updatePositionMap(525, 700, view);
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
	bool skillBool = skillButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	bool battlePosBool = battlePosButton.mouseClickedInButton(menuSelected, menuDeselected, win);
	if(charBool)
	{
		menuOption = 0;
		return true;
	}
	else if(skillBool)
	{
		menuOption = 1;
		return true;
	}
	else if(battlePosBool)
	{
		menuOption = 2;
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
	skillButton.drawAll(win);
	battlePosButton.drawAll(win);
}
