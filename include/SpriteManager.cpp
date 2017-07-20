#include <iostream>

#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
}

//****************** MUTATORS ********************
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
sf::Sprite* SpriteManager::getSprite()
{
	return &sprite;
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
