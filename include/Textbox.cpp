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
	//rec.setSize(sf::Vector2f(window.getSize().x, window.getSize().y - (window.getSize().y - recSize)));
	//rec.setPosition(sf::Vector2f(0, window.getSize().y - recSize));
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

void Textbox::openBox()
{
}

void Textbox::closeBox()
{
}

void Textbox::nextText()
{
	//Wait for button press to continue to next text
}


