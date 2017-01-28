#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y, sf::String nameTexture)
{
	//Load texture
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}

	//Sets texture and position of sprite
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	//Sets size of sprite
	collisionRectangle.setSize(sprite.getScale());

	//Used for time management
	lastTime = 0;
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
	collisionRectangle.setSize(sprite.getScale());
}

void Player::setPos(int x, int y)
{
	sprite.setPosition(x, y);
}

void Player::movePos(int speed)
{
	bool spacePress = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	if(spacePress && currentTime > lastTime + 3000)
	{
		lastTime = currentTime;
		//TODO Speed Modifier. Different sprites? Different movement? 
		speed *= 2;
	}

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

sf::RectangleShape Player::getCollisionRectangle()
{
	return collisionRectangle;
}
