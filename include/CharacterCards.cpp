#include <SFML/Graphics.hpp>
#include "CharacterCards.h"
#include <iostream>

CharacterCards::CharacterCards()
{
	font.loadFromFile("font/Ubuntu.ttf");

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
}

void CharacterCards::setupText(sf::Text& txt, sf::Font& font, int charSize)
{
	txt.setCharacterSize(charSize);
	txt.setFont(font);
	txt.setColor(sf::Color::Black);
}

void CharacterCards::updatePosition(sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	hp.setPosition(sf::Vector2f(180 + viewX, 450 + viewY));
	mana.setPosition(sf::Vector2f(180 + viewX, 580 + viewY));

	name.setPosition(660 + viewX, 150 + viewY);
	desc.setPosition(180 + viewX, 150 + viewY);
	str.setPosition(180 + viewX, 200 + viewY);
	def.setPosition(180 + viewX, 260 + viewY);
	agi.setPosition(180 + viewX, 320 + viewY);
}

void CharacterCards::setupCard(Character chr)
{
	name.setString(chr.getName());

	//TODO Description for each character (fileReader)

	str.setString("Strength:  " + std::to_string(chr.getStrength()));
	def.setString("Defense:  " + std::to_string(chr.getDefense()));
	agi.setString("Agility:  " + std::to_string(chr.getAgility()));
	
	hp.setStats(chr.getCurrentHp(), chr.getMaxHp(), "Health");
	mana.setStats(chr.getCurrentMana(), chr.getMaxMana(), "Mana");
}

void CharacterCards::drawAll(sf::RenderWindow& win)
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
}
