#include <SFML/Graphics.hpp>

#include "MainMenu.h"

#include <iostream>

MainMenu::MainMenu()
{
	//TODO Add bgm
	
	//Defaults for button
	currentlySelected = 0;
	numButtons = 3;

	font.loadFromFile("font/Ubuntu.ttf");

	start.setFont(font);
	load.setFont(font);
	exit.setFont(font);

	start.setCharacterSize(30);
	load.setCharacterSize(30);
	exit.setCharacterSize(30);

	start.setString("Start");
	load.setString("Load");
	exit.setString("Exit");

	start.setPosition(sf::Vector2f(500, 200));
	load.setPosition(sf::Vector2f(500, 400));
	exit.setPosition(sf::Vector2f(500, 600));

	//Set color
	unselected = sf::Color(35, 83, 160);
	selected = sf::Color(96, 157, 255);

	//Set rectangle
	startButton.setSize(sf::Vector2f(400, 100));
	loadButton.setSize(sf::Vector2f(400, 100));
	exitButton.setSize(sf::Vector2f(400, 100));

	startButton.setPosition(sf::Vector2f(350, 175));
	loadButton.setPosition(sf::Vector2f(350, 375));
	exitButton.setPosition(sf::Vector2f(350, 575));
}

void MainMenu::scroll()
{
	bool wPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool sPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	if(!wPressed)
	{
		wNotPressed = true;
	}
	if(!sPressed)
	{
		sNotPressed = true;
	}

	//Scroll down
	if(wNotPressed && wPressed)
	{
		wNotPressed = false;
		currentlySelected--;
		if(currentlySelected < 0)
		{
			currentlySelected = numButtons - 1;
		}
	}

	//Scroll up
	if(sNotPressed && sPressed)
	{
		sNotPressed = false;
		currentlySelected++;
		if(currentlySelected > numButtons - 1)
		{
			currentlySelected = 0;
		}
	}
}

void MainMenu::currentlySelectedIndicate()
{
	switch (currentlySelected)
	{
		case 0:
			startButton.setFillColor(selected);
			loadButton.setFillColor(unselected);
			exitButton.setFillColor(unselected);
			break;
		case 1:
			startButton.setFillColor(unselected);
			loadButton.setFillColor(selected);
			exitButton.setFillColor(unselected);
			break;
		case 2:
			startButton.setFillColor(unselected);
			loadButton.setFillColor(unselected);
			exitButton.setFillColor(selected);
			break;
	}
}

//Returns number if selected, otherwise -1
int MainMenu::selection()
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(spacePressed)
	{
		return currentlySelected;
	}
	
	return -1;
}

void MainMenu::drawAll(sf::RenderWindow& win)
{
	win.draw(startButton);
	win.draw(loadButton);
	win.draw(exitButton);
	win.draw(start);
	win.draw(load);
	win.draw(exit);
}
