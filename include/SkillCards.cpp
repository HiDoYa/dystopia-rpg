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
	iconTexture.loadFromFile("images/ally/skillIcons.png");
	icon.setTexture(&iconTexture);
}

void SkillCards::setupCard(Skill skill, int id)
{
	skillId = id;
	std::string textHover = skill.getName() + '\n' + skill.getDescription();
	equip.getHoverText()->setString(textHover);

	switch(skill.getPrimaryType())
	{
		case 0:
			icon.setTextureRect(sf::IntRect(0, 0, 64, 64));
			break;
		case 1:
			icon.setTextureRect(sf::IntRect(64, 0, 64, 64));
			break;
		case 2:
			icon.setTextureRect(sf::IntRect(128, 0, 64, 64));
			break;
		case 3:
			icon.setTextureRect(sf::IntRect(192, 0, 64, 64));
			break;
	}
}

void SkillCards::setupCard(Item item, int id)
{
	skillId = id;
	std::string textHover = item.getName();
	equip.getHoverText()->setString(textHover);
	//TODO FINISH
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

int SkillCards::getSkillId()
{
	return skillId;
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
