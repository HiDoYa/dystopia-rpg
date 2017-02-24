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
#include "include/StateManager.h"
#include "include/Textbox.h"
#include "include/UIOverlay.h"

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Game");

	//Defines what region is shown on screen
	sf::View view = window.getView();
	
	//Sets framerate to 60fps
	window.setFramerateLimit(60);

	//State Manager
	StateManager state;

	//Main loop - ends when window is closed
	while(window.isOpen())
	{
		//Event Processing
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Request for closing the window
			if(event.type == sf::Event::Closed)
			{
				//Somehow this line fixes a bunch of errors??
				std::cout << "Closing event\n";
				window.close();
			}
		}


		switch (state.getCurrentState())
		{
			case 0:
				state.allMenu(window);
				break;
			case 1:
				state.allMap(window, view);
				break;
			case 2:
				state.allBattle(window, view);
				break;
		}

		//End current frame and display its contents on screen
		window.display();
	}

	return 0;
}

