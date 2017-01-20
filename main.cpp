#include <SFML/Graphics.hpp>

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Crc Game");
	
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

		//Simple lateral, vertical, and diagonal
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

		if(left && up)
		{
			crc.setPosition(crc.getPosition().x - 1.4, crc.getPosition().y - 1.4);
		}
		else if(left && down)
		{
			crc.setPosition(crc.getPosition().x - 1.4, crc.getPosition().y + 1.4);
		}
		else if(right && up)
		{
			crc.setPosition(crc.getPosition().x + 1.4, crc.getPosition().y - 1.4);
		}
		else if(right && down)
		{
			crc.setPosition(crc.getPosition().x + 1.4, crc.getPosition().y + 1.4);
		}
		else if(left)
		{
			crc.setPosition(crc.getPosition().x - speed, crc.getPosition().y);
		}
		else if(right)
		{
			crc.setPosition(crc.getPosition().x + speed, crc.getPosition().y);
		}
		else if(up)
		{
			crc.setPosition(crc.getPosition().x, crc.getPosition().y - speed);
		}
		else if(down)
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
