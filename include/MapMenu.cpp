#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//TODO
	bgTexture.loadFromFile("test");
	bgSprite.setTexture(&bgTexture);
	charSelected = false;
}

void MapMenu::setupChar(std::vector<std::shared_ptr<Character>>& ally)
{
	charSelected = false;
	for(int i = 0; i < ally.size(); i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		characterButtons.push_back(tempPtr);
		characterButtons[i]->getRect()->setSize(sf::Vector2f(200, 50));
		characterButtons[i]->getRect()->setPosition(sf::Vector2f(200, 50 * i));
		characterButtons[i]->getText()->setString(ally[i]->getName());
	}
}

void MapMenu::showCharacterCard(std::vector<std::shared_ptr<Character>>& ally)
{
	characterCard.setupCard(*(ally[charSelectedNum]));
}

void MapMenu::drawAllChar(sf::RenderWindow& win)
{
	win.draw(bgSprite);

	if(charSelected)
	{
		characterCard.drawAll(win);
	}
	else
	{
		for(int i = 0; i < characterButtons.size(); i++)
		{
			characterButtons[i]->drawAll(win);
		}
	}
}

void MapMenu::drawAllSkills(sf::RenderWindow& win)
{
}

void MapMenu::drawAllBattlePos(sf::RenderWindow& win)
{
}
