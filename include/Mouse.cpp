#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	textureDefault.loadFromFile("images/cursors/default.png");
	textureTalk.loadFromFile("images/cursors/talk.png");

	sprite.setTexture(textureDefault);
	sprite.setScale(sf::Vector2f(0.09, 0.09));
}

void Mouse::useDefaultMouse()
{
	sprite.setTexture(textureDefault);
}

void Mouse::useTalkMouse()
{
	sprite.setTexture(textureTalk);
}

void Mouse::setScale(int i)
{
	sprite.setScale(sf::Vector2f(i, i ));
}

void Mouse::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}

sf::Sprite Mouse::getSprite()
{
	return sprite;
}

sf::Texture Mouse::getTextureDefault()
{
	return textureDefault;
}

sf::Texture Mouse::getTextureTalk()
{
	return textureTalk;
}
