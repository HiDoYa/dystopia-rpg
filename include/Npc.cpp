#include "Npc.h"

Npc::Npc(int x, int y, sf::String nameTexture)
{
	//Gets texture of sprite
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}

	//Set texture and position of sprite
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	//Sets collision rectangle
	collisionRectangle.setSize(sprite.getScale());

	textNum = 0;
	openBox = false;
	closeBox = false;
}

void Npc::setTexture(sf::String nameTexture)
{
	if(!texture.loadFromFile(nameTexture))
	{
		std::cout << "Error loading file";
	}
}

void Npc::setScale(double num)
{
	sprite.setScale(sf::Vector2f(num, num));
	collisionRectangle.setSize(sprite.getScale());
}

void Npc::setPos(int x, int y)
{
	sprite.setPosition(x, y);
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

bool Npc::mouseOver(sf::Sprite& mouse, sf::Texture& textureAction, sf::Texture& textureDefault)
{
	if(sprite.getGlobalBounds().contains(mouse.getPosition()))
	{
		mouse.setTexture(textureAction);
		isMouseOver = true;
		return true;
	}
	else
	{
		mouse.setTexture(textureDefault);
		isMouseOver = false;
		return false;
	}
}

bool Npc::getColliding(sf::Sprite spr)
{
	return sprite.getGlobalBounds().intersects(spr.getGlobalBounds());
}

bool Npc::getColliding(sf::RectangleShape rec)
{
	return sprite.getGlobalBounds().intersects(rec.getGlobalBounds());
}

void Npc::speak(sf::String nm, sf::String str, Textbox& box)
{
	//if mouse pressed and char is within certain range of posX, posY, talk
	//TODO if str is larger than 80, split it into 2 parts, etc
	//Setting the text
	if(isMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
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

	if(textNum == 1)
	{
		openBox = false;
		box.setName(nm);
		box.animateText(str);
		if(box.nextText())
		{
			textNum = 2;
		}
	}
	if(textNum == 2)
	{
		box.setName(nm);
		box.animateText("Here I am");

		if(box.nextText())
		{
			textNum = 3;
		}
	}
	if(textNum == 3)
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

