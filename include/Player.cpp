#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y)
{
	//Sets texture and position of sprite
	texturePosX = texturePosY = 0;

	//A character
	setTextureSprite("images/character/char1.png");
	setTextureRect(0, 0);
	setPosition(x, y);

	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	curStep = 0;

	//Used for time management
	lastTimeAnim = 0;
	lastTimeMu = 0;
	spriteAnimationDelay = 90;
	stepSoundDelay = 300;

	//Movement default
	speed = 8;
	lastDirection = 0;
	moving = false;
	movingNum = 0;
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

void Player::setHp(int inp)
{
	hp = inp;
}

int Player::getHp()
{
	return hp;
}

void Player::stepSound()
{
	time = clock.getElapsedTime(); 
	currentTime = time.asMilliseconds();

	if(lastTimeMu + stepSoundDelay < currentTime)
	{
		lastTimeMu = currentTime;
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
			setTextureRect(0, 256);
			break;
		case 1:
			setTextureRect(64, 256);
			break;
		case 2:
			setTextureRect(128, 256);
			break;
		case 3:
			setTextureRect(192, 256);
			break;
	}
}

void Player::movePos()
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

		//Stop moving after 8 times
		if(movingNum == 8)
		{
			movingNum = 0;
			moving = false;
		}
		
		//TODO
		moveSprite(xSpeed, ySpeed);
	}
	else if((wPress && sPress) || (aPress && dPress))
	{
		//Do nothing (moving in opposing directions)
	}
	else if(wPress && canMoveUp)
	{
		lastDirection = 0;
		moving = true;
		//spriteAnimation();
		stepSound();
	}
	else if(sPress && canMoveDown)
	{
		lastDirection = 1;
		moving = true;
		//spriteAnimation();
		stepSound();
	}
	else if(aPress && canMoveLeft)
	{
		lastDirection = 2;
		moving = true;
		//spriteAnimation();
		stepSound();
	}
	else if(dPress && canMoveRight)
	{
		lastDirection = 3;
		moving = true;
		//spriteAnimation();
		stepSound();
	}
	else
	{
		//standStill();
	}

	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

//Direction is 0 when top, 1 when right, 2 when down, 3 when left
void Player::spriteAnimation()
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(currentTime > lastTimeAnim + spriteAnimationDelay)
	{
		texturePosY = lastDirection * 64;
		lastTimeAnim = currentTime;
		texturePosX += 64;
		if(texturePosX > 64 * 6)
		{
			texturePosX = 64;
		}
		setTextureRect(texturePosX - 64, texturePosY);
	}
}

//Checks for collision
bool Player::collisionZones(int i, int j)
{
	//Checks if player is colliding
	bool colliding = false;

	//Gets the coordinates of players (in terms of every 64 pixels)
	int currentPlayerX, currentPlayerY;
	currentPlayerX = getPosition().x / 64;
	currentPlayerY = getPosition().y / 64;

	//Only if the player is within one block from the collision tile
	if((currentPlayerX == i && (currentPlayerY + 1 == j || currentPlayerY - 1 == j)) || (currentPlayerY == j && (currentPlayerX == i + 1 || currentPlayerX == i - 1)))
	{
		if(currentPlayerX == i)
		{
			if(currentPlayerY - 1 == j)
			{
				canMoveUp = false;
				colliding = true;
			}
			if(currentPlayerY + 1 == j)
			{
				canMoveDown = false;
				colliding = true;
			}
		}

		if(currentPlayerY == j)
		{
			if(currentPlayerX - 1 == i)
			{
				canMoveLeft = false;
				colliding = true;
			}
			if(currentPlayerX + 1 == i)
			{
				canMoveRight = false;
				colliding = true;
			}
		}
	}

	return colliding;
}
