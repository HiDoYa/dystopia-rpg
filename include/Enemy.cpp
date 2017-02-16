#include "Enemy.h"

#include <iostream>

Enemy::Enemy(int x, int y, int downFromTop)
{
	//Default
	id = 1;
	hp = 100;
	level = 3;
	atk = 10;
	delay = 6000;
	alive = true;

	//TODO setTextureSprite(asdf);
	setTextureRect(0, downFromTop);
	setPosition(x, y);
}

//********* MUTATORS *********

void Enemy::setId(int inp)
{
	id = inp;
}

void Enemy::setHp(int inp)
{
	hp = inp;
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

int Enemy::getHp()
{
	return hp;
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
