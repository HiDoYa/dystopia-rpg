#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//TODO
	bgTexture.loadFromFile("test");
	bgSprite.setTexture(bgTexture);
}

void MapMenu::setupChar(std::vector<std::shared_ptr<Character>>& ally)
{
	for(int i = 0; i < ally.size(); i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr.push_back(characterButtons);
		characterButtons[i]->getRect()->setSize(sf::Vector2f(200, 50));
		characterButtons[i]->getRect()->setPosition(sf::Vector2f(200, 50));
		characterButtons[i]->getText()->setString(ally[i]->getName());
	}
}

void MapMenu::drawAll(sf::RenderWindow& win)
{
	win.draw(bgSprite);

	for(int i = 0; i < characterButtons.size(); i++)
	{
		characterButtons[i]->drawAll(win);
	}
}
