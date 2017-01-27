#include <iostream>
#include "Textbox.h"

//Default constructor
Textbox::Textbox(sf::RenderWindow& win)
{
	//Gets box parameters
	recSize = 150;
	width = win.getSize().x;
	height = recSize;
	posX = 0;
	posY = win.getSize().y - recSize; 

	//Loads fonts
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	name.setFont(font);

	//Sets character sizes
	text.setCharacterSize(35);
	name.setCharacterSize(25);

	//Sets character color
	text.setColor(sf::Color::Black);
	name.setColor(sf::Color::Black);

	//Sets position of text
	text.setPosition(sf::Vector2f(60, win.getSize().y - 100));
	name.setPosition(sf::Vector2f(20, win.getSize().y - 140));

	//Box attributes
	rec.setFillColor(sf::Color::White);
	rec.setSize(sf::Vector2f(width, height));
	rec.setPosition(sf::Vector2f(posX, posY));

	//Not opened
	open = false;

	//Initialize for animation
	textIndex = 0;
	textSpeed = 20;
	lastTime = 0;
}

//Sets the font
void Textbox::setFont(sf::String str)
{
	font.loadFromFile(str);
	text.setFont(font);
	name.setFont(font);
}

//Sets the string for text
void Textbox::setText(sf::String str)
{
	text.setString(str);
}

//Sets the for string for name
void Textbox::setName(sf::String str)
{
	name.setString(str);
}

//Sets textspeed
void Textbox::setTextSpeed(int num)
{
	textSpeed = num;
}

//Returns box (rectangle)
sf::RectangleShape Textbox::getBox()
{
	return rec;
}

//Returns text 
sf::Text Textbox::getText()
{
	return text;
}

//Returns name
sf::Text Textbox::getName()
{
	return name;
}

bool Textbox::getOpen()
{
	return open;
}

//Draws rectangle (textbox), text, and name
void Textbox::drawAll(sf::RenderWindow& win)
{
	win.draw(rec);
	win.draw(text);
	win.draw(name);
}

sf::String Textbox::convertText(sf::String str)
{
	if(str.getSize() > 40)
	{
		//Works backwards from character 40 until a space is found, and replaces it with new line
		for(int i = 40; i > 0; i--)
		{
			if(str[i] == ' ')
			{
				str[i] = '\n';
				break;
			}
		}
	}
	return str;
}

//Text doesnt appear instantly
void Textbox::animateText(sf::String str)
{
	//Converts text (for double lines)
	str = convertText(str);

	//Gets current time
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	//If the displayed text isnt the same as the str input
	if(text.getString() != str)
	{
		//Only run if the currentTime is above a certain time above lastTime
		if(currentTime > lastTime + textSpeed)
		{
			//Append a new letter
			animText += str[textIndex];
			setText(animText);

			//Set up for next
			lastTime = currentTime;
			textIndex++;
		}
	}
	else
	{
		//Resets temp string, and index
		animText = "";
		textIndex = 0;
	}
}

//Animation for box popping open
void Textbox::openBox()
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();
	if(currentTime > lastTime + 30 && width < 800)
	{
		width += 40;
		posX -= 20;
		rec.setPosition(sf::Vector2f(posX, posY));
		rec.setSize(sf::Vector2f(width, height));
		lastTime = currentTime;
	}

	if(width == 800)
	{
		open = true;
	}
}

//Animation for box closing 
void Textbox::closeBox()
{
	posX = width/2;
	width = 0;
	rec.setSize(sf::Vector2f(width, height - recSize));
}

//Wait for button press to continue to next text
void Textbox::nextText()
{
}

