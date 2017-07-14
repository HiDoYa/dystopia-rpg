#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//Menu background
	menuBackground.setTextureSprite("images/ui/mapMenu.png");
	charSelected = false;

	//Setup back button
	backButton.getRect()->setSize(sf::Vector2f(200, 50));
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
			title.setString("Skills");
			break;
		case 2:
			title.setString("Battle");
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

	backButton.updatePositionMap(775, 700, view);
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
void MapMenu::setupChar(std::vector<std::shared_ptr<Character>>& ally)
{
	charSelected = false;
	for(int i = 0; i < ally.size(); i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		characterButtons.push_back(tempPtr);
		characterButtons[i]->getRect()->setSize(sf::Vector2f(300, 120));
		characterButtons[i]->getText()->setString(ally[i]->getName());
		characterButtons[i]->getText()->setCharacterSize(20);
		characterButtons[i]->getText()->setColor(sf::Color::Black);
	}
}

void MapMenu::showCharacterCard(std::shared_ptr<Character>& allySingular)
{
	characterCard.setupCard(*allySingular);
}

void MapMenu::checkForCharacterButton(std::vector<std::shared_ptr<Character>>& ally,
				      sf::RenderWindow& win)
{
	if(!charSelected)
	{
		for(int i = 0; i < characterButtons.size(); i++)
		{
			if(characterButtons[i]->mouseClickedInButton(sf::Color::Red, sf::Color::White, win))
			{
				charSelected = true;
				showCharacterCard(ally[i]);
				break;
			}
		}
	}
}

void MapMenu::updateCharacterCardPosition(sf::View view)
{
	for(int i = 0; i < characterButtons.size(); i++)
	{
		characterButtons[i]->updatePositionMap(200, 150 * (i + 1), view);
	}
	characterCard.updatePosition(view);
}

void MapMenu::drawAllChar(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);

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

//******** SKILLS *********
void MapMenu::drawAllSkills(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}

//******** BATTLEPOS *********
void MapMenu::drawAllBattlePos(sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);
}
