#include <SFML/Graphics.hpp>
#include <iostream>

#include "MapMenu.h"

MapMenu::MapMenu()
{
	//Menu background
	menuBackground.setTextureSprite("images/ui/mapMenu.png");
	charSelected = false;

	//Setup back button
	backButton.getRect()->setSize(sf::Vector2f(175, 50));
	backButton.getText()->setString("Back");
	backButton.getText()->setCharacterSize(15);

	//Title
	font.loadFromFile("font/Ubuntu.ttf");
	title.setFont(font);
	title.setCharacterSize(25);
	title.setColor(sf::Color::Black);

	//Battle
	selectedCol = sf::Color::Red;
	deselectedCol = sf::Color::Black;
	deselectedColW = sf::Color::White;

	instructions.setFont(font);
	instructions.setCharacterSize(10);
	instructions.setColor(sf::Color::Black);
	instructions.setString("Click a player and click on an empty grid to change the character's default starting position.");

	for(int i = 0; i < 6; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr->getRect()->setSize(sf::Vector2f(200, 100));
		tempPtr->getRect()->setFillColor(sf::Color::White);
		tempPtr->getRect()->setOutlineColor(sf::Color::Black);
		tempPtr->getRect()->setOutlineThickness(2);
		grid.push_back(tempPtr);
	}

	currentToggle = -1;
	charNumberGrid = {-1, -1, -1, -1, -1, -1};
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
	if(backButton.mouseClickedInButton(selectedCol, deselectedCol, win))
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
	characterCard.setDisplaySkills(false);
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
				std::vector<int> allyInParty, 
				std::vector<std::shared_ptr<Skill>> skillList, 
				std::vector<int> unlockedSkills)
{
	characterCard.setupCard(*allySingular, indexInAlly, allyInParty, skillList, unlockedSkills);
}

void MapMenu::checkForCharacterButton(std::vector<std::shared_ptr<Character>>& ally,
				      std::vector<int> allyInParty, 
				      std::vector<std::shared_ptr<Skill>> skillList,
				      std::vector<int> unlockedSkills, sf::RenderWindow& win)
{
	if(!charSelected)
	{
		for(int i = 0; i < characterButtons.size(); i++)
		{
			if(characterButtons[i]->mouseClickedInButton(sf::Color::Red, sf::Color::White, win))
			{
				charSelected = true;
				showCharacterCard(ally[i], i, allyInParty, skillList, unlockedSkills);
				break;
			}
		}
	}
}

void MapMenu::checkForPartyButton(std::vector<int>& allyInParty, std::vector<std::shared_ptr<Character>>& ally, int& currentState, bool& mapMenuLoaded, sf::RenderWindow& win)
{
	characterCard.checkForButton(allyInParty, ally, currentState, mapMenuLoaded, win);
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
void MapMenu::setupBattle(std::vector<std::shared_ptr<Character>>& ally, std::vector<int> allyInParty)
{
	currentToggle = -1;
	hasNotClicked = false;
	for(int i = 0; i < allyInParty.size(); i++)
	{
		int indexNum = ally[allyInParty[i]]->getBattlePos();
		charNumberGrid[indexNum] = allyInParty[i];
	}
}

void MapMenu::checkForClicked()
{
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		hasNotClicked = true;
	}
}

void MapMenu::checkForBattleButton(std::vector<std::shared_ptr<Character>>& ally, std::vector<int> allyInParty, sf::RenderWindow& win)
{
	checkForClicked();

	if(currentToggle == -1)
	{
		for(int i = 0 ; i < 6; i++)
		{
			if(charNumberGrid[i] != -1 && 
			   grid[i]->mouseClickedInButton(selectedCol, deselectedColW, win))
			{
				hasNotClicked = false;
				currentToggle = i;
				break;
			}
		}
	}
	else
	{
		for(int i = 0 ; i < 6; i++)
		{
			if(charNumberGrid[i] == -1 && 
			   grid[i]->mouseClickedInButton(selectedCol, deselectedColW, win))
			{
				hasNotClicked = false;
				charNumberGrid[i] = charNumberGrid[currentToggle];
				//The old location is now empty
				charNumberGrid[currentToggle] = -1;

				ally[charNumberGrid[i]]->setBattlePos(i);
				currentToggle = -1;

				//Reset all colors
				for(int j = 0; j < 6; j++)
				{
					grid[j]->getRect()->setFillColor(deselectedColW);
				}
				break;
			}
		}
	}
}

void MapMenu::updateBattlePos(std::vector<std::shared_ptr<Character>>& ally, std::vector<int> allyInParty, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	instructions.setPosition(sf::Vector2f(150 + viewX, 150 + viewY));

	std::vector<sf::Vector2f> gridPos = 
	{
		sf::Vector2f(330, 200),
		sf::Vector2f(330, 350),
		sf::Vector2f(330, 500),
		sf::Vector2f(600, 200),
		sf::Vector2f(600, 350),
		sf::Vector2f(600, 500),
	};

	for(int i = 0; i < 6; i++)
	{
		grid[i]->updatePositionMap(gridPos[i].x, gridPos[i].y, view);
	}

	for(int i = 0; i < allyInParty.size(); i++)
	{
		int bPos = ally[allyInParty[i]]->getBattlePos();
		ally[allyInParty[i]]->setPosition(gridPos[bPos].x + 68 + viewX, gridPos[bPos].y + 18 + viewY);
	}
}

void MapMenu::drawAllBattle(std::vector<std::shared_ptr<Character>>& ally, std::vector<int> allyInParty, sf::RenderWindow& win)
{
	menuBackground.drawSprite(win);

	win.draw(instructions);

	for(int i = 0; i < 6; i++)
	{
		grid[i]->drawAll(win);
	}

	for(int i = 0; i < allyInParty.size(); i++)
	{
		ally[allyInParty[i]]->setScale(1, 1);
		ally[allyInParty[i]]->drawSprite(win);
	}
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
