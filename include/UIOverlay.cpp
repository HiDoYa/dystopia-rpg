#include "UIOverlay.h"
#include <string>
#include <iostream>

UIOverlay::UIOverlay()
{
	//TODO set position of all elements
	//TODO Sent font sizes, fonts, colors, etc
}

//********** MUTATORS ************** 

void UIOverlay::setPosition(sf::View view)
{
	int x = view.getCenter().x - view.getSize().x;
	int y = view.getCenter().y - view.getSize().y;
	mainWrapperSprite.setPosition(x, y);
	//TODO Shift all elements of UI
}

void UIOverlay::setCurrency(float cur)
{
	currencyText.setString("Gold: " + std::to_string(cur));
}

void UIOverlay::setLevel(int lvl)
{
	leveltext.setString(std::to_string(lvl));
}

void UIOverlay::setHealth(int current, int max)
{
	//TODO fix
	int length = 300;
	damageBar.setSize(sf::Vector2f(length / max, 20));
	healthBar.setSize(sf::Vector2f((length - current) / max, 20));
}

void UIOverlay::setMana(int current, int max)
{
}

void UIOverlay::setExp(int current, int req)
{
}

