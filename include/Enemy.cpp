#include "Enemy.h"

Enemy::Enemy(int x, int y, sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file\n";
	}

	//Sets texture and position of sprite
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Enemy::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::setScale(int sc)
{
	sprite.setScale(sf::Vector2f(sc, sc));
}

void Enemy::setHealth(int i)
{
	health = i;
}

void Enemy::setAttackDmg(int i)
{
	attackDmg = i;
}

sf::Sprite Enemy::getSprite()
{
	return sprite;
}

bool Enemy::mouseOver(sf::Sprite mouse)
{
	if(sprite.getGlobalBounds().contains(mouse.getPosition()))
	{
		isMouseOver = true;
		return true;
	}
	else
	{
		isMouseOver = false;
		return false;
	}
}

bool Enemy::getColliding(sf::Sprite spr)
{
	return collisionRectangle.getGlobalBounds().intersects(spr.getGlobalBounds());
}

bool Enemy::getColliding(sf::RectangleShape rec)
{
	return collisionRectangle.getGlobalBounds().intersects(rec.getGlobalBounds());
}

int Enemy::getHealth()
{
	return health;
}

int Enemy::getAttackDmg()
{
	return attackDmg;
}
