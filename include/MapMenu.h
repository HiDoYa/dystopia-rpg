#include "ClickButton.h"
#include "Character.h"
#include "CharacterCards.h"
#include <memory>

#ifndef MAPMENU_H
#define MAPMENU_H

class MapMenu
{
	private:
		//TODO Manipulate this
		sf::Texture bgTexture;
		sf::RectangleShape bgSprite;

		//Characters
		std::vector<std::shared_ptr<ClickButton>> characterButtons;
		CharacterCards characterCard;
		bool charSelected;
		int charSelectedNum;

		//Skills

		//Battle Positions
	public:
		MapMenu();
		//Characters
		void setupChar(std::vector<std::shared_ptr<Character>>&);
		void showCharacterCard(std::vector<std::shared_ptr<Character>>&);


		//Skills
		
		
		//Battle Positions

		void drawAllChar(sf::RenderWindow&);
		void drawAllSkills(sf::RenderWindow&);
		void drawAllBattlePos(sf::RenderWindow&);
};

#endif
