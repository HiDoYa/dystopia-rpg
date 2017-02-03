#include <iostream>
#include <string>
#include <vector>
#include "Textbox.h"

//Default constructor
Textbox::Textbox(sf::RenderWindow& win)
{
	//Gets box parameters
	width = 0;
	height = 150;
	posX = 0;
	posY = win.getSize().y - height; 

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
	nextPrompt.setString("Click to continue.");

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
	posX = x;
	posY = y + 570;
	updatePosition();
}

void Textbox::updatePosition()
{
	text.setPosition(sf::Vector2f(posX + 50, posY + 40));
	name.setPosition(sf::Vector2f(posX + 20, posY + 10));
	nextPrompt.setPosition(sf::Vector2f(posX + 1100, posY + 120));
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

//This is the hardest thing I've ever coded wtf.
//Converts text into vector of strings to output in textbox
void Textbox::convertText(std::string str, std::vector<std::string>& sVec)
{
	//Length of text for each line
	int textLen = 55;
	float doubleTextLen = textLen * 2;

	//Resets old content
	sVec.clear();

	//There must be a space at the end (due to the nature of my algorithm)
	str.push_back(' ');

	//Gets num of strings that will be required
	int numOfStrings = 0.9 + (str.length() / doubleTextLen);

	//maxNdx is used to make sure the loop doesn't check contents that are outside the string's memory
	int maxNdx = str.length() - 1;

	//Lastndx used for the text that is used in the last (previous) textbox
	int lastNdx = 0;

	//Loop separates each 120 chars into a diff array in sPtr
	for(int i = 0; i < numOfStrings; i++)
	{
		//Adds a string to the vector
		sVec.push_back("");

		//Text to test is dependent on how large each vector should be and the current loop
		int textToTest = doubleTextLen * (i + 1);

		//Makes sure the text to test is less than the maximum index
		if(textToTest > maxNdx)
		{
			textToTest = maxNdx;
		}

		//Starts at textToTest index and works backwards, checking for a space
		for(int text = textToTest; text > lastNdx; text--)
		{
			//When running into a space, that is the cut off point for the string
			if(str[text] == ' ')
			{
				//Adds all the of the string from the last index (the previous cut off) and the new cut off
				for(int currentText = lastNdx; currentText < text; currentText++)
				{
					sVec[i].push_back(str[currentText]);
				}

				//Adds a null terminator
				sVec[i].push_back('\0');

				//Sets lastNdx to the current index plus one
				lastNdx = text + 1;
				break;
			}
		}
	}

	//Split each box into 2 lines (if above 55 lines)
	for(int strNum = 0; strNum < numOfStrings; strNum++)
	{
		//If the string in the vector is larger than the maximum length per line
		if(sVec[strNum].length() > textLen)
		{
			//Works backwards from character 40 until a space is found, and replaces it with new line
			for(int i = textLen; i > 0; i--)
			{
				//If it finds a space, it is the cut off point
				if(sVec[strNum][i] == ' ')
				{
					//Inserts a carriage return to split the string into two parts  
					sVec[strNum][i] = '\n';
					break;
				}
			}
		}
	}
}
//Text doesnt appear instantly
void Textbox::animateText(std::string str)
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
		nextPrompt.setCharacterSize(20);
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
	if(currentTime > lastTime + 30 && width < 1280)
	{
		width += 80;
		rec.setPosition(sf::Vector2f(posX, posY));
		rec.setSize(sf::Vector2f(width, height));
		lastTime = currentTime;
	}

	if(width >= 1280)
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
		width -= 80;
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
		nextPrompt.setCharacterSize(0);
		return true;
	}
	return false;
}

