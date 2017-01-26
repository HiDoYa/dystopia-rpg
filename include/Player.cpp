#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y, sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Player::setTexture(sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}
}

void Player::setScale(double num)
{
	sprite.setScale(sf::Vector2f(num, num));
}

void Player::setPos(int x, int y)
{
	sprite.setPosition(x, y);
}

void Player::movePos(int speed)
{
	bool wPress = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool sPress = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool aPress = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool dPress = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	if((wPress && sPress) || (aPress && dPress))
	{
		std::cout << "Moving in opposing directions..." << std::endl;
	}
	else if(wPress && dPress)
	{
		sprite.move(speed, -speed);
	}
	else if(wPress && aPress)
	{
		sprite.move(-speed, -speed);
	}
	else if(sPress && dPress)
	{
		sprite.move(speed, speed);
	}
	else if(sPress && aPress)
	{
		sprite.move(-speed, speed);
	}
	else if(wPress)
	{
		sprite.move(0, -speed);
	}
	else if(sPress)
	{
		sprite.move(0, speed);
	}
	else if(dPress)
	{
		sprite.move(speed, 0);
	}
	else if(aPress)
	{
		sprite.move(-speed, 0);
	}
}

void Player::mouseAndCharAngle(sf::Vector2i mo)
{
	//TODO FIX
	//Calculates how much to rotate the player using trigonometry
	double a = mo.x - sprite.getPosition().x;
	double b = sprite.getPosition().y - mo.y;
	double r = sqrt(a*a + b*b);
	sprite.setRotation((asin(b / r)) * 180 / 3.14);
}

void Player::rotatePos(int degrees)
{
	//TODO
	sprite.rotate(degrees);
}

sf::Texture Player::getTexture()
{
	return texture;
}

sf::Sprite Player::getSprite()
{
	return sprite;
}
