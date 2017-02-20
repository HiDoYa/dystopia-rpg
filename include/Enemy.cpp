#include "Enemy.h"

#include <iostream>

Enemy::Enemy(int x, int y)
{
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

	//Sets health bars
	maxHpBar.setSize(sf::Vector2f(100, 50));
	currentHpBar.setSize(sf::Vector2f(100, 50));

	//Sets position 
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

void Enemy::setCurrentHp(int inp)
{
	currentHp = inp;
	currentHpBar.setFillColor(sf::Color::Green);
	currentHpBar.setSize(sf::Vector2f(100, 10));
	currentHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);
}

void Enemy::setMaxHp(int inp)
{
	maxHp = inp;
	maxHpBar.setFillColor(sf::Color::Red);
	maxHpBar.setSize(sf::Vector2f(100, 10));
	maxHpBar.setPosition(getPosition().x - 15, getPosition().y - 50);
}

void Enemy::setCurrentMana(int inp)
{
	currentMana = inp;
	currentManaBar.setFillColor(sf::Color::Green);
	currentManaBar.setSize(sf::Vector2f(100, 10));
	currentManaBar.setPosition(getPosition().x - 15, getPosition().y - 50);
}

void Enemy::setMaxMana(int inp)
{
	maxMana = inp;
	maxManaBar.setFillColor(sf::Color::Red);
	maxManaBar.setSize(sf::Vector2f(100, 10));
	maxManaBar.setPosition(getPosition().x - 15, getPosition().y - 50);
}

void Enemy::setAgility(int inp)
{
	agility = inp;
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

int Enemy::getCurrentHp()
{
	return currentHp;
}

int Enemy::getMaxHp()
{
	return maxHp;
}

int Enemy::getCurrentMana()
{
	return currentMana;
}

int Enemy::getMaxMana()
{
	return maxMana;
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

void Enemy::drawHealthBar(sf::RenderWindow& win)
{
	win.draw(maxHpBar);
	win.draw(currentHpBar);
}

void Enemy::drawTimeBar(sf::RenderWindow& win)
{
	win.draw(timeReq);
	win.draw(timeFilled);
}

void Enemy::drawAll(sf::RenderWindow& win)
{
	//Draw bars
	drawHealthBar(win);
	drawTimeBar(win);

	//Draws sprite
	setTextureSprite("images/enemies/test4.png");
	setTextureRect(0, 0);
	win.draw(getSprite());
}
