#include <cmath>
#include <string>
#include <iostream>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//Game classes
#include "include/Textbox.h"
#include "include/Npc.h"
#include "include/Player.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();

	//Image as cursor
	window.setMouseCursorVisible(false);
	sf::Texture cursorTextureDefault, cursorTextureTalk;
	cursorTextureDefault.loadFromFile("images/cursor.png");
	cursorTextureTalk.loadFromFile("images/cursorTalk.png");
	sf::Sprite cursorSprite(cursorTextureDefault);
	cursorSprite.setScale(sf::Vector2f(0.09, 0.09));

	//Music
	sf::Music music;
	music.openFromFile("sound/ambientMu.ogg");
	music.play();

	//Instance Tests 
	Textbox box(window);

	Npc kitty(20, 20, "images/hello.jpeg");
	kitty.setScale(0.2);

	Player chr(300, 250, "images/penguin.png");
	chr.setScale(0.06);

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

		chr.movePos(10);

		//Cursor
		cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		kitty.mouseOver(cursorSprite, cursorTextureTalk, cursorTextureDefault);
		kitty.speak("Kitty", "Hi there", box);


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
