#include "Enemy.h"

Enemy::Enemy()
{
}

void setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

void setScale(int sc)
{
	sprite.setScale(sf::Vector2f(sc, sc));
}

void setHealth(int i)
{
	health = i;
}

void setAttackDmg(int i)
{
	attackDmg = i;
}

sf::Sprite getSprite()
{
	return sprite;
}

int getHealth()
{
	return health;
}

int getAttackDmg()
{
	return attackDmg;
}
