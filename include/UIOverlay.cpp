#include <SFML/Graphics.hpp>
#include <iostream>

#include "UIOverlay.h"

UIOverlay::UIOverlay()
{
	//Font
	font.loadFromFile("font/Ubuntu.ttf");
	currencyText.setCharacterSize(15);

	//level wrapper
	levelNumWrapper.setRadius(30);
	
	//Currency Text
	currencyText.setFont(font);
	
	//level Text
	levelText.setFont(font);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(25);
}

//********** MUTATORS ************** 

void UIOverlay::setPosition(sf::View view)
{
	int x = view.getCenter().x - (view.getSize().x / 2);
	int y = view.getCenter().y - (view.getSize().y / 2);
	mainWrapperSprite.setPosition(x, y);

	levelNumWrapper.setPosition(sf::Vector2f(x + 10, y + 20));

	currencyText.setPosition(sf::Vector2f(x + 900, y + 30));

	levelText.setPosition(sf::Vector2f(x + 33, y + 40));
}

void UIOverlay::setCurrency(int cur)
{
	currencyText.setString("Gold: " + std::to_string(cur));
}

void UIOverlay::setLevel(int lvl)
{
	levelText.setString(std::to_string(lvl));
}

//********* ETC ***********

void UIOverlay::drawAll(sf::RenderWindow& win)
{
	win.draw(mainWrapperSprite);

	win.draw(levelNumWrapper);
	win.draw(levelText);

	win.draw(currencyText);
}
