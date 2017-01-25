#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "include/Textbox.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	//Textbox instance 
	Textbox box(window);

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
		box.setText(std::to_string(time.asSeconds()));
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
