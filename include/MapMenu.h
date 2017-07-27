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
		sf::Text instructions;
		sf::Color selectedCol;
		sf::Color deselectedCol;
		sf::Color deselectedColW;
		std::vector<std::shared_ptr<ClickButton>> grid;
		//Stores the character number if a character exists in the grid
		std::vector<int> charNumberGrid;
		//The index number in ALLY (not allyinparty, not battlepos)
		int currentToggle;
		bool hasNotClicked;

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
		void showCharacterCard(std::shared_ptr<Character>&, int, std::vector<int>, 
				std::vector<std::shared_ptr<Skill>>, std::vector<int>);
		void checkForCharacterButton(std::vector<std::shared_ptr<Character>>&,
					     std::vector<int>, std::vector<std::shared_ptr<Skill>>, 
					     std::vector<int>, sf::RenderWindow&);
		void checkForPartyButton(std::vector<int>&, 
				std::vector<std::shared_ptr<Character>>&, int&, bool&, 
				sf::RenderWindow&);
		void updateCharPosition(std::vector<std::shared_ptr<Character>>, sf::View);
		void drawAllChar(std::vector<std::shared_ptr<Character>>, sf::RenderWindow&);

		//Battle
		void setupBattle(std::vector<std::shared_ptr<Character>>&, std::vector<int>);
		void checkForClicked();
		void checkForBattleButton(std::vector<std::shared_ptr<Character>>&, std::vector<int>, sf::RenderWindow&);
		void updateBattlePos(std::vector<std::shared_ptr<Character>>&, std::vector<int>, sf::View);
		void drawAllBattle(std::vector<std::shared_ptr<Character>>&, std::vector<int>, sf::RenderWindow&);
		
		//Items
		void drawAllItem(sf::RenderWindow&);
		
		//Save
		void drawAllSave(sf::RenderWindow&);
};

#endif
