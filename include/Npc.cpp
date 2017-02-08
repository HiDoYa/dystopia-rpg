#include "Npc.h"
#include <vector>

Npc::Npc(int x, int y, sf::String nameTexture)
{
	//Gets texture of sprite
	texture.loadFromFile(nameTexture);

	//Set texture and position of sprite
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	//Sets collision rectangle
	collisionRectangle.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	collisionRectangle.setPosition(x, y);

	textNum = 0;
	openBox = false;
	closeBox = false;
}

void Npc::setTexture(sf::String nameTexture)
{
	texture.loadFromFile(nameTexture);
}

void Npc::setScale(float num)
{
	sprite.setScale(sf::Vector2f(num, num));
	collisionRectangle.setScale(sf::Vector2f(num, num));
}

void Npc::setPos(int x, int y)
{
	sprite.setPosition(x, y);
	collisionRectangle.setPosition(x, y);
}

sf::Texture Npc::getTexture()
{
	return texture;
}

sf::Sprite Npc::getSprite()
{
	return sprite;
}

void Npc::autoMove()
{
}

void Npc::moveAwayFromChar(int charPosX, int charPosY)
{
}

void Npc::moveTowardChar(int charPosX, int charPosY)
{
}

bool Npc::mouseOver(sf::Sprite mouse)
{
	if(sprite.getGlobalBounds().contains(mouse.getPosition()))
	{
		isMouseOver = true;
		return true;
	}
	else
	{
		isMouseOver = false;
		return false;
	}
}

bool Npc::getColliding(sf::Sprite spr)
{
	return collisionRectangle.getGlobalBounds().intersects(spr.getGlobalBounds());
}

bool Npc::getColliding(sf::RectangleShape rec)
{
	return collisionRectangle.getGlobalBounds().intersects(rec.getGlobalBounds());
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
void Npc::speak(sf::String nm, sf::String str, Textbox& box)
{
	if(isMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		box.convertText(str, sVec);
		if(!box.getOpen() && textNum == 0)
		{
			openBox = true;
		}
	}

	if(openBox && textNum == 0)
	{
		box.openBox();
		if(box.getOpen())
		{
			textNum = 1;
		}
	}

	for(int i = 0; i < sVec.size(); i++)
	{
		if(textNum == i + 1)
		{
			openBox = false;
			box.setName(nm);
			box.animateText(sVec[i]);
			if(box.nextText())
			{
				if(sVec.size() == textNum)
				{
					textNum = -1;
				}
				else
				{
					textNum = i + 2;
				}
			}
		}
	}

	if(textNum == -1)
	{
		closeBox = true;
	}

	if(closeBox)
	{
		box.closeBox();
		if(!box.getOpen())
		{
			closeBox = false;
		}
		textNum = 0;
	}
}

