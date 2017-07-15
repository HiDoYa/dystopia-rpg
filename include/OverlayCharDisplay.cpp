#include <SFML/Graphics.hpp>
#include <iostream>

#include "OverlayCharDisplay.h"

OverlayCharDisplay::OverlayCharDisplay()
{
	font.loadFromFile("font/Ubuntu.ttf");
	name.setFont(font);
	level.setFont(font);

	name.setCharacterSize(13);
	level.setCharacterSize(15);

	hp.setLabelPos(1);
	mana.setLabelPos(1);

	cardWrap.setSize(sf::Vector2f(150, 50));
}

void OverlayCharDisplay::setupDisplay(std::shared_ptr<Character> currentAllyPtr)
{
	name.setString(currentAllyPtr->getName());
	level.setString(std::to_string(currentAllyPtr->getLevel()));
	hp.setStats(currentAllyPtr->getCurrentHp(), currentAllyPtr->getMaxHp(), "Health");
	mana.setStats(currentAllyPtr->getCurrentMana(), currentAllyPtr->getMaxMana(), "Mana");
}

void OverlayCharDisplay::updatePosition(sf::Vector2f pos, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	cardWrap.setPosition(sf::Vector2f(pos.x + viewX, pos.y + viewY));
}

void OverlayCharDisplay::drawAll(sf::RenderWindow& win)
{
	win.draw(cardWrap);
	win.draw(name);
	win.draw(level);
	hp.drawAll(win);
	mana.drawAll(win);
}
