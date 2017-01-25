#include <math.h>
#include <SFML/Graphics.hpp>
#include "Textbox.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	Textbox box;

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

		box.updateText("Hello");

		//Activates window for OpenGL rendering
		window.clear();

		//Draws
		//window.draw(name);
		window.draw(box.getBox());

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
