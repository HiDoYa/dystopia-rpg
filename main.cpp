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
#include "include/Mouse.h"

//testing

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();

	//Used to keep track of mouse movement using both displacement and user mouse movement
	float mousePosX, mousePosY, mousePosXDisplacement, mousePosYDisplacement, prevMousePosXDisplacement, prevMousePosYDisplacement;
	mousePosXDisplacement = mousePosYDisplacement = prevMousePosXDisplacement = prevMousePosYDisplacement = 0;


	//Disable the user's OS mouse
	window.setMouseCursorVisible(false);

	//Loads mouse class
	Mouse mouse;

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
	Player chr(window.getSize().x/2, window.getSize().y/2);
	int prevPosX, prevPosY;
	prevPosX = prevPosY = 0;

	//Temporary Background
	sf::Texture bgTexture;
	bgTexture.loadFromFile("images/maps/testmap.jpg");
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
				std::cout << "closing-event ";
				window.close();
			}
		}


		//Cursor
		mousePosX = sf::Mouse::getPosition(window).x;
		mousePosY = sf::Mouse::getPosition(window).y;

		//Character move
		chr.setCollisionBools(kitty.getSprite());
		chr.movePos(mousePosXDisplacement, mousePosYDisplacement);

		prevPosX = chr.getPos().x;
		prevPosY = chr.getPos().y;
		prevMousePosXDisplacement = mousePosXDisplacement;
		prevMousePosYDisplacement = mousePosYDisplacement;

		//Sets position of cursor
		mouse.setPosition(mousePosX + mousePosXDisplacement, mousePosY + mousePosYDisplacement);

		//Sets position of box
		box.setPosition(mousePosXDisplacement, mousePosYDisplacement);

		//Npc Kitty interactions
		mouse.npcTalkSet(&kitty);

		kitty.speak("Kitty", "Lorem ipsum dolor sit amet", box);

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
		window.draw(mouse.getSprite());

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
