#include <SFML/Graphics.hpp>
#include <iostream>
#include "StatBar.h"

StatBar::StatBar()
{
	font.loadFromFile("font/Ubuntu.ttf");
	label.setFont(font);
	current = max = sizeX = sizeY = 0;
	labelUse = false;
	labelPos = false;
}

void StatBar::setLabelUse(bool inp)
{
	labelUse = inp;
}

void StatBar::setLabelPos(int inp)
{
	labelPos = inp;
}

void StatBar::setLabelSize(int inp)
{
	label.setCharacterSize(inp);
}

sf::RectangleShape* StatBar::getCurrentRect()
{
	return &currentRect;
}

sf::RectangleShape* StatBar::getMaxRect()
{
	return &maxRect;
}

sf::Text

{
	return &currentRect;
}

void StatBar::setMaxSize(sf::Vector2f size)
{
	sizeX = size.x;
	sizeY = size.y;

	currentRect.setSize(size);
	maxRect.setSize(size);
}

void StatBar::setPosition(sf::Vector2f pos)
{
	currentRect.setPosition(pos);
	maxRect.setPosition(pos);
	if(labelUse)
	{
		switch(labelPos)
		{
			case 0:
				int labelHeight = label.getGlobalBounds().height;
				//10 is for leaving some space (not snug)
				label.setPosition(pos.x + 10, pos.y - height - 10);
				break;
			case 1:
				label.setPosition(pos.x + 10, pos.y + sizeY + 10);
				break;
			case 2:
				int labelHeight = label.getGlobalBounds().height;
				int yDisp = (labelHeight / 2) - (sizeY / 2);
				label.setPosition(pos.x + 10, pos.y + yDisp);
				break;
		}
	}
}

void StatBar::setStats(int currentInp, int maxInp)
{
	current = currentInp;
	max = maxInp;
	updateSize();
}

void Statbar::updateSize()
{
	float currentSizeX = (float(current) / max) * sizeX;
	currentRect.setSize(sf::Vector2f(currentSizeX, sizeY));
	maxRect.setSize(sf::Vector2f(sizeX, sizeY));
}

void StatBar::drawAll(sf::RenderWindow& win)
{
	win.draw(maxRect);
	win.draw(currentRect);

	if(labelUse)
	{
		win.draw(label);
	}
}
