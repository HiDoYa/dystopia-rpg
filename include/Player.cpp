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

	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	step3.openFromFile("sound/step3.ogg");
	curStep = 0;

	//Used for time management
	lastTime = 0;
	lastTimeMu = 0;
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

void Player::stepSound()
{
	tme = clk.getElapsedTime();
	currentTimeMu = tme.asMilliseconds();

	if(lastTimeMu + 300 < currentTimeMu)
	{
		lastTimeMu = currentTimeMu;
		curStep = (curStep + 1) % 3;

		switch (curStep)
		{
			case 0:
				step1.play();
				break;
			case 1:
				step2.play();
				break;
			case 2:
				step3.play();
				break;
		}
	}
}

void Player::movePos(int speed, float& xDisplacement, float& yDisplacement)
{
	bool wPress = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool sPress = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool aPress = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool dPress = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if((wPress && sPress) || (aPress && dPress))
	{
		//Do nothing (moving in opposing directions)
	}
	else if(wPress && dPress)
	{
		sprite.move(speed, -speed);
		xDisplacement += speed;
		yDisplacement += -speed;
		stepSound();
	}
	else if(wPress && aPress)
	{
		sprite.move(-speed, -speed);
		xDisplacement += -speed;
		yDisplacement += -speed;
		stepSound();
	}
	else if(sPress && dPress)
	{
		sprite.move(speed, speed);
		xDisplacement += speed;
		yDisplacement += speed;
		stepSound();
	}
	else if(sPress && aPress)
	{
		sprite.move(-speed, speed);
		xDisplacement += -speed;
		yDisplacement += speed;
		stepSound();
	}
	else if(wPress)
	{
		sprite.move(0, -speed);
		xDisplacement += 0;
		yDisplacement += -speed;
		stepSound();
	}
	else if(sPress)
	{
		sprite.move(0, speed);
		xDisplacement += 0;
		yDisplacement += speed;
		stepSound();
	}
	else if(dPress)
	{
		sprite.move(speed, 0);
		xDisplacement += speed;
		yDisplacement += 0;
		stepSound();
	}
	else if(aPress)
	{
		sprite.move(-speed, 0);
		xDisplacement += -speed;
		yDisplacement += 0;
		stepSound();
	}
}

void Player::dashMove(int speed)
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	bool spacePress = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(spacePress && currentTime > lastTime + 3000)
	{
		lastTime = currentTime;
		//TODO Speed Modifier. Different sprites? Different movement? 
		speed *= 2;
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
