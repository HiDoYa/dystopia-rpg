#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Textbox.h"

//Default constructor
Textbox::Textbox()
{
	//Default initialization
	posX = posY = 0;
	
	//Gets box parameters
	height = 150;

	//Box attributes (box starts off closed)
	sf::Color bxColor(242, 242, 242);
	rec.setFillColor(bxColor);
	rec.setSize(sf::Vector2f(0, height));

	choiceBox.setFillColor(bxColor);
	choiceBox.setSize(sf::Vector2f(800, 200));
	curChoice.setFillColor(sf::Color::Green);
	curChoice.setSize(sf::Vector2f(800, 75));

	currentChoice = 0;
	choiceBoxOpen = false;
	oldTextSize = 0;
	displayChoiceBoxes= false;
	open = false;
	currentCompleted = false;

	//Loads fonts and styling
	font.loadFromFile("font/Ubuntu.ttf");
	text.setFont(font);
	name.setFont(font);
	name.setStyle(sf::Text::Underlined);
	nextPrompt.setFont(font);

	choiceInstruct.setFont(font);
	choiceInstruct.setStyle(sf::Text::Underlined);
	choiceOne.setFont(font);
	choiceTwo.setFont(font);


	//Sets character sizes
	text.setCharacterSize(20);
	name.setCharacterSize(12);
	nextPrompt.setCharacterSize(0);

	choiceInstruct.setCharacterSize(15);
	choiceOne.setCharacterSize(20);
	choiceTwo.setCharacterSize(20);


	//Load Music
	mu.openFromFile("sound/textNoise.wav");

	//Sets character color
	sf::Color txtColor(109, 109, 109);
	text.setColor(txtColor);
	name.setColor(txtColor);

	choiceInstruct.setColor(txtColor);
	choiceOne.setColor(txtColor);
	choiceTwo.setColor(txtColor);

	nextPrompt.setColor(txtColor);

	//Time management for opening/closing box
	delayBoxSetup = 30;
	currentTime = 0;
	lastTimeBox = 0;

	//To skip text
	lastNotPressed = false;
	lastTimeSkip = 0;

	//Initialize for animation
	textIndex = 0;
	textNum = 0;
	textSpeed = 20;
	lastTimeLetter = 0;

	//Choice Instruction is always the same
	choiceInstruct.setString("Choose an option.");
	nextPrompt.setString("Press spacebar to continue...");
}

//*********** ACCESSORS *************
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

//********* MUTATORS *********
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

//********** UTILITY *************
void Textbox::updatePosition(sf::View view)
{
	posX = view.getCenter().x - (view.getSize().x / 2);
	posY = view.getCenter().y + (view.getSize().y / 2) - height; 

	text.setPosition(sf::Vector2f(posX + 30, posY + 50));
	name.setPosition(sf::Vector2f(posX + 20, posY + 20));
	nextPrompt.setPosition(sf::Vector2f(posX + 701, posY + 120));

	//TODO 
	choiceBox.setPosition(sf::Vector2f(posX + 150, posY - 300));
	choiceOne.setPosition(sf::Vector2f(posX + 150, posY - 250));
	choiceTwo.setPosition(sf::Vector2f(posX + 150, posY - 150));

	rec.setPosition(sf::Vector2f(posX, posY));

	//TODO Sets the position of box 
	if(currentChoice == 0)
	{
		curChoice.setPosition(sf::Vector2f(posX + 150, posY - 225));
	}
	else if(currentChoice == 1)
	{
		curChoice.setPosition(sf::Vector2f(posX + 150, posY - 175));
	}
}

//TODO
void Textbox::readFromScript(std::string inpFile)
{
	std::ifstream scriptFile(inpFile);
	//script.get(i);
}

//Draws rectangle (textbox), text, and name
void Textbox::drawAll(sf::RenderWindow& win)
{
	win.draw(rec);
	if(displayChoiceBoxes)
	{
		win.draw(choiceBox);
		win.draw(curChoice);
		win.draw(choiceInstruct);
		win.draw(choiceOne);
		win.draw(choiceTwo);
	}
	win.draw(text);
	win.draw(name);
	win.draw(nextPrompt);
}

