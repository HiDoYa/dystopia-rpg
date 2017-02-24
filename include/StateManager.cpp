#include "Battle.h"
#include "MainMenu.h"
#include "Map.h"
#include "StateManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>

StateManager::StateManager()
{
	currentState = 0;

	menuLoaded = false;
	mapLoaded = false;
	battleLoaded = false;
}

//********* MENU *************

void StateManager::allMenu(sf::RenderWindow& win)
{
	loadMenu();
	updateMenu(win);
}

void StateManager::loadMenu()
{
	if(!menuLoaded)
	{
		menuLoaded = true;
		mainMenu.setTextureSprite("images/background.jpg");
	}
}

void StateManager::updateMenu(sf::RenderWindow& win)
{
	mainMenu.scroll();
	mainMenu.currentlySelectedIndicate();

	switch (mainMenu.selection())
	{
		case 0:
			//Starts game
			currentState = 1;
			break;
		case 1:
			//TODO Load game
			break;
		case 2:
			//Exits game
			win.close();
			break;
	}

	//Draw bg
	mainMenu.drawSprite(win);

	//Draw menu
	mainMenu.drawAll(win);

}

//********* MAP *************

void StateManager::allMap(sf::RenderWindow& win, sf::View& view)
{
	loadMap(win);
	updateMap(win, view);
	renderMap(win, view);
}

void StateManager::loadMap(sf::RenderWindow& win)
{
	if(!mapLoaded)
	{
		battleLoaded = false;
		mapLoaded = true;
		//TODO Load file that contains names of all three of these ground/collision/background files for loading
		ground.setupBitmap("data/maps/testmap", win);
		collision.setupBitmap("data/maps/testcollision", win);
		background.setupStatic("images/background.jpg");

		//TODO Load appropriate npcs w/ dynamic allocation and from files. Use some loop for number of npcs.
		Npc temp;
		temp.setPosition(128, 128);
		npc.push_back(temp);
		npc[0].setTextureSprite("images/test4.png");

		//TODO Set player position based on map or other factors
		player.setPosition(64, 64);
	}
}

void StateManager::updateMap(sf::RenderWindow& win, sf::View& view)
{
	//TODO Set overlay based on player stats
	overlay.setCurrency(0);
	overlay.setLevel(1);
	overlay.setExp(1, 10);
	overlay.setHealth(90, 100);
	overlay.setMana(90, 100);

	//TODO NPC speak
	npc[0].speak("That One Guy", "Lorem ipsum dolor", textbox);

	//TODO Loop so all npcs are checked
	if(!npc[0].getSpeaking())
	{
		player.movePos();
	} 
	//TODO Set encounter rate based on map
	player.encounter(100, currentState);

	//Activate window for OpenGL rendering
	win.clear();

	//Set view
	view.setCenter(player.getPosition());
	win.setView(view);

	//Sets position based on view
	overlay.setPosition(view);
	textbox.updatePosition(view);
}

void StateManager::renderMap(sf::RenderWindow& win, sf::View& view)
{
	//Bot ground
	background.drawStatic(win, view);

	//Mid ground
	ground.drawBitmap(win);
	collision.drawCollision(win, player);
	player.drawSprite(win);
	
	//TODO Loop for npcs
	win.draw(npc[0].getSprite());
	npc[0].collision(player);

	//TODO High ground
	
	//Always on top
	textbox.drawAll(win);
	overlay.drawAll(win);
}

//******** BATTLE *********

void StateManager::allBattle(sf::RenderWindow& win, sf::View& view)
{
	loadBattle(win, view);
	updateBattle(win, view);
	renderBattle(win, view);
}

void StateManager::loadBattle(sf::RenderWindow& win, sf::View& view)
{
	if(!battleLoaded)
	{
		mapLoaded = false;
		battleLoaded = true;

		//TODO Load battle data
		battle.setupBattle("data/enemies/testenemy");

		//Set view
		view.setCenter(sf::Vector2f(512, 384));
		win.setView(view);
		overlay.setPosition(view);

		//TODO Set background image
	}
}

void StateManager::updateBattle(sf::RenderWindow& win, sf::View& view)
{
	//TODO
	player.setPosition(800, 450);
}

void StateManager::renderBattle(sf::RenderWindow& win, sf::View& view)
{
	//Background image
	background.drawStatic(win, view);

	//TODO Mid ground
	player.drawSprite(win);
	battle.drawAll(win);

	//TODO On top
	overlay.drawAll(win);
}

//***** ACCESSORS ******
int StateManager::getCurrentState()
{
	return currentState;
}
