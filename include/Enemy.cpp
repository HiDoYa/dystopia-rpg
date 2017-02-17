#include "Enemy.h"

#include <iostream>

Enemy::Enemy(int x, int y, int downFromTop)
{
	//Default attributes of enemy
	id = 1;
	hp = 100;
	level = 3;
	atk = 10;
	delay = 6000;
	alive = true;

	//Sets health bars
	health.setSize(sf::Vector2f(100, 50));
	damage.setSize(sf::Vector2f(100, 50));

	//TODO setTextureSprite("someEnemySpriteSheet.png");
	setTextureRect(0, downFromTop);
	setPosition(x, y);
}

//********* MUTATORS *********

void Enemy::setId(int inp)
{
	id = inp;
}

void Enemy::setCurrentHp(int inp)
{
	currentHp = inp;
}

void Enemy::setMaxHp(int inp)
{
	maxHp = inp;
}

void Enemy::setLevel(int inp)
{
	level = inp;
}

void Enemy::setAtk(int inp)
{
	atk = inp;
}

void Enemy::setDelay(int inp)
{
	delay = inp;
}

void Enemy::setAlive(bool inp)
{
	alive = inp;
}

//********* ACCESSORS *********

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

int Enemy::getAtk()
{
	return atk;
}

int Enemy::getDelay()
{
	return delay;
}

bool Enemy::getAlive()
{
	return alive;
}
