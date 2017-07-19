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
		SpriteManager menuBackground;
		ClickButton backButton;
		int stateBefore;

		sf::Font font;
		sf::Text title;

		//Characters
		std::vector<std::shared_ptr<ClickButton>> characterButtons;
		CharacterCards characterCard;
		bool charSelected;

		//Battle

		//Save
		//TODO Save in another "currentState"
	public:
		//General
		MapMenu();
		void setTitle(int);
		void checkForBackButton(int&, sf::RenderWindow& win);
		void updatePosition(sf::View view);
		void drawBack(sf::RenderWindow&);
		void drawBackground(sf::RenderWindow&);
		
		//Characters
		void setupChar(std::vector<std::shared_ptr<Character>>&, std::vector<int>);
		void showCharacterCard(std::shared_ptr<Character>&, int, std::vector<int>);
		void checkForCharacterButton(std::vector<std::shared_ptr<Character>>&,
					     std::vector<int>, sf::RenderWindow&);
		void checkForPartyButton(std::vector<int>&, int&, bool&, sf::RenderWindow&);
		void updateCharPosition(std::vector<std::shared_ptr<Character>>, sf::View);
		void drawAllChar(std::vector<std::shared_ptr<Character>>, sf::RenderWindow&);

		//Battle
		void drawAllBattle(sf::RenderWindow&);
		
		//Items
		void drawAllItem(sf::RenderWindow&);
		
		//Save
		void drawAllSave(sf::RenderWindow&);
};

#endif
