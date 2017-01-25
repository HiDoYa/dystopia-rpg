#include <math.h>
#include <SFML/Graphics.hpp>

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Crc Game");
	
	//Creates green circle
	sf::RectangleShape rec;
	int recSize = 150;
	rec.setFillColor(sf::Color::White);
	rec.setSize(sf::Vector2f(window.getSize().x, window.getSize().y - (window.getSize().y - recSize)));
	rec.setPosition(sf::Vector2f(0, window.getSize().y - recSize));

	sf::Font font;
	font.loadFromFile("Ubuntu.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(35);
	text.setColor(sf::Color::Red);
	text.setString("Main text goes here");
	text.setPosition(sf::Vector2f(20, window.getSize().y - 100));

	sf::Text name;
	name.setFont(font);
	name.setCharacterSize(20);
	name.setColor(sf::Color::Red);
	name.setString("Name");
	name.setPosition(sf::Vector2f(5, window.getSize().y - 150));
	


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
		//TODO Here

		//Activates window for OpenGL rendering
		window.clear();

		//TODO Drawing
		//window.draw();
		window.draw(rec);
		window.draw(text);
		window.draw(name);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
