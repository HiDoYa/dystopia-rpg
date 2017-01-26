#include "Textbox.h"

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
}

void Textbox::setFont(sf::String str)
{
	font.loadFromFile(str);
	text.setFont(font);
	name.setFont(font);
}

void Textbox::setText(sf::String str)
{
	text.setString(str);
}

void Textbox::setName(sf::String str)
{
	name.setString(str);
}

void Textbox::setRecSize(int num)
{
	recSize = num;
}

void Textbox::setTextSpeed(double num)
{
	textSpeed = num;
}

sf::RectangleShape Textbox::getBox()
{
	return rec;
}

sf::Text Textbox::getText()
{
	return text;
}

sf::Text Textbox::getName()
{
	return name;
}

void Textbox::drawAll(sf::RenderWindow& win)
{
	win.draw(rec);
	win.draw(text);
	win.draw(name);
}

void Textbox::animateText()
{
	//Text doesnt appear instantly
}

void Textbox::openBox()
{
	//Animation for box popping open
}

void Textbox::closeBox()
{
	//Animation for box closing 
}

void Textbox::nextText()
{
	//Wait for button press to continue to next text
}

