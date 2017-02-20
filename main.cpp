#include <iostream>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//Game classes
#include "include/Battle.h"
#include "include/MainMenu.h"
#include "include/Map.h"
#include "include/Npc.h"
#include "include/Player.h"
#include "include/SpriteManage.h"
#include "include/Textbox.h"
#include "include/UIOverlay.h"

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();

	//Text box instances
	Textbox box(view);

	//UIOverlay
	UIOverlay overlay;
	overlay.setCurrency(0);
	overlay.setLevel(1);
	overlay.setExp(1, 10);
	overlay.setHealth(90, 100);
	overlay.setMana(90, 100);

	//NPC instances
	Npc npcTest(128, 128, "images/test4.png");
	
	//Player instances
	Player chr(64, 64);

	//Main menu instance
	MainMenu mainMenu;

	//Background
	Map ground, background, collision;
	ground.setupBitmap("data/maps/testmap", window);
	collision.setupBitmap("data/maps/testcollision", window);
	background.setupStatic("images/background.jpg");

	//Scene
	//0 = menu, 1 = map, 2 = battle
	int scene = 0;

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


		if(scene == 0)
		{
			mainMenu.scroll();
			mainMenu.currentlySelectedIndicate();

			if(mainMenu.selection() == 0)
			{
				scene = 1;
			}
			else if(mainMenu.selection() == 1)
			{
				//TODO load game
			}
			else if(mainMenu.selection() == 2)
			{
				break;
			}

			//TODO Draw background image
			background.drawStatic(window, view); 

			//Draw main menu buttons
			mainMenu.drawAll(window);
		}
		else if(scene == 1)
		{

			//Npc interaction
			npcTest.speak("That One Guy", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sed velit semper, bibendum orci id, auctor tellus. Proin sollicitudin, urna et accumsan", box);

			//Character moves if npcs aren't speaking
			if(!npcTest.getSpeaking())
			{
				chr.movePos();
			}
			chr.encounter(10, scene);

			//Activates window for OpenGL rendering
			sf::Color winColor(107, 120, 140);
			window.clear(winColor);

			//Sets view
			view.setCenter(chr.getPosition());
			window.setView(view);

			//Sets position based on view
			overlay.setPosition(view);
			box.updatePosition(view);

			//Always on bottom
			background.drawStatic(window, view); 

			//Mid
			ground.drawBitmap(window);
			collision.drawCollision(window, chr);
			chr.drawSprite(window);

			//Npcs
			window.draw(npcTest.getSprite());
			npcTest.collision(chr);
			
			//Always on top
			box.drawAll(window);

			//Draw UI
			overlay.drawAll(window);
		}
		else if(scene == 2)
		{
			chr.setPosition(800, 450);

			//Use dynamically allocated Battle instance to later delete
			Battle battleScene;
			battleScene.setupBattle("data/enemies/testenemy");
			
			//Reset screen view
			view.setCenter(sf::Vector2f(512, 384));
			window.setView(view);
			overlay.setPosition(view);

			//Background image
			background.drawStatic(window, view);

			//Midground
			chr.drawSprite(window);
			battleScene.drawEnemies(window);

			//Update UI
			overlay.drawAll(window);
		}

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}

