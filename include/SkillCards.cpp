#include <SFML/Graphics.hpp>
#include "SkillCards.h"
#include <iostream>

SkillCards::SkillCards()
{
	//Set shapes
	icon.setRadius(50);
	cardBackground.setSize(sf::Vector2f());

	//Set button
	equip.setType(0);
	equip.setHoverText(true);
	equip.getHoverText()->setCharacterSize(9);
	equip.getHoverText()->setColor(sf::Color::White);

	equip.getText()->setString("Equip");
	equip.getText()->setCharacterSize(10);
	equip.getText()->setColor(sf::Color::Black);
	equip.getRect()->setSize(sf::Vector2f(75, 40));

	//Icon
	iconTexture.loadFromFile("images/skillIcons.png");
	icon.setTexture(&iconTexture);
}

void SkillCards::setupCard(Skill skill, int id)
{
	std::string textHover = skill.getName() + '\n' + skill.getDescription();
	equip.getHoverText()->setString(textHover);

	icon.setTextureRect(sf::IntRect(id % 10, id / 10, 64, 64));

}

void SkillCards::setPosition(sf::Vector2f pos, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	cardBackground.setPosition(sf::Vector2f(pos.x + viewX, pos.y + viewY));
	icon.setPosition(sf::Vector2f(pos.x + 30 + viewX, pos.y + 10 + viewY));
	equip.updatePositionMap(pos.x, pos.y + 80, view);
	equip.setPositionHover(pos.x + 30, pos.y + 30, view);
}

bool SkillCards::selectSkill(sf::RenderWindow& win)
{
	if(equip.mouseClickedInButton(sf::Color::Red, sf::Color::White, win))
	{
		return true;
	}
	return false;
}

void SkillCards::drawAll(sf::RenderWindow& win)
{
	win.draw(cardBackground);
	win.draw(icon);
	equip.drawAll(win);
}
