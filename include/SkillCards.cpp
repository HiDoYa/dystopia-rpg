#include <SFML/Graphics.hpp>
#include "SkillCards.h"
#include <iostream>

SkillCards::SkillCards()
{
	font.loadFromFile("font/Ubuntu.ttf");

	//set text
	name.setFont(font);
	description.setFont(font);
	name.setCharacterSize(15);
	description.setCharacterSize(12);

	//Set shapes
	icon.setRadius(8);
	skillRating.setSize(sf::Vector2f(200, 70));
}

void SkillCards::setupCard(Skill skill)
{
	name.setString(skill.getName());
	//TODO description.setString();
	//TODO load icon and skillRating
}

void SkillCards::setPosition(sf::Vector2f pos, sf::View view)
{
	name.setPosition();
}

void SkillCards::drawAll(sf::RenderWindow& win)
{
	win.draw(cardBackground);
	win.draw(icon);
	skillRating.drawAll(win);
	win.draw(name);
	win.draw(description);
}
