#include <SFML/Graphics.hpp>
#include "CharacterCards.h"
#include <iostream>

CharacterCards::CharacterCards()
{
	font.loadFromFile("font/Ubuntu.ttf");

	setupText(name, font);
	setupText(desc, font);
	setupText(str, font);
	setupText(def, font);
	setupText(agi, font);

	hp.setLabelUse(true);
	hp.setLabelPos(0);
	hp.setLabelSize(25);
	hp.setMaxSize(sf::Vector2f(200, 50));
	hp.setPositiion(sf::Vecto2f(100, 400));

	mana.setLabelUse(true);
	mana.setLabelPos(0);
	mana.setLabelSize(25);
	mana.setMaxSize(sf::Vector2f(200, 50));
	mana.setPositiion(sf::Vecto2f(100, 400));
}

void CharacterCards::setupText(sf::Text txt, sf::Font font, int charSize)
{
	txt.setCharacterSize(charSize);
	txt.setFont(font);
}

void CharacterCards::setupCard(Character chr)
{
	name.setString(chr.getName());

	//TODO Description for each character (fileReader)

	str.setString("Strength:  " + std::to_string(chr.getStrength()));
	def.setString("Defense:  " + std::to_string(chr.getDefense()));
	agi.setString("Agility:  " + std::to_string(chr.getAgility()));
	
	hp.setStats(chr.getCurrentHp(), chr.getMaxHp());
	mana.setStats(chr.getCurrentMana(), chr.getMaxMana());
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
