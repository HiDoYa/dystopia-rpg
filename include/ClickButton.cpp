#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "ClickButton.h"

ClickButton::ClickButton()
{
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	type = 0;
}

ClickButton::ClickButton(int inp)
{
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	type = inp;
}

void ClickButton::setType(int inp)
{
	type = inp;
}

sf::Text* ClickButton::getText()
{
	return &text;
}

sf::RectangleShape* ClickButton::getRect()
{
	return &rect;
}

sf::CircleShape* ClickButton::getCirc()
{
	return &circ;
}

void ClickButton::centerText()
{
	int wrapperLeft, wrapperTop, wrapperWidth, wrapperHeight, textWidth, textHeight, xDisp, yDisp;
	
	if(type == 0)
	{
		wrapperLeft = rect.getGlobalBounds().left;
		wrapperTop = rect.getGlobalBounds().top;
		wrapperWidth = rect.getGlobalBounds().width;
		wrapperHeight = rect.getGlobalBounds().height;
	}
	else if(type == 1)
	{
		wrapperLeft = circ.getGlobalBounds().left;
		wrapperTop = circ.getGlobalBounds().top;
		wrapperWidth = circ.getGlobalBounds().width;
		wrapperHeight = circ.getGlobalBounds().height;
	}

	textWidth = text.getGlobalBounds().width;
	textHeight = text.getGlobalBounds().height;

	xDisp = ((wrapperWidth - textWidth) / 2) + wrapperLeft;
	yDisp = ((wrapperHeight - textHeight) / 2) + wrapperTop;

	text.setPosition(xDisp, yDisp);
}

bool ClickButton::mouseInButton(sf::Color col1, sf::Color col2, sf::RenderWindow& win)
{
	sf::Vector2i mouseCoords = sf::Mouse::getPosition(win);

	if(type == 0)
	{
		int startX = rect.getPosition().x;
		int endX = rect.getPosition().x + rect.getSize().x;
		int startY = rect.getPosition().y;
		int endY = rect.getPosition().y + rect.getSize().y;

		if(mouseCoords.x >= startX && mouseCoords.x <= endX &&
		   mouseCoords.y >= startY && mouseCoords.y <= endY)
		{
			rect.setFillColor(col1);
			return true;
		}

		rect.setFillColor(col2);
	}
	else if(type == 1)
	{
		float rad = circ.getRadius();
		float posX = circ.getPosition().x + rad;
		float posY = circ.getPosition().y + rad;

		float diffX = posX - mouseCoords.x;
		float diffY = posY - mouseCoords.y;

		if(sqrt(diffX * diffX + diffY * diffY) < rad)
		{
			circ.setFillColor(col1);
			return true;
		}

		circ.setFillColor(col2);
	}

	return false;
}

bool ClickButton::mouseInButton(std::string texture1, std::string texture2, sf::RenderWindow& win)
{
	sf::Vector2i mouseCoords = sf::Mouse::getPosition(win);

	if(type == 0)
	{
		int startX = rect.getPosition().x;
		int endX = rect.getPosition().x + rect.getSize().x;
		int startY = rect.getPosition().y;
		int endY = rect.getPosition().y + rect.getSize().y;

		if(mouseCoords.x >= startX && mouseCoords.x <= endX &&
		   mouseCoords.y >= startY && mouseCoords.y <= endY)
		{
			texture.loadFromFile(texture1);
			rect.setTexture(texture);
			return true;
		}
		texture.loadFromFile(texture2);
		rect.setTexture(texture);
	}
	else if(type == 1)
	{
		float rad = circ.getRadius();
		float posX = circ.getPosition().x + rad;
		float posY = circ.getPosition().y + rad;

		float diffX = posX - mouseCoords.x;
		float diffY = posY - mouseCoords.y;

		if(sqrt(diffX * diffX + diffY * diffY) < rad)
		{
			texture.loadFromFile(texture1);
			circ.setTexture(texture);
			return true;
		}

		texture.loadFromFile(texture2);
		circ.setTexture(texture);
	}

	return false;
}

bool ClickButton::mouseClickedInButton(sf::Color col1, sf::Color col2, sf::RenderWindow& win)
{
	bool mouseInside = mouseInButton(col1, col2, win);
	bool mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if(mouseInside && mouseClicked)
	{
		return true;
	}

	return false;
}

bool ClickButton::mouseClickedInButton(std::string texture1, std::string texture2, sf::RenderWindow& win)
{
	bool mouseInside = mouseInButton(texture1, texture2, win);
	bool mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if(mouseInside && mouseClicked)
	{
		return true;
	}

	return false;
}

void ClickButton::drawAll(sf::RenderWindow& win)
{
	if(type == 0)
	{
		win.draw(rect);
	}
	else if(type == 1)
	{
		win.draw(circ);
	}
	win.draw(text);
}
