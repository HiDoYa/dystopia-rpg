#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "include/Npc.h"
#include "include/Textbox.h"
#include <iostream>

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	//Instance Tests 
	Textbox box(window);
	Npc kitty(20, 20, "images/hello.jpeg");
	kitty.setScale(0.3);

	//Time
	sf::Clock clock;
	sf::Time time;

	//Sets framerate to 30fps
	window.setFramerateLimit(30);

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

		time = clock.getElapsedTime();
		time.asSeconds();

		//Setting the text
		box.setText("Text");
		box.setName("Name");

		//Activates window for OpenGL rendering
		window.clear();

		//window.draw();
		window.draw(kitty.getSprite());
		box.drawAll(window);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
