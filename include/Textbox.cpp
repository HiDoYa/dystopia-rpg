#include <iostream>
#include "Textbox.h"

//Default constructor
Textbox::Textbox(sf::RenderWindow& win)
{
	//Gets box parameters
	recSize = 150;
	//width = win.getSize().x;
	width = 0;
	height = recSize;
	//posX = 0;
	posX = win.getSize().x / 2;
	posY = win.getSize().y - recSize; 

	//Loads fonts
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	name.setFont(font);
	nextPrompt.setFont(font);
	name.setStyle(sf::Text::Underlined);

	//Load Music
	mu.openFromFile("sound/textNoise.wav");

	//Sets character sizes
	text.setCharacterSize(35);
	name.setCharacterSize(25);
	nextPrompt.setCharacterSize(0);

	//Sets character color
	sf::Color txtColor(109, 109, 109);
	text.setColor(txtColor);
	name.setColor(txtColor);
	nextPrompt.setColor(txtColor);

	//Updates position
	updatePosition();

	//Next propmt is always the same
	nextPrompt.setString("Click to continue...");

	//Box attributes
	sf::Color bxColor(242, 242, 242);
	rec.setFillColor(bxColor);
	rec.setSize(sf::Vector2f(width, height));

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
	nextPrompt.setFont(font);
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

bool Textbox::setSuccess()
{
	success = false;
}

void Textbox::setPosition(int x, int y)
{
	posX += x;
	posY += y;
	updatePosition();
}

void Textbox::updatePosition()
{
	text.setPosition(sf::Vector2f(60, posY + 50));
	name.setPosition(sf::Vector2f(20, posY + 10));
	nextPrompt.setPosition(sf::Vector2f(600, posY + 130));
	rec.setPosition(sf::Vector2f(posX, posY));
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

bool Textbox::getSuccess()
{
	return success;
}

//Draws rectangle (textbox), text, and name
void Textbox::drawAll(sf::RenderWindow& win)
{
	win.draw(rec);
	win.draw(text);
	win.draw(name);
	win.draw(nextPrompt);
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

			//Play sound
			mu.play();

			//Set up for next
			lastTime = currentTime;
			textIndex++;
		}
	}
	else
	{
		//Resets temp string, and index
		nextPrompt.setCharacterSize(15);
		animText = "";
		textIndex = 0;
		success = true;
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

	if(width >= 800)
	{
		open = true;
	}
}

//Animation for box closing 
void Textbox::closeBox()
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();
	text.setString("");
	name.setString("");
	if(currentTime > lastTime + 30 && width > 0)
	{
		width -= 40;
		posX += 20;
		rec.setPosition(sf::Vector2f(posX, posY));
		rec.setSize(sf::Vector2f(width, height));
		lastTime = currentTime;
	}

	if(width == 0)
	{
		open = false;
	}
}

//Wait for button press to continue to next text (sub text at bottom that blinks. Asks for player to click to continue)
bool Textbox::nextText()
{
	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();
	if(success && open && sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastTime + 300 < currentTime)
	{
		lastTime = currentTime;
		std::cout << "Button pressed" << std::endl;
		nextPrompt.setCharacterSize(0);
		return true;
	}
	return false;
}

