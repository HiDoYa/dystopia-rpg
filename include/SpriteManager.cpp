#include <SFML/Graphics.hpp>
#include <iostream>

#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
	length = 100;

	//Set bar color
	currentHpBar.setFillColor(sf::Color::Green);
	maxHpBar.setFillColor(sf::Color::Red);

	currentManaBar.setFillColor(sf::Color::Blue);
	maxManaBar.setFillColor(sf::Color::Black);

	//Set name
	name.setString("Character");
	font.loadFromFile("font/Ubuntu.ttf");
	name.setFont(font);
	name.setCharacterSize(15);
}

//****************** MUTATORS ********************
void SpriteManager::setName(std::string inp)
{
	name.setString(inp);
}

void SpriteManager::setHpBar(int currentHp, int maxHp)
{
	maxHpBar.setSize(sf::Vector2f(length, 10));
	currentHpBar.setSize(sf::Vector2f((static_cast<float>(currentHp) / maxHp) * length, 10));
}

void SpriteManager::setManaBar(int currentMana, int maxMana)
{
	maxManaBar.setSize(sf::Vector2f(length, 10));
	currentManaBar.setSize(sf::Vector2f((static_cast<float>(currentMana) / maxMana) * length, 10));
}

void SpriteManager::setTextureSprite(std::string inp)
{
	texture.loadFromFile(inp);
	sprite.setTexture(texture);
}

void SpriteManager::setTextureRect(int x, int y)
{
	sprite.setTextureRect(sf::IntRect(x, y, 64, 64));
}

void SpriteManager::setTextureRect(int x, int y, int dimension)
{
	sprite.setTextureRect(sf::IntRect(x, y, dimension, dimension));
}

void SpriteManager::setScale(float x, float y)
{
	sprite.setScale(sf::Vector2f(x, y));
}

void SpriteManager::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

//****************** ACCESSORS  ********************
sf::Sprite SpriteManager::getSprite()
{
	return sprite;
}

sf::Vector2f SpriteManager::getPosition()
{
	return sprite.getPosition();
}

//****************** ETC ********************
void SpriteManager::drawSprite(sf::RenderWindow& win)
{
	win.draw(sprite);
}

void SpriteManager::updatePositionBattle()
{
	currentHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);
	maxHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);

	currentManaBar.setPosition(getPosition().x - 15, getPosition().y - 40);
	maxManaBar.setPosition(getPosition().x - 15, getPosition().y - 40);

	name.setPosition(getPosition().x - 10, getPosition().y - 80);
}

void SpriteManager::drawSpriteBattle(sf::RenderWindow& win)
{
	win.draw(sprite);

	win.draw(maxHpBar);
	win.draw(currentHpBar);
	
	win.draw(maxManaBar);
	win.draw(currentManaBar);

	win.draw(name);
}


void SpriteManager::moveSprite(int x, int y)
{
	sprite.move(sf::Vector2f(x, y));
}
