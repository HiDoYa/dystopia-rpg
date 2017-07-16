#include <SFML/Graphics.hpp>
#include <iostream>

#include "OverlayCharDisplay.h"

OverlayCharDisplay::OverlayCharDisplay()
{
	font.loadFromFile("font/Ubuntu.ttf");
	name.setFont(font);
	level.setFont(font);

	name.setCharacterSize(8);
	level.setCharacterSize(9);
	hp.getLabel()->setCharacterSize(4);
	mana.getLabel()->setCharacterSize(4);

	hp.setMaxSize(sf::Vector2f(80, 14));
	mana.setMaxSize(sf::Vector2f(80, 14));

	hp.getCurrentRect()->setFillColor(sf::Color::Red);
	mana.getCurrentRect()->setFillColor(sf::Color::Yellow);

	hp.setLabelPos(2);
	mana.setLabelPos(2);

	name.setColor(sf::Color::Black);
	level.setColor(sf::Color::Black);
	hp.getLabel()->setColor(sf::Color::Black);
	mana.getLabel()->setColor(sf::Color::Black);

	cardWrap.setSize(sf::Vector2f(100, 110));
}

void OverlayCharDisplay::setupDisplay(std::shared_ptr<Character> currentAllyPtr)
{
	level.setString("Level : " + std::to_string(currentAllyPtr->getLevel()));
	name.setString(currentAllyPtr->getName());
	hp.setStats(currentAllyPtr->getCurrentHp(), currentAllyPtr->getMaxHp());
	mana.setStats(currentAllyPtr->getCurrentMana(), currentAllyPtr->getMaxMana());
}

void OverlayCharDisplay::updatePosition(sf::Vector2f pos, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	cardWrap.setPosition(sf::Vector2f(pos.x + viewX, pos.y + viewY));
	level.setPosition(sf::Vector2f(pos.x + viewX + 6, pos.y + viewY + 14));
	name.setPosition(sf::Vector2f(pos.x + viewX + 6, pos.y + viewY + 23));
	name.setPosition(sf::Vector2f(pos.x + viewX + 6, pos.y + viewY + 33));
	hp.setPosition(sf::Vector2f(pos.x + viewX + 6, pos.y + viewY + 58));
	mana.setPosition(sf::Vector2f(pos.x + viewX + 6, pos.y + viewY + 84));
}

void OverlayCharDisplay::drawAll(sf::RenderWindow& win)
{
	win.draw(cardWrap);
	win.draw(name);
	win.draw(level);
	hp.drawAll(win);
	mana.drawAll(win);
}
