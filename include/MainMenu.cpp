#include <SFML/Graphics.hpp>

#include "MainMenu.h"

MainMenu::MainMenu()
{
	//TODO Add bgm
	
	//Set color
	unselected = sf::Color(35, 83, 160);
	selected = sf::Color(96, 157, 255);

	//Set rectangle
	startButton.getRect()->setSize(sf::Vector2f(400, 100));
	loadButton.getRect()->setSize(sf::Vector2f(400, 100));
	exitButton.getRect()->setSize(sf::Vector2f(400, 100));

	startButton.getRect()->setPosition(sf::Vector2f(330, 175));
	loadButton.getRect()->setPosition(sf::Vector2f(330, 375));
	exitButton.getRect()->setPosition(sf::Vector2f(330, 575));

	//Set text
	startButton.getText()->setCharacterSize(30);
	loadButton.getText()->setCharacterSize(30);
	exitButton.getText()->setCharacterSize(30);

	startButton.getText()->setString("Start");
	loadButton.getText()->setString("Load");
	exitButton.getText()->setString("Exit");

	startButton.centerText();
	loadButton.centerText();
	exitButton.centerText();
}

int MainMenu::clickCheck(sf::RenderWindow& win)
{
	bool start = startButton.mouseClickedInButton(selected, unselected, win);
	bool load = loadButton.mouseClickedInButton(selected, unselected, win);
	bool exit = exitButton.mouseClickedInButton(selected, unselected, win);

	if(start)
	{
		return 0;
	}
	else if(load)
	{
		return 1;
	}
	else if(exit)
	{
		return 2;
	}

	return -1;
}

void MainMenu::drawAll(sf::RenderWindow& win)
{
	drawSprite(win);

	startButton.drawAll(win);
	loadButton.drawAll(win);
	exitButton.drawAll(win);
}
