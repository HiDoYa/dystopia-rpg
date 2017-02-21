#include "Enemy.h"

#include <iostream>

Enemy::Enemy(int x, int y)
{
	//The length of all bars
	length = 100;

	//Default attributes of enemy
	name.setString("Enemy");
	level = 3;
	maxHp = 100;
	currentHp = 100;
	maxMana = 10;
	currentMana = 10;
	agility = 100;
	atk = 10;
	alive = true;
	
	//Set bar color
	currentHpBar.setFillColor(sf::Color::Green);
	maxHpBar.setFillColor(sf::Color::Red);
	
	currentManaBar.setFillColor(sf::Color::Blue);
	maxManaBar.setFillColor(sf::Color::Black);

	timeReq.setFillColor(sf::Color::Yellow);
	timeFull.setFillColor(sf::Color::Black);

	//Sets position of sprite
	setPosition(x, y);
}

//********* MUTATORS *********

void Enemy::setName(sf::String inp)
{
	name.setString(inp);
}

void Enemy::setLevel(int inp)
{
	level = inp;
}

void Enemy::setMaxHp(int inp)
{
	maxHp = inp;
	maxHpBar.setSize(sf::Vector2f(length, 10));
}

void Enemy::setCurrentHp(int inp)
{
	currentHp = inp;
	currentHpBar.setSize(sf::Vector2f((static_cast<float>(currentHp) / maxHp) * length, 10));
}

void Enemy::setMaxMana(int inp)
{
	maxMana = inp;
	maxManaBar.setSize(sf::Vector2f(length, 10));
}

void Enemy::setCurrentMana(int inp)
{
	currentMana = inp;
	currentManaBar.setSize(sf::Vector2f((static_cast<float>(currentMana) / maxMana) * length, 10));
}

void Enemy::setAgility(int inp)
{
	agility = inp;
	timeReq.setSize(sf::Vector2f((length), 10));
	timeFull.setSize(sf::Vector2f((static_cast<float>(1) * length), 10));
	//TODO timeReq.
}

void Enemy::setAtk(int inp)
{
	atk = inp;
}

void Enemy::setAlive(bool inp)
{
	alive = inp;
}

//********* ACCESSORS *********

sf::String Enemy::getName()
{
	return name.getString();
}

int Enemy::getLevel()
{
	return level;
}

int Enemy::getMaxHp()
{
	return maxHp;
}

int Enemy::getCurrentHp()
{
	return currentHp;
}

int Enemy::getMaxMana()
{
	return maxMana;
}

int Enemy::getCurrentMana()
{
	return currentMana;
}

int Enemy::getAgility()
{
	return agility;
}

int Enemy::getAtk()
{
	return atk;
}

bool Enemy::getAlive()
{
	return alive;
}

//************ DRAW

void Enemy::updatePosition()
{
	//Sets bar placement
	currentHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);
	maxHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);

	currentManaBar.setPosition(getPosition().x - 15, getPosition().y - 40);
	maxManaBar.setPosition(getPosition().x - 15, getPosition().y - 40);

	timeReq.setPosition(getPosition().x - 15, getPosition().y - 20);
	timeFull.setPosition(getPosition().x - 15, getPosition().y - 20);
}

void Enemy::drawAll(sf::RenderWindow& win)
{	
	//Draw hp bars
	win.draw(maxHpBar);
	win.draw(currentHpBar);
	
	//Draw mana bars
	win.draw(maxManaBar);
	win.draw(currentManaBar);

	//Draw timebars
	win.draw(timeReq);
	win.draw(timeFull);

	//Draws sprite
	setTextureSprite("images/enemies/test4.png");
	setTextureRect(0, 0);
	win.draw(getSprite());
}
