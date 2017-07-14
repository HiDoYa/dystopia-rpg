#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

//Game classes
#include "include/Battle.h"
#include "include/BattleOverlay.h"
#include "include/Character.h"
#include "include/CharacterCards.h"
#include "include/ClickButton.h"
#include "include/Dialogue.h"
#include "include/FileReader.h"
#include "include/MainMenu.h"
#include "include/Map.h"
#include "include/MapMenu.h"
#include "include/MapPlayer.h"
#include "include/Npc.h"
#include "include/SpriteManager.h"
#include "include/Skill.h"
#include "include/StatBar.h"
#include "include/Textbox.h"
#include "include/UIOverlay.h"

//Has to be included last
#include "include/StateManager.h"

int main()
{
	//Declares and creates a new window
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Dystopia RPG");

	//Defines what region is shown on screen
	sf::View view = window.getView();
	
	//Sets framerate to 60fps
	window.setFramerateLimit(30);

	//State Manager
	StateManager state;

	std::cout << "\nLoading in main.cpp\n";

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
				std::cout << "Closing event in main.cpp\n";
				window.close();
			}
		}


		if(window.hasFocus())
		{
			switch (state.getCurrentState())
			{
				case 0:
					state.loadMenu();
					state.updateMenu(window);
					break;
				case 1:
					state.loadMap(window);
					state.updateMap(window, view);
					state.renderMap(window, view);
					break;
				case 2:
					state.loadBattle(window, view);
					state.updateBattle(window, view);
					state.renderBattle(window, view);
					break;
				case 3:
					state.loadMapMenu(window, view);
					state.updateMapMenu(window, view);
					state.renderMapMenu(window);
					break;
			}

			//End current frame and display its contents on screen
			window.display();
		}
	}

	std::cout << "Exiting in main.cpp\n";
	return 0;
}

