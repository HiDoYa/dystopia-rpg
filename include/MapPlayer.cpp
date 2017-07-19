#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.h"
#include "UIOverlay.h"

#include "MapPlayer.h"

MapPlayer::MapPlayer()
{
	//Sets texture and position of sprite
	texturePosX = texturePosY = 0;
	setTextureSprite("images/ally/player.png");
	setTextureRect(64, 0);

	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	curStep = 0;

	//Used for tme management
	lastTimeAnim = 0;
	lastTimeMu = 0;
	currentTime = 0;
	spriteAnimationDelay = 60;
	stepSoundDelay = 300;

	//Movement default
	speed = 8;
	xSpeed = ySpeed = 0;
	lastDirection = 0;
	moving = false;
	movingNum = 0;
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
	checkEncounter = false;
}

//*********** MUTATORS ************

//*********** ACCESSORS ************
bool MapPlayer::getMoving()
{
	return moving;
}

//*********** ETC ************

void MapPlayer::stepSound()
{
	tme = clock.getElapsedTime(); 
	currentTime = tme.asMilliseconds();

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

void MapPlayer::standStill()
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

void MapPlayer::movePos()
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
		spriteAnimation();

		//Stop moving after 8 tmes
		if(movingNum == 8)
		{
			movingNum = 0;
			moving = false;
			checkEncounter = true;
		}
		
		moveSprite(xSpeed, ySpeed);
	}
	else if((wPress && sPress) || (aPress && dPress))
	{
		//Do nothing (moving in opposing directions)
	}
	else if(wPress)
	{
		keyPressAction(0, canMoveUp);
	}
	else if(sPress)
	{
		keyPressAction(1, canMoveDown);
	}
	else if(aPress)
	{
		keyPressAction(2, canMoveLeft);
	}
	else if(dPress)
	{
		keyPressAction(3, canMoveRight);
	}
	else
	{
		standStill();
	}

	//Reset flags and check whether one can move in directions again later
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

void MapPlayer::keyPressAction(int direction, bool canMove)
{
	lastDirection = direction;

	if(canMove)
	{
		moving = true;
		spriteAnimation();
		stepSound();
	}
	else
	{
		standStill();
	}
}

//Calculates whether player should encounter enemy. Encounter chance is from 0-100
void MapPlayer::encounter(int encounterChance, int& scene)
{
	if(checkEncounter)
	{
		checkEncounter = false;
		srand(time(NULL));
		if((rand() % 101) < encounterChance)
		{
			scene = 2;
		}
	}
}

//Direction is 0 when top, 1 when right, 2 when down, 3 when left
void MapPlayer::spriteAnimation()
{
	tme = clock.getElapsedTime();
	currentTime = tme.asMilliseconds();

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
bool MapPlayer::collisionZones(int i, int j)
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
				if(lastDirection == 0)
				{
					colliding = true;
				}
			}
			if(currentPlayerY + 1 == j)
			{
				canMoveDown = false;
				if(lastDirection == 1)
				{
					colliding = true;
				}
			}
		}

		if(currentPlayerY == j)
		{
			if(currentPlayerX - 1 == i)
			{
				canMoveLeft = false;
				if(lastDirection == 3)
				{
					colliding = true;
				}
			}
			if(currentPlayerX + 1 == i)
			{
				canMoveRight = false;
				if(lastDirection == 3)
				{
					colliding = true;
				}
			}
		}
	}

	return colliding;
}
