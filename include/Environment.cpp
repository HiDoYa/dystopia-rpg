#include <iostream>
#include "Environment.h"

//Default constructor
Environment::Environment(int x, int y, sf::String str)
{
	texture.loadFromFile(str);
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(x, y));
}

void Environment::setScale(int scl)
{
	sprite.setScale(sf::Vector2f(scl, scl));
}

void Environment::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

bool Environment::getColliding(sf::RectangleShape rec)
{
	return sprite.getGlobalBounds().intersects(rec.getGlobalBounds());
}

bool Environment::getColliding(sf::Sprite spr)
{
	return sprite.getGlobalBounds().intersects(spr.getGlobalBounds());
}

sf::Sprite Environment::getSprite()
{
	return sprite;
}
