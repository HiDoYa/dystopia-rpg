#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//TODO
	bgTexture.loadFromFile("test");
	bgSprite.setTexture(bgTexture);

	for(int i = 0; i < 5; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr.push_back(menuChoices);
		menuChoices[i]->getRect()->setSize(sf::Vector2f(200, 50));
	}

	menuChoices[0]->getRect()->setPosition(sf::Vector2f(200, 50));
	menuChoices[1]->getRect()->setPosition(sf::Vector2f(200, 50));
	menuChoices[2]->getRect()->setPosition(sf::Vector2f(200, 50));
	menuChoices[3]->getRect()->setPosition(sf::Vector2f(200, 50));
	menuChoices[4]->getRect()->setPosition(sf::Vector2f(200, 50));

	menuChoices[0]->getText()->setString("Characters");
	menuChoices[1]->getText()->setString("Items");
	menuChoices[2]->getText()->setString("Skills");
	menuChoices[3]->getText()->setString("Battle Positions");
	menuChoices[4]->getText()->setString("Back");
}

void MapMenu::drawAll(sf::RenderWindow& win)
{
	win.draw(bgSprite);

	for(int i = 0; i < menuChoices.size(); i++)
	{
		menuChoices[i]->drawAll(win);
	}
}
