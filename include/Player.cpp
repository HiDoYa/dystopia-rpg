#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(int x, int y)
{
	texture.loadFromFile("images/character/player.png");

	//Sets texture and position of sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
	sprite.setPosition(x, y);
	texturePosX = texturePosY = 0;
	sprite.setScale(1, 1);

	//Collision rectangle
	collisionRectangle.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - sprite.getGlobalBounds().height / 2));
	
	//Stores size of sprite in vector2f
	collisionSize = sf::Vector2f(collisionRectangle.getGlobalBounds().width, collisionRectangle.getGlobalBounds().height);

	//Sound
	step1.openFromFile("sound/step1.ogg");
	step2.openFromFile("sound/step2.ogg");
	curStep = 0;

	//Used for time management
	lastTime = 0;
	lastTimeMu = 0;
	spriteAnimationDelay = 90;
	stepSoundDelay = 300;
	dashMoveDelay = 3000;

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



void Player::setCollisionBools(sf::Sprite spr)
{
	canMoveUp = canMoveDown = canMoveRight = canMoveLeft = true;

	//Gets point for each given that the sprite moves
	sf::Vector2f sprUpCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left, collisionRectangle.getGlobalBounds().top - speedRegular);
	sf::Vector2f sprDownCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left, collisionRectangle.getGlobalBounds().top + speedRegular);
	sf::Vector2f sprLeftCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left - speedRegular, collisionRectangle.getGlobalBounds().top);
	sf::Vector2f sprRightCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left + speedRegular, collisionRectangle.getGlobalBounds().top);
	
	//Calculates each rectangle for if the player CAN move
	sf::Rect<float> moveUpRect(sprUpCheckNum, collisionSize);
	sf::Rect<float> moveDownRect(sprDownCheckNum, collisionSize);
	sf::Rect<float> moveLeftRect(sprLeftCheckNum, collisionSize);
	sf::Rect<float> moveRightRect(sprRightCheckNum, collisionSize);

	if(spr.getGlobalBounds().intersects(moveUpRect))
	{
		canMoveUp = false;
	}
	if(spr.getGlobalBounds().intersects(moveDownRect))
	{
		canMoveDown = false;
	}
	if(spr.getGlobalBounds().intersects(moveLeftRect))
	{
		canMoveLeft = false;
	}
	if(spr.getGlobalBounds().intersects(moveRightRect))
	{
		canMoveRight = false;
	}
}

void Player::setCollisionBools(sf::RectangleShape rect)
{
	canMoveUp = canMoveDown = canMoveRight = canMoveLeft = true;

	//Gets point for each given that the sprite moves
	sf::Vector2f sprUpCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left, collisionRectangle.getGlobalBounds().top - speedRegular);
	sf::Vector2f sprDownCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left, collisionRectangle.getGlobalBounds().top + speedRegular);
	sf::Vector2f sprLeftCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left - speedRegular, collisionRectangle.getGlobalBounds().top);
	sf::Vector2f sprRightCheckNum = sf::Vector2f(collisionRectangle.getGlobalBounds().left + speedRegular, collisionRectangle.getGlobalBounds().top);
	
	//Calculates each rectangle for if the player CAN move
	sf::Rect<float> moveUpRect(sprUpCheckNum, collisionSize);
	sf::Rect<float> moveDownRect(sprDownCheckNum, collisionSize);
	sf::Rect<float> moveLeftRect(sprLeftCheckNum, collisionSize);
	sf::Rect<float> moveRightRect(sprRightCheckNum, collisionSize);

	if(rect.getGlobalBounds().intersects(moveUpRect))
	{
		canMoveUp = false;
	}
	if(rect.getGlobalBounds().intersects(moveDownRect))
	{
		canMoveDown = false;
	}
	if(rect.getGlobalBounds().intersects(moveLeftRect))
	{
		canMoveLeft = false;
	}
	if(rect.getGlobalBounds().intersects(moveRightRect))
	{
		canMoveRight = false;
	}
}

void Player::standStill()
{
	switch(lastDirection)
	{
		case 0:
			sprite.setTextureRect(sf::IntRect(0, 384, 96, 96));
			break;
		case 1:
			sprite.setTextureRect(sf::IntRect(96, 384, 96, 96));
			break;
		case 2:
			sprite.setTextureRect(sf::IntRect(192, 384, 96, 96));
			break;
		case 3:
			sprite.setTextureRect(sf::IntRect(288, 384, 96, 96));
			break;
	}
}

void Player::movePos(float& xDisplacement, float& yDisplacement)
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
		if(lastDirection == 0)
		{
			xSpeed = speedSlow;
			ySpeed = -speedRegular;
		}
		else if(lastDirection == 3)
		{
			xSpeed = speedRegular;
			ySpeed = -speedSlow;
		}
		else
		{
			xSpeed = speedSlow;
			ySpeed = -speedRegular;
			lastDirection = 0;
		}
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(wPress && aPress)
	{
		if(lastDirection == 0)
		{
			xSpeed = -speedSlow;
			ySpeed = -speedRegular;
		}
		else if(lastDirection == 2)
		{
			xSpeed = -speedRegular;
			ySpeed = -speedSlow;
		}
		else
		{
			xSpeed = -speedSlow;
			ySpeed = -speedRegular;
			lastDirection = 0;
		}
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(sPress && dPress)
	{
		if(lastDirection == 1)
		{
			xSpeed = speedSlow;
			ySpeed = speedRegular;
		}
		else if(lastDirection == 3)
		{
			xSpeed = speedRegular;
			ySpeed = speedSlow;
		}
		else
		{
			xSpeed = speedSlow;
			ySpeed = speedRegular;
			lastDirection = 1;
		}
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(sPress && aPress)
	{
		if(lastDirection == 1)
		{
			xSpeed = -speedSlow;
			ySpeed = speedRegular;
		}
		else if(lastDirection == 2)
		{
			xSpeed = -speedRegular;
			ySpeed = speedSlow;
		}
		else
		{
			xSpeed = -speedSlow;
			ySpeed = speedRegular;
			lastDirection = 1;
		}
		spriteAnimation(lastDirection);
		stepSound();
	}
	else if(wPress)
	{
		xSpeed = 0;
		ySpeed = -speedRegular;
		spriteAnimation(0);
		lastDirection = 0;
		stepSound();
	}
	else if(sPress)
	{
		xSpeed = 0;
		ySpeed = speedRegular;
		spriteAnimation(1);
		lastDirection = 1;
		stepSound();
	}
	else if(aPress)
	{
		xSpeed = -speedRegular;
		ySpeed = 0;
		spriteAnimation(2);
		lastDirection = 2;
		stepSound();
	}
	else if(dPress)
	{
		xSpeed = speedRegular;
		ySpeed = 0;
		spriteAnimation(3);
		lastDirection = 3;
		stepSound();
	}
	else
	{
		xSpeed = ySpeed = 0;
		standStill();
	}

	//Checks whether the player CAN move
	if(!canMoveUp && ySpeed < 0)
	{
		ySpeed = 0;
	}
	if(!canMoveDown && ySpeed > 0)
	{
		ySpeed = 0;
	}
	if(!canMoveLeft && xSpeed < 0)
	{
		xSpeed = 0;
	}
	if(!canMoveRight && xSpeed > 0)
	{
		xSpeed = 0;
	}

	//Moves sprite and adds to displacement of screen (for mouse)
	sprite.move(xSpeed, ySpeed);
	collisionRectangle.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - sprite.getGlobalBounds().height / 2);
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

void Player::dashMove(int speed)
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	bool spacePress = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(spacePress && currentTime > lastTime + dashMoveDelay)
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

