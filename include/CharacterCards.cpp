#include <SFML/Graphics.hpp>
#include "CharacterCards.h"
#include <iostream>

CharacterCards::CharacterCards()
{
	font.loadFromFile("font/Ubuntu.ttf");
	existInParty = false;
	allyIndex = -1;

	background.setTextureSprite("images/ui/characterCard.png");

	setupText(name, font, 27);
	setupText(desc, font, 20);
	setupText(str, font, 20);
	setupText(def, font, 20);
	setupText(agi, font, 20);

	hp.setLabelPos(0);
	hp.setLabelSize(13);
	hp.setMaxSize(sf::Vector2f(350, 50));
	hp.getCurrentRect()->setFillColor(sf::Color::Red);
	hp.getLabel()->setColor(sf::Color::Black);

	mana.setLabelPos(0);
	mana.setLabelSize(13);
	mana.setMaxSize(sf::Vector2f(350, 50));
	mana.getCurrentRect()->setFillColor(sf::Color::Yellow);
	mana.getLabel()->setColor(sf::Color::Black);

	partyButton.getRect()->setSize(sf::Vector2f(300, 80));
	partyButton.getText()->setCharacterSize(15);
	partyButton.getText()->setColor(sf::Color::Black);

	for(int i = 0; i < 3; i++)
	{
		skillButton.push_back(std::shared_ptr<ClickButton>(new ClickButton));
		skillButton[i]->setType(1);
		skillButton[i]->getCirc()->setRadius(15);
	}
}

void CharacterCards::setupText(sf::Text& txt, sf::Font& font, int charSize)
{
	txt.setCharacterSize(charSize);
	txt.setFont(font);
	txt.setColor(sf::Color::Black);
}

void CharacterCards::updatePosition(std::vector<std::shared_ptr<Character>> ally, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	hp.setPosition(sf::Vector2f(180 + viewX, 450 + viewY));
	mana.setPosition(sf::Vector2f(180 + viewX, 580 + viewY));

	name.setPosition(180 + viewX, 150 + viewY);
	desc.setPosition(180 + viewX, 150 + viewY);
	str.setPosition(180 + viewX, 220 + viewY);
	def.setPosition(180 + viewX, 280 + viewY);
	agi.setPosition(180 + viewX, 340 + viewY);

	if(allyIndex != -1)
	{
		ally[allyIndex]->setPosition(570 + viewX, 450 + viewY);
		ally[allyIndex]->setScale(2.5, 2.5);
	}

	partyButton.updatePositionMap(700, 100, view);
}

void CharacterCards::setupCard(Character chr, int indexInAlly, std::vector<int> allyInParty)
{
	name.setString(chr.getName());

	//TODO Description for each character (fileReader)

	str.setString("Strength:  " + std::to_string(chr.getStrength()));
	def.setString("Defense:  " + std::to_string(chr.getDefense()));
	agi.setString("Agility:  " + std::to_string(chr.getAgility()));
	
	hp.setStats(chr.getCurrentHp(), chr.getMaxHp(), "Health");
	mana.setStats(chr.getCurrentMana(), chr.getMaxMana(), "Mana");

	//Checks whether the ally is already in the party
	existInParty = false;
	allyIndex = indexInAlly;
	for(int i = 0; i < allyInParty.size(); i++)
	{
		if(allyInParty[i] == indexInAlly)
		{
			existInParty = true;
		}
	}

	if(allyIndex == 0)
	{
		partyButton.getText()->setString("Cannot Remove");
	}
	else if(existInParty)
	{
		partyButton.getText()->setString("Remove from Party");
	}
	else if(allyInParty.size() == 3)
	{
		partyButton.getText()->setString("Party is full.");
	}
	else if(!existInParty)
	{
		partyButton.getText()->setString("Add to Party");
	}
}

void CharacterCards::checkForButton(std::vector<int>& allyInParty, int& currentState, bool& mapMenuLoaded, sf::RenderWindow& win)
{
	bool pressed = partyButton.mouseClickedInButton(sf::Color::Red, sf::Color::White, win);

	if(pressed && allyInParty.size() < 3 && allyIndex != 0)
	{
		if(existInParty)
		{
			for(int i = 0; i < allyInParty.size(); i++)
			{
				if(allyInParty[i] == allyIndex)
				{
					allyInParty.erase(allyInParty.begin() + i);
					break;
				}
			}
		}
		else
		{
			allyInParty.push_back(allyIndex);
		}
		//Goes back to the map
		currentState = 1;
		mapMenuLoaded = false;
	}
}

void CharacterCards::drawAll(std::vector<std::shared_ptr<Character>> ally, sf::RenderWindow& win)
{
	background.drawSprite(win);

	hp.drawAll(win);
	mana.drawAll(win);
	image.drawSprite(win);

	win.draw(name);
	win.draw(desc);

	win.draw(str);
	win.draw(def);
	win.draw(agi);

	ally[allyIndex]->drawSprite(win);

	partyButton.drawAll(win);
}
