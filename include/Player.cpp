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

	//Hp
	hp = 100;
	
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

void Player::setPos(int x, int y)
{
	sprite.setPosition(x, y);
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
		
		sprite.move(xSpeed, ySpeed);
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
		sprite.setTextureRect(sf::IntRect(texturePosX - 64, texturePosY, 64, 64));
	}
}

void Player::setHp(int hpSet)
{
	hp = hpSet;
}

//Checks for collision
bool Player::collisionZones(int i, int j)
{
	//Checks if player is colliding
	bool colliding = false;

	//Gets the coordinates of players (in terms of every 64 pixels)
	int currentPlayerX, currentPlayerY;
	currentPlayerX = sprite.getPosition().x / 64;
	currentPlayerY = sprite.getPosition().y / 64;

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

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

sf::Sprite Player::getSprite()
{
	return sprite;
}

int Player::getHp()
{
	return hp;
}
