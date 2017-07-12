#include "ClickButton.h"
#include <memory>

#ifndef MAPMENU_H
#define MAPMENU_H

class MapMenu
{
	private:
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		std::vector<std::shared_ptr<ClickButton>> characterButtons;

		//Characters
		std::vector<std::shared_ptr<sf::RectangleShape>> characterCards;

		//Skills

		//Battle Positions
	public:
		MapMenu();
		//Characters
		void setupChar(std::vector<std::-shared_ptr<Character>>&);


		//Skills
		
		
		//Battle Positions

		void drawAll(sf::RenderWindow&);
};

#endif