//********** PRETEXT ***********
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

//Animation for box popping open
void Textbox::openBox()
{
	open = true;
	rec.setSize(sf::Vector2f(1024, height));
}

//********* DURING TEXT **************
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
		nextPrompt.setCharacterSize(13);

		animText = "";
		textIndex = 0;
	}
}

bool Textbox::textHandler(sf::String nm, sf::String str, bool condition, bool& currentlyTalking)
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(condition && textNum == 0 && lastTimeBox + 350 < currentTime)
	{
		openBox();
		textNum = 1;
		currentlyTalking = true;
		convertText(str, sVec);
	}

	for(int i = 0; i < sVec.size(); i++)
	{
		if(textNum == i + 1)
		{
			setName(nm);
			animateText(sVec[i]);

			if(nextText())
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
		closeBox();
		textNum = 0;
		currentlyTalking = false;
		//Used to change event vector at end of text
		return true;
	}
	return false;
}

//Return 0 if choiceBox isn't done yet.
//Returns 1 or 2 if choiceBox is done and indicates which choice the user chose
int Textbox::choiceBoxDisp(std::string nm, std::string textStr, std::string regInp, std::string strOne, std::string strTwo, std::string choiceOneDisp, std::string choiceTwoDisp, bool condition, bool& currentlyTalking)
{
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(condition && textNum == 0 && lastTimeBox + 350 < currentTime)
	{
		choiceBoxOpen = true;
		openBox();
		textNum = 1;
		currentlyTalking = true;
		convertText(textStr, sVec);
		oldTextSize = sVec.size();
	}

	for(int i = 0; i < sVec.size(); i++)
	{
		if(textNum == i + 1)
		{
			setName(nm);
			animateText(sVec[i]);

			if(nextText())
			{
				if(sVec.size() == textNum)
				{
					textNum++;
				}
				else
				{
					textNum = i + 2;
				}
			}
		}
	}

	if(textNum == sVec.size() + 1)
	{
		animateText(regInp);
		if(currentCompleted)
		{
			displayChoiceBoxes = true;
			choiceOne.setString(strOne);
			choiceTwo.setString(strTwo);
			makeChoice();
		}
		if(nextText())
		{
			displayChoiceBoxes = false;
			textNum = sVec.size() + 2;
			if(currentChoice == 0)
			{
				convertText(choiceOneDisp, sVec);
			}
			else if(currentChoice == 1)
			{
				convertText(choiceTwoDisp, sVec);
			}
		}
	}

	//New zero keeps track of what number "textNum" is at 
	int newZero = oldTextSize + 1;

	for(int i = newZero; i < sVec.size() + newZero; i++)
	{
		if(textNum == i + 1)
		{
			setName(nm);
			animateText(sVec[i - newZero]);

			if(nextText())
			{
				if(sVec.size() + newZero == textNum)
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
		closeBox();
		currentChoice = 0;
		choiceBoxOpen = false;
		currentlyTalking = false;
		textNum = 0;
		return currentChoice;
	}
	return 0;
}

void Textbox::makeChoice()
{
	bool sPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool wPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	//To change current selection
	if(sPressed && currentChoice == 0)
	{
		currentChoice = 1;
	}
	else if(wPressed && currentChoice == 1)
	{
		currentChoice = 0;
	}

}

//************* POST TEXT *****************
//Animation for box closing 
void Textbox::closeBox()
{
	time = clock.getElapsedTime();
	lastTimeBox = time.asMilliseconds();
	text.setString("");
	name.setString("");
	open = false;
	rec.setSize(sf::Vector2f(0, height));
}

//Wait for button press to continue to next text (sub text at bottom that blinks. Asks for player to click to continue)
bool Textbox::nextText()
{
	int textDelay;
	if(displayChoiceBoxes)
	{
		//Choice text
		textDelay = 500;
	}
	else
	{
		//Reg text
		textDelay = 200;
	}

	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentCompleted && (lastTimeSkip + textDelay < currentTime))
	{
		nextPrompt.setCharacterSize(0);
		lastNotPressed = false;
		lastTimeSkip = currentTime;
		return true;
	}
	return false;
}


