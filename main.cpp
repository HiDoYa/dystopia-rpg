#include <cmath>
#include <string>
#include <iostream>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//Game classes
#include "include/Environment.h"
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

	//Environment instance
	Environment tree(300, 100, "images/tree.png");

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
		chr.movePos(mousePosXDisplacement, mousePosYDisplacement);

		bool noPass = tree.getColliding(chr.getSprite()) || kitty.getColliding(chr.getSprite());
		if(noPass)
		{
			chr.setPos(prevPosX, prevPosY);
			mousePosXDisplacement = prevMousePosXDisplacement;
			mousePosYDisplacement = prevMousePosYDisplacement;
		}
		prevPosX = chr.getPos().x;
		prevPosY = chr.getPos().y;
		prevMousePosXDisplacement = mousePosXDisplacement;
		prevMousePosYDisplacement = mousePosYDisplacement;

		//Sets position of cursor
		mouse.setPosition(mousePosX + mousePosXDisplacement, mousePosY + mousePosYDisplacement);

		//Sets position of box
		box.setPosition(mousePosXDisplacement, mousePosYDisplacement);

		//Npc Kitty interactions
		if(kitty.mouseOver(mouse.getSprite()))
		{
			mouse.useTalkMouse();
		}
		else
		{
			mouse.useDefaultMouse();
		}
		std::string strTest = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum aliquet dolor urna, eget convallis nulla fringilla vitae. Praesent purus dolor, accumsan eu auctor a, eleifend a nibh. Duis cursus purus nulla, eget fringilla leo sollicitudin sed. Proin et gravida lacus. Nunc nulla urna, tempus et fermentum quis, viverra ac ipsum. Mauris a fermentum ex, nec lobortis mauris. Morbi commodo lorem nec purus iaculis dictum.";
		kitty.speak("Kitty", strTest, box);

		//Activates window for OpenGL rendering
		sf::Color winColor(107, 120, 140);
		window.clear(winColor);
		
		//Getting mouse to change the view
		//int chrX = chr.getSprite().getPosition().x;
		//int chrY = chr.getSprite().getPosition().y;
		//int moX = cursorSprite.getPosition().x;
		//int moY = cursorSprite.getPosition().y;

		//if(moX < 400)
		//{
		//	moX = 400;
		//}
		//else if(moX  > 800)
		//{
		//	moX = 800;
		//}
		//view.setCenter(sf::Vector2f(chrX + moX, chrY + moY));

		//Sets view
		view.setCenter(chr.getSprite().getPosition());
		window.setView(view);

		//window.draw();
		window.draw(bgSprite);
		window.draw(kitty.getSprite());
		window.draw(chr.getSprite());
		window.draw(tree.getSprite());
		box.drawAll(window);
		window.draw(mouse.getSprite());

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}
