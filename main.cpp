#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

//Game classes
#include "include/Npc.h"
#include "include/Player.h"
#include "include/Textbox.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();


	//Image as cursor
	window.setMouseCursorVisible(false);
	sf::Texture cursorTexture;
	cursorTexture.loadFromFile("images/cursor.png");
	sf::Sprite cursorSprite(cursorTexture);
	cursorSprite.setScale(sf::Vector2f(0.05, 0.05));


	//Instance Tests 
	Textbox box(window);

	Npc kitty(20, 20, "images/hello.jpeg");
	kitty.setScale(0.2);

	Player chr(300, 250, "images/penguin.png");
	chr.setScale(0.06);

	int scene = 0;

	//Time
	sf::Clock clock;
	sf::Time time;

	//Sets framerate to 60fps
	window.setFramerateLimit(60);

	//Main loop - ends when window is closed
	while(window.isOpen())
	{
		//Event Processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Request for closing the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Setting the text
		if(!box.getOpen() && scene == 0)
		{
			box.openBox();
			if(box.getOpen())
			{
				scene = 1;
			}
		}
		if(scene == 1)
		{
			box.setName("Somebody");
			box.animateText("hello, this is a test for the text box. asdf asdf filler filler.");
			if(box.nextText())
			{
				scene = 2;
			}
		}
		if(scene == 2)
		{
			box.setName("Somebody else");
			box.animateText("This is somebody else speaking. Hi");

			if(box.nextText())
			{
				scene = 3;
			}
		}
		if(scene == 3)
		{
			box.closeBox();
		}


		chr.movePos(10);

		//Cursor position
		cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		//Activates window for OpenGL rendering
		sf::Color winColor(107, 120, 140);
		window.clear(winColor);

		//Sets view
		window.setView(view);

		//window.draw();
		window.draw(kitty.getSprite());
		window.draw(chr.getSprite());
		box.drawAll(window);
		window.draw(cursorSprite);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
