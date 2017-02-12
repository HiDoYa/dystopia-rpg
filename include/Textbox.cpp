#include <iostream>
#include <string>
#include <vector>
#include "Textbox.h"

//Default constructor
Textbox::Textbox(sf::View& view)
{
	//Gets box parameters
	width = 0;
	height = 150;

	//Box attributes (box starts off closed)
	sf::Color bxColor(242, 242, 242);
	rec.setFillColor(bxColor);
	rec.setSize(sf::Vector2f(width, height));
	open = false;

	//Loads fonts and styling
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	name.setFont(font);
	nextPrompt.setFont(font);
	name.setStyle(sf::Text::Underlined);

	//Sets character sizes
	text.setCharacterSize(35);
	name.setCharacterSize(25);
	nextPrompt.setCharacterSize(0);

	//Load Music
	mu.openFromFile("sound/textNoise.wav");

	//Sets character color
	sf::Color txtColor(109, 109, 109);
	text.setColor(txtColor);
	name.setColor(txtColor);
	nextPrompt.setColor(txtColor);

	//Next propmt is always the same
	nextPrompt.setString("Press spacebar to continue...");

	//Time management for opening/closing box
	delayBoxSetup = 30;
	lastTimeBox = 0;

	//To skip text
	lastNotPressed = false;
	lastTimeSkip = 0;

	//Initialize for animation
	textIndex = 0;
	textSpeed = 20;
	lastTimeLetter = 0;
}

//Sets the font (for different characters)
void Textbox::setFont(sf::String str)
{
	font.loadFromFile(str);
	text.setFont(font);
	name.setFont(font);
	nextPrompt.setFont(font);
}

//Sets the for string for name
void Textbox::setName(sf::String str)
{
	name.setString(str);
}

//Sets the string for text
void Textbox::setText(sf::String str)
{
	text.setString(str);
}

//Sets textspeed
void Textbox::setTextSpeed(int num)
{
	textSpeed = num;
}

void Textbox::updatePosition(sf::View view)
{
	posX = view.getCenter().x - (view.getSize().x / 2);
	posY = view.getCenter().y + (view.getSize().y / 2) - height; 

	text.setPosition(sf::Vector2f(posX + 50, posY + 40));
	name.setPosition(sf::Vector2f(posX + 20, posY + 10));
	nextPrompt.setPosition(sf::Vector2f(posX + 700, posY + 120));
	rec.setPosition(sf::Vector2f(posX, posY));
}

//Returns name
sf::Text Textbox::getName()
{
	return name;
}

//Returns text 
sf::Text Textbox::getText()
{
	return text;
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
	win.draw(nextPrompt);
}

//This is the hardest thing I've ever coded wtf.
//Converts text into vector of strings to output in textbox
void Textbox::convertText(std::string str, std::vector<std::string>& sVec)
{
	//Length of text for each line
	int textLen = 40;
	float fullTextLen = textLen * 2;

	//Resets old content
	sVec.clear();

	//There must be a space at the end (due to the nature of my algorithm)
	str.push_back(' ');

	//Gets num of strings that will be required
	int numOfStrings = 0.9 + (str.length() / fullTextLen);

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
		int textToTest = fullTextLen * (i + 1);

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
	//If the displayed text isnt the same as the str input
	if(text.getString() != str)
	{
		//Gets current time
		time = clock.getElapsedTime();
		currentTime = time.asMilliseconds();

		//Current text is not yet completed
		currentCompleted = false;
		//Only run if the currentTime is above a certain time above lastTimeLetter
		if(currentTime > lastTimeLetter + textSpeed)
		{
			//Append a new letter
			animText += str[textIndex];
			setText(animText);

			//Play sound
			mu.play();

			//Set up for next
			lastTimeLetter = currentTime;
			textIndex++;
		}

		//TO SKIP TEXT
		//Press spacebar to skip. 
		if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (currentTime > lastTimeSkip + 100))
		{
			lastNotPressed = true;
		}
		if(lastNotPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			setText(str);
			lastNotPressed = false;
			lastTimeSkip = currentTime;
		}
	}
	else
	{
		//Says the current text has completed
		currentCompleted = true;

		//Resets temp string, and index
		nextPrompt.setCharacterSize(20);
		animText = "";
		textIndex = 0;
	}
}

//Animation for box popping open
void Textbox::openBox()
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();
	if(currentTime > lastTimeBox + delayBoxSetup && width < 1024)
	{
		width += 64;
		rec.setPosition(sf::Vector2f(posX, posY));
		rec.setSize(sf::Vector2f(width, height));
		lastTimeBox = currentTime;
	}

	if(width >= 1024)
	{
		open = true;
	}
}

//Animation for box closing 
void Textbox::closeBox()
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();
	text.setString("");
	name.setString("");
	if(currentTime > lastTimeBox + delayBoxSetup && width > 0)
	{
		width -= 64;
		rec.setPosition(sf::Vector2f(posX, posY));
		rec.setSize(sf::Vector2f(width, height));
		lastTimeBox = currentTime;
	}

	if(width == 0)
	{
		open = false;
	}
}

//Wait for button press to continue to next text (sub text at bottom that blinks. Asks for player to click to continue)
bool Textbox::nextText()
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(open && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentCompleted && (lastTimeSkip + 200 < currentTime))
	{
		nextPrompt.setCharacterSize(0);
		lastNotPressed = false;
		lastTimeSkip = currentTime;
		return true;
	}
	return false;
}

