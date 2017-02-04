#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y)
{
	texture.loadFromFile("images/character/player.png");

	//Sets texture and position of sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(x, y);
	texturePosX = texturePosY = 0;

	//TODO Collision Rectangle
	//collisionRectangle.setSize(sprite.getScale());

	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	curStep = 0;

	//Used for time management
	lastTime = 0;
	lastTimeMu = 0;

	//Movement default
	speedRegular = 8;
	speedSlow = 6;
	lastDirection = 0;
}

void Player::setScale(float num)
{
	sprite.setScale(sf::Vector2f(num, num));
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
		curStep = (curStep + 1) % 2;

		switch (curStep)
		{
			case 0:
				step1.play();
				break;
			case 1:
				step2.play();
				break;
		}
	}
}

void Player::setCollisionBools(sf::Sprite spr, int speed)
{
	canMoveUp = canMoveDown = canMoveRight = canMoveLeft = false;

	sf::Vector2f sprRightCheckNum = sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + speed, sprite.getGlobalBounds().top);
	sf::Vector2f sprLeftCheckNum = sf::Vector2f(sprite.getGlobalBounds().left - speed, sprite.getGlobalBounds().top);
	sf::Vector2f sprUpCheckNum = sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top - speed);
	sf::Vector2f sprDownCheckNum = sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + spr.getGlobalBounds().height + speed);

	//TODO
	if(true)
	{
		//Can't move right
	}
	else if(true)
	{
		//Can't move left 
	}
	else if(true)
	{
		//Can't move up 
	}
	else if(true)
	{
		//Can't move down 
	}
}

void Player::standStill()
{
	switch(lastDirection)
	{
		case 0:
			sprite.setTextureRect(sf::IntRect(0, 256, 64, 64));
			break;
		case 1:
			sprite.setTextureRect(sf::IntRect(64, 256, 64, 64));
			break;
		case 2:
			sprite.setTextureRect(sf::IntRect(128, 256, 64, 64));
			break;
		case 3:
			sprite.setTextureRect(sf::IntRect(192, 256, 64, 64));
			break;
	}
}

void Player::movePos(float& xDisplacement, float& yDisplacement)
{
	bool wPress = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool sPress = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool aPress = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool dPress = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	//Resets speed
	primarySpeed = secondarySpeed = speedRegular;

	if((wPress && sPress) || (aPress && dPress))
	{
		//Do nothing (moving in opposing directions)
	}
	else if(wPress && dPress)
	{
		if(lastDirection == 0)
		{
			primarySpeed = speedSlow;
		}
		else if(lastDirection == 3)
		{
			secondarySpeed = speedSlow;
		}
		else
		{
			lastDirection = 0;
			primarySpeed = speedSlow;
		}

		sprite.move(primarySpeed, -secondarySpeed);
		xDisplacement += primarySpeed;
		yDisplacement += -secondarySpeed;
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(wPress && aPress)
	{
		if(lastDirection == 0)
		{
			primarySpeed = speedSlow;
		}
		else if(lastDirection == 2)
		{
			secondarySpeed = speedSlow;
		}
		else
		{
			lastDirection = 0;
			primarySpeed = speedSlow;
		}

		sprite.move(-primarySpeed, -secondarySpeed);
		xDisplacement += -primarySpeed;
		yDisplacement += -secondarySpeed;
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(sPress && dPress)
	{
		if(lastDirection == 1)
		{
			primarySpeed = speedSlow;
		}
		else if(lastDirection == 3)
		{
			secondarySpeed = speedSlow;
		}
		else
		{
			lastDirection = 1;
			primarySpeed = speedSlow;
		}

		sprite.move(primarySpeed, secondarySpeed);
		xDisplacement += primarySpeed;
		yDisplacement += secondarySpeed;
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(sPress && aPress)
	{
		if(lastDirection == 1)
		{
			primarySpeed = speedSlow;
		}
		else if(lastDirection == 2)
		{
			secondarySpeed = speedSlow;
		}
		else
		{
			lastDirection = 1;
			primarySpeed = speedSlow;
		}

		sprite.move(-primarySpeed, secondarySpeed);
		xDisplacement += -primarySpeed;
		yDisplacement += secondarySpeed;
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(wPress)
	{
		sprite.move(0, -primarySpeed);
		xDisplacement += 0;
		yDisplacement += -primarySpeed;
		spriteAnimation(0);
		lastDirection = 0;
		stepSound();
	}
	else if(sPress)
	{
		sprite.move(0, primarySpeed);
		xDisplacement += 0;
		yDisplacement += primarySpeed;
		spriteAnimation(1);
		lastDirection = 1;
		stepSound();
	}
	else if(aPress)
	{
		sprite.move(-primarySpeed, 0);
		xDisplacement += -primarySpeed;
		yDisplacement += 0;
		spriteAnimation(2);
		lastDirection = 2;
		stepSound();
	}
	else if(dPress)
	{
		sprite.move(primarySpeed, 0);
		xDisplacement += primarySpeed;
		yDisplacement += 0;
		spriteAnimation(3);
		lastDirection = 3;
		stepSound();
	}
	else
	{
		standStill();
	}
}

//Direction is 0 when top, 1 when right, 2 when down, 3 when left
void Player::spriteAnimation(int direction)
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	if(currentTime > lastTime + 90)
	{
		texturePosY = direction * 64;
		lastTime = currentTime;
		texturePosX += 64;
		if(texturePosX > 64 * 6)
		{
			texturePosX = 64;
		}
		sprite.setTextureRect(sf::IntRect(texturePosX - 64, texturePosY, 64, 64));
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

sf::Vector2f Player::getPos()
{
	return sprite.getPosition();
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
