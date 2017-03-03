#include <SFML/Graphics.hpp>

#include "UIOverlay.h"

UIOverlay::UIOverlay()
{
	//Font
	font.loadFromFile("font/Ubuntu.ttf");
	currencyText.setCharacterSize(25);

	//HP
	maxHpBar.setFillColor(sf::Color::Red);
	currentHpBar.setFillColor(sf::Color::Green);

	//Mana
	maxManaBar.setFillColor(sf::Color::Black);
	currentManaBar.setFillColor(sf::Color::Blue);

	//Exp bars
	maxExpBar.setFillColor(sf::Color::Black);
	currentExpBar.setFillColor(sf::Color::Yellow);

	//level wrapper
	levelNumWrapper.setRadius(30);
	
	//Currency Text
	currencyText.setFont(font);
	
	//level Text
	levelText.setFont(font);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(35);
}

//********** MUTATORS ************** 

void UIOverlay::setPosition(sf::View view)
{
	int x = view.getCenter().x - (view.getSize().x / 2);
	int y = view.getCenter().y - (view.getSize().y / 2);
	mainWrapperSprite.setPosition(x, y);

	maxHpBar.setPosition(sf::Vector2f(x + 30, y + 30));
	currentHpBar.setPosition(sf::Vector2f(x + 30, y + 30));

	maxManaBar.setPosition(sf::Vector2f(x + 30, y + 55));
	currentManaBar.setPosition(sf::Vector2f(x + 30, y + 55));

	maxExpBar.setPosition(sf::Vector2f(x, y));
	currentExpBar.setPosition(sf::Vector2f(x, y));

	levelNumWrapper.setPosition(sf::Vector2f(x + 10, y + 20));

	currencyText.setPosition(sf::Vector2f(x + 900, y + 30));

	levelText.setPosition(sf::Vector2f(x + 30, y + 30));
}

void UIOverlay::setCurrency(int cur)
{
	currencyText.setString("Gold: " + std::to_string(cur));
}

void UIOverlay::setLevel(int lvl)
{
	levelText.setString(std::to_string(lvl));
}

void UIOverlay::setHealth(int current, int max)
{
	int length = 300;
	maxHpBar.setSize(sf::Vector2f(length, 15));
	currentHpBar.setSize(sf::Vector2f((static_cast<float> (current) / max) * length, 15));
}

void UIOverlay::setMana(int current, int max)
{
	int length = 300;
	maxManaBar.setSize(sf::Vector2f(length, 15));
	currentManaBar.setSize(sf::Vector2f((static_cast<float> (current) / max) * length, 15));
}

void UIOverlay::setExp(int current, int max)
{
	int length = 1024;
	maxExpBar.setSize(sf::Vector2f(length, 10));
	currentExpBar.setSize(sf::Vector2f((static_cast<float>(current) / max) * length, 10));
}

//********* ETC ***********

void UIOverlay::drawAll(sf::RenderWindow& win)
{
	win.draw(mainWrapperSprite);

	win.draw(maxHpBar);
	win.draw(currentHpBar);

	win.draw(maxManaBar);
	win.draw(currentManaBar);

	win.draw(maxExpBar);
	win.draw(currentExpBar);

	win.draw(levelNumWrapper);
	win.draw(levelText);

	win.draw(currencyText);
}
