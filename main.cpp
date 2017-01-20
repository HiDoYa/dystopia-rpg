#include <SFML/Graphics.hpp>

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test works!");
	
	//Creates green circle
	sf::CircleShape crc(100.f);
	crc.setFillColor(sf::Color::Green);
	int speed = 5;

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

		//Simple lateral and vertical movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			crc.setPosition(crc.getPosition().x - speed, crc.getPosition().y);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			crc.setPosition(crc.getPosition().x + speed, crc.getPosition().y);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			crc.setPosition(crc.getPosition().x, crc.getPosition().y - speed);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			crc.setPosition(crc.getPosition().x, crc.getPosition().y + speed);
		}
		
		//Activates window for OpenGL rendering
		window.clear();

		//Draws the circle shape
		window.draw(crc);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
