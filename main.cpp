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
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();
	//Used to keep track of mouse movement using both displacement and user mouse movement
	float mousePosX, mousePosY, mousePosXDisplacement, mousePosYDisplacement;
	mousePosXDisplacement = mousePosYDisplacement = 0;

	//Cursor can't leave window
	//TODO: ??? Not working???
	//window.setMouseCursorGrabbed(true);

	//Disable the user's OS mouse
	window.setMouseCursorVisible(false);
	//Loads textures for mouses
	sf::Texture cursorTextureDefault, cursorTextureTalk;
	cursorTextureDefault.loadFromFile("images/cursor.png");
	cursorTextureTalk.loadFromFile("images/cursorTalk.png");
	//Cursor starts off with default
	sf::Sprite cursorSprite(cursorTextureDefault);
	cursorSprite.setScale(sf::Vector2f(0.09, 0.09));

	//Music
	sf::Music music;
	music.openFromFile("sound/ambientMu.ogg");
	music.play();

	//Text box instances
	Textbox box(window);

	//NPC instances
	Npc kitty(20, 20, "images/hello.jpeg");
	kitty.setScale(0.2);

	//Player instances
	Player chr(window.getSize().x/2, window.getSize().y/2, "images/penguin.png");
	chr.setScale(0.06);

	//Temporary Background
	sf::Texture bgTexture;
	bgTexture.loadFromFile("images/forest.jpg");
	sf::Sprite bgSprite(bgTexture);
	bgSprite.setPosition(sf::Vector2f(0, 0));

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


		//Cursor
		mousePosX = sf::Mouse::getPosition(window).x;
		mousePosY = sf::Mouse::getPosition(window).y;

		//Character move
		chr.movePos(10, mousePosXDisplacement, mousePosYDisplacement);

		//Sets position of cursor
		cursorSprite.setPosition(sf::Vector2f(mousePosX + mousePosXDisplacement, mousePosY + mousePosYDisplacement));

		//Sets position of box
		box.setPosition(mousePosXDisplacement, mousePosYDisplacement);

		//Npc Kitty interactions
		kitty.mouseOver(cursorSprite, cursorTextureTalk, cursorTextureDefault);
		kitty.speak("Kitty", "Hi there", box);


		
		//Activates window for OpenGL rendering
		sf::Color winColor(107, 120, 140);
		window.clear(winColor);

		//Sets view
		view.setCenter(chr.getSprite().getPosition());
		window.setView(view);

		//window.draw();
		window.draw(bgSprite);
		window.draw(kitty.getSprite());
		window.draw(chr.getSprite());
		box.drawAll(window);
		window.draw(cursorSprite);

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
