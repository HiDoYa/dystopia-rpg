#include "Textbox.h"

Textbox::Textbox()
{
	//Loads fonts
	font.loadFromFile("../font/Ubuntu.ttf");
	text.setFont(font);
	name.setFont(font);

	//Sets character sizes
	text.setCharacterSize(35);
	name.setCharacterSize(30);

	//Sets character color
	text.setColor(sf::Color::Black);
	name.setColor(sf::Color::Black);

	//Sets position of text
	text.setPosition(sf::Vector2f(20, 500));
	name.setPosition(sf::Vector2f(10, 450));

	//Box attributes
	recSize = 150;
	rec.setFillColor(sf::Color::White);
	rec.setSize(sf::Vector2f(800, 150));
	rec.setPosition(sf::Vector2f(0, 450));
	//rec.setSize(sf::Vector2f(window.getSize().x, window.getSize().y - (window.getSize().y - recSize)));
	//rec.setPosition(sf::Vector2f(0, window.getSize().y - recSize));
}

void Textbox::setFont(sf::String str)
{
	font.loadFromFile(str);
	text.setFont(font);
	name.setFont(font);
}

void Textbox::setFontSize(int num)
{
}

void Textbox::setName(sf::String str)
{
}

void Textbox::openBox()
{
}

void Textbox::closeBox()
{
}

void Textbox::updateText(sf::String str)
{
	text.setString(str);
}

void Textbox::nextText()
{
	//Wait for button press to continue to next text
}

sf::RectangleShape Textbox::getBox()
{
	return rec;
}

void Textbox::getText()
{
}
