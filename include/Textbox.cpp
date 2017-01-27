#include <iostream>
#include "Textbox.h"

//Default constructor
Textbox::Textbox(sf::RenderWindow& win)
{
	//Gets width and height of window
	int width = win.getSize().x;
	int height = win.getSize().y;

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
	text.setPosition(sf::Vector2f(60, height - 100));
	name.setPosition(sf::Vector2f(20, height - 140));

	//Box attributes
	recSize = 150;
	rec.setFillColor(sf::Color::White);
	rec.setSize(sf::Vector2f(width, height - recSize));
	rec.setPosition(sf::Vector2f(0, height - recSize));

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

//Draws rectangle (textbox), text, and name
void Textbox::drawAll(sf::RenderWindow& win)
{
	win.draw(rec);
	win.draw(text);
	win.draw(name);
}

//Text doesnt appear instantly
void Textbox::animateText(sf::String str)
{
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
}

//Animation for box closing 
void Textbox::closeBox()
{
}

//Wait for button press to continue to next text
void Textbox::nextText()
{
}

