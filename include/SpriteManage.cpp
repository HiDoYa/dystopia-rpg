#include <SFML/Graphics.hpp>

#include "SpriteManage.h"

//****************** MUTATORS ********************
void SpriteManage::setTextureSprite(sf::String inp)
{
	texture.loadFromFile(inp);
	sprite.setTexture(texture);
}

void SpriteManage::setTextureRect(int x, int y)
{
	sprite.setTextureRect(sf::IntRect(x, y, 64, 64));
}

void SpriteManage::setTextureRect(int x, int y, int dimension)
{
	sprite.setTextureRect(sf::IntRect(x, y, dimension, dimension));
}

void SpriteManage::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

//****************** ACCESSORS  ********************
sf::Sprite SpriteManage::getSprite()
{
	return sprite;
}

sf::Vector2f SpriteManage::getPosition()
{
	return sprite.getPosition();
}

//****************** ETC ********************
void SpriteManage::drawSprite(sf::RenderWindow& win)
{
	win.draw(sprite);
}

void SpriteManage::moveSprite(int x, int y)
{
	sprite.move(sf::Vector2f(x, y));
}
