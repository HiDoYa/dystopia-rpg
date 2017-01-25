#include <math.h>
#include <SFML/Graphics.hpp>
#include "include/Textbox.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	Textbox box(window);

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

		box.setText("Hello");
		box.setName("Name");

		//Activates window for OpenGL rendering
		window.clear();

		//Draws
		//window.draw(name);
		box.drawAll(window);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
