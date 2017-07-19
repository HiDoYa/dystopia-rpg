#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//Menu background
	menuBackground.setTextureSprite("images/ui/mapMenu.png");
	charSelected = false;

	//Setup back button
	backButton.getRect()->setSize(sf::Vector2f(150, 50));
	backButton.getText()->setString("Back");
	backButton.getText()->setCharacterSize(15);

	//Title
	font.loadFromFile("font/Ubuntu.ttf");
	title.setFont(font);
	title.setCharacterSize(25);
	title.setColor(sf::Color::Black);
}

void MapMenu::setTitle(int menuOption)
{
	switch(menuOption)
	{
		case 0:
			title.setString("Characters");
			break;
		case 1:
			title.setString("Battle");
			break;
		case 2:
			title.setString("Items");
			break;
		case 3:
			title.setString("Save");
			break;
	}
}

void MapMenu::checkForBackButton(int& currentState, sf::RenderWindow& win)
{
	if(backButton.mouseClickedInButton(sf::Color::Red, sf::Color::Black, win))
	{
		charSelected = false;
		currentState = 1;
	}
}

void MapMenu::updatePosition(sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	backButton.updatePositionMap(825, 700, view);
	menuBackground.setPosition(0 + viewX, 0 + viewY);
	title.setPosition(180 + viewX, 90 + viewY);
}

void MapMenu::drawBack(sf::RenderWindow& win)
{
	backButton.drawAll(win);
	win.draw(title);
}

void MapMenu::drawBackground(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}

//******** CHARACTERS *********
void MapMenu::setupChar(std::vector<std::shared_ptr<Character>>& ally, std::vector<int> allyFound)
{
	charSelected = false;
	for(int i = 0; i < allyFound.size(); i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		characterButtons.push_back(tempPtr);
		characterButtons[i]->getRect()->setSize(sf::Vector2f(300, 120));
		characterButtons[i]->getText()->setString(ally[allyFound[i]]->getName());
		characterButtons[i]->getText()->setCharacterSize(20);
		characterButtons[i]->getText()->setColor(sf::Color::Black);
	}
}

void MapMenu::showCharacterCard(std::shared_ptr<Character>& allySingular, int indexInAlly,
				std::vector<int> allyInParty)
{
	characterCard.setupCard(*allySingular, indexInAlly, allyInParty);
}

void MapMenu::checkForCharacterButton(std::vector<std::shared_ptr<Character>>& ally,
				      std::vector<int> allyInParty, sf::RenderWindow& win)
{
	if(!charSelected)
	{
		for(int i = 0; i < characterButtons.size(); i++)
		{
			if(characterButtons[i]->mouseClickedInButton(sf::Color::Red, sf::Color::White, win))
			{
				charSelected = true;
				showCharacterCard(ally[i], i, allyInParty);
				break;
			}
		}
	}
}

void MapMenu::checkForPartyButton(std::vector<int>& allyInParty, int& currentState, bool& mapMenuLoaded, sf::RenderWindow& win)
{
	characterCard.checkForButton(allyInParty, currentState, mapMenuLoaded, win);
}

void MapMenu::updateCharPosition(std::vector<std::shared_ptr<Character>> ally, sf::View view)
{
	for(int i = 0; i < characterButtons.size(); i++)
	{
		characterButtons[i]->updatePositionMap(200, 150 * (i + 1), view);
	}
	characterCard.updatePosition(ally, view);
}

void MapMenu::drawAllChar(std::vector<std::shared_ptr<Character>> ally, sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);

	if(charSelected)
	{
		characterCard.drawAll(ally, win);
	}
	else
	{
		for(int i = 0; i < characterButtons.size(); i++)
		{
			characterButtons[i]->drawAll(win);
		}
	}
}

//******** BATTLE *********
void MapMenu::drawAllBattle(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}

//******** ITEMS *********
void MapMenu::drawAllItem(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}

//******** SAVE *********
void MapMenu::drawAllSave(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}
