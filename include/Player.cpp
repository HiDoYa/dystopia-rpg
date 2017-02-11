#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y)
{
	texture.loadFromFile("images/character/char1.png");

	//Sets texture and position of sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	sprite.setPosition(x, y);
	texturePosX = texturePosY = 0;
	
	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	curStep = 0;

	//Used for time management
	lastTime = 0;
	lastTimeMu = 0;
	spriteAnimationDelay = 90;
	stepSoundDelay = 300;

	//Movement default
	speed = 8;
	lastDirection = 0;
	moving = false;
	movingNum = 0;
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

	if(lastTimeMu + stepSoundDelay < currentTimeMu)
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

void Player::standStill()
{
	switch(lastDirection)
	{
		case 0:
			sprite.setTextureRect(sf::IntRect(0, 384, 64, 64));
			break;
		case 1:
			sprite.setTextureRect(sf::IntRect(96, 384, 64, 64));
			break;
		case 2:
			sprite.setTextureRect(sf::IntRect(192, 384, 64, 64));
			break;
		case 3:
			sprite.setTextureRect(sf::IntRect(288, 384, 64, 64));
			break;
	}
}

void Player::movePos(float& xDisplacement, float& yDisplacement)
{
	bool wPress = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool sPress = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool aPress = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool dPress = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	xSpeed = ySpeed = 0;

	if(moving)
	{
		switch (lastDirection)
		{
			case 0:
				ySpeed = -speed;
				break;
			case 1:
				ySpeed = speed;
				break;
			case 2: 
				xSpeed = -speed;
				break;
			case 3: 
				xSpeed = speed;
				break;
		}
		movingNum++;
		if(movingNum == 7)
		{
			movingNum = 0;
			moving = false;
		}
	}
	else if((wPress && sPress) || (aPress && dPress))
	{
		//Do nothing (moving in opposing directions)
	}
	else if(wPress)
	{
		lastDirection = 0;
		moving = true;
		stepSound();
	}
	else if(sPress)
	{
		lastDirection = 1;
		moving = true;
		stepSound();
	}
	else if(aPress)
	{
		lastDirection = 2;
		moving = true;
		stepSound();
	}
	else if(dPress)
	{
		lastDirection = 3;
		moving = true;
		stepSound();
	}
	else
	{
		//standStill();
	}

	//Checks whether the player CAN move
	//if(!canMoveUp && ySpeed < 0)
	//{
	//	ySpeed = 0;
	//}
	//if(!canMoveDown && ySpeed > 0)
	//{
	//	ySpeed = 0;
	//}
	//if(!canMoveLeft && xSpeed < 0)
	//{
	//	xSpeed = 0;
	//}
	//if(!canMoveRight && xSpeed > 0)
	//{
	//	xSpeed = 0;
	//}

	//Moves sprite and adds to displacement of screen (for mouse)
	sprite.move(xSpeed, ySpeed);
	xDisplacement += xSpeed;
	yDisplacement += ySpeed;
}

//Direction is 0 when top, 1 when right, 2 when down, 3 when left
void Player::spriteAnimation(int direction)
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	if(currentTime > lastTime + spriteAnimationDelay)
	{
		texturePosY = direction * 96;
		lastTime = currentTime;
		texturePosX += 96;
		if(texturePosX > 96 * 6)
		{
			texturePosX = 96;
		}
		sprite.setTextureRect(sf::IntRect(texturePosX - 96, texturePosY, 96, 96));
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

