#include "ClickButton.h"
#include <memory>

#ifndef MAPMENU_H
#define MAPMENU_H

class MapMenu
{
	private:
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		std::vector<std::shared_ptr<ClickButton>> menuChoices;
		std::vector<std::shared_ptr<sf::RectangleShape>> characterCards;
	public:
		MapMenu();
		void drawAll(sf::RenderWindow&);
};

#endif
