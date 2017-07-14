#include <SFML/Graphics.hpp>
#include <iostream>
#include "StatBar.h"

StatBar::StatBar()
{
	font.loadFromFile("font/Ubuntu.ttf");
	label.setFont(font);
	label.setCharacterSize(10);

	current = max = sizeX = sizeY = 0;
	labelPos = false;

	maxRect.setFillColor(sf::Color::Black);
	currentRect.setFillColor(sf::Color::Green);
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

sf::Text* StatBar::getLabel()
{
	return &label;
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

	int labelHeight = label.getGlobalBounds().height;
	int labelPadding = labelHeight / 10;

	switch(labelPos)
	{
		case 0:
			//10 is for leaving some space (not snug)
			label.setPosition(pos.x + 10, pos.y - labelHeight - labelPadding);
			break;
		case 1:
			label.setPosition(pos.x + 10, pos.y + sizeY + labelPadding);
			break;
		case 2:
			int yDisp = (labelHeight / 2) - (sizeY / 2);
			label.setPosition(pos.x + 10, pos.y + yDisp);
			break;
	}
}

void StatBar::setStats(int currentInp, int maxInp, std::string stat)
{
	current = currentInp;
	max = maxInp;

	updateSize();

	//Set string
	std::string labelInp;
	if(stat != "")
	{
		labelInp = stat + ": ";
	}
	labelInp += std::to_string(currentInp) + " / " + std::to_string(maxInp);
	label.setString(labelInp);
}

void StatBar::updateSize()
{
	float currentSizeX = (float(current) / max) * sizeX;
	currentRect.setSize(sf::Vector2f(currentSizeX, sizeY));
	maxRect.setSize(sf::Vector2f(sizeX, sizeY));
}

void StatBar::drawAll(sf::RenderWindow& win)
{
	win.draw(maxRect);
	win.draw(currentRect);
	win.draw(label);
}
