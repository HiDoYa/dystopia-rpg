#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	for(int i = 0; i < 5; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr.push_back(menuChoices);
		menuChoices[i]->getRect()->setSize(sf::Vector2f(200, 50));
	}

	menuChoices[0]->getRect()->setPosition(sf::Vector2f(200, 50));
}
