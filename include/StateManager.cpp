#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>

#include "Battle.h"
#include "Character.h"
#include "Dialogue.h"
#include "FileReader.h"
#include "MainMenu.h"
#include "Map.h"
#include "MapPlayer.h"
#include "Npc.h"
#include "Skill.h"
#include "Textbox.h"
#include "UIOverlay.h"

#include "StateManager.h"

StateManager::StateManager()
{
	//Placeholder defaults
	startPosX = startPosY = 64;
	encounterRate = 0;
	currentZone = currentMap = 0;

	//Defaults
	currentState = 0;
	currentBattleState = 0;
	prevZ = prevM = 0;

	menuLoaded = false;
	mapLoaded = false;
	battleLoaded = false;

	battle.reset(new Battle);

	//Event has false and true by default
	event.push_back(false);
	event.push_back(true);
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
		mainMenu.setTextureSprite("images/background.png");

		fileReader.loadAlly(ally);
		fileReader.loadSkill(skill);
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
		mapLoaded = true;

		std::string mapFileString1 = "data/maps/z" + std::to_string(currentZone) + "/";
		std::string mapFileString2 = "/m" + std::to_string(currentMap);

		//Set maps
		ground.reset(new Map);
		collision.reset(new Map);
		background.reset(new Map);

		ground->setupBitmap(mapFileString1 + "ground" + mapFileString2, win);
		collision->setupBitmap(mapFileString1 + "collision" + mapFileString2, win);
		background->setupStatic("images/background.png");

		//Loads npcs from main map file
		std::string fileNm = mapFileString1 + "main" + mapFileString2;
		fileReader.loadMainMapFile(fileNm, npc, enemyListStore, prevZ, prevM, startPosX, startPosY, currentZone, currentMap, encounterRate);

		//Set prevZ and prevM to the current
		prevZ = currentZone;
		prevM = currentMap;

		//Set player position based on map or other factors
		player.setPosition(startPosX, startPosY);
	}
}

void StateManager::updateMap(sf::RenderWindow& win, sf::View& view)
{
	//Battles must be loaded when going from map
	battleLoaded = false;
	player.setPosition(startPosX, startPosY);

	//Activate window for OpenGL rendering
	win.clear();

	speaking = false;

	for(int i = 0; i < npc.size(); i++)
	{
		npc[i]->speak(event, textbox, player);
	}


	for(int i = 0; i < npc.size(); i++)
	{
		if(npc[i]->getSpeaking())
		{
			speaking = true;
		}
	}
	
	if(!speaking)
	{
		player.movePos();
		startPosX = player.getPosition().x;
		startPosY = player.getPosition().y;
	} 
	player.encounter(encounterRate, currentState);

	ground->newMapCheck(player, startPosX, startPosY, currentZone, currentMap, mapLoaded, encounterRate);

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
	background->drawStatic(win, view);

	//Mid ground
	ground->drawBitmap(win);
	collision->drawCollision(win, player);
	player.drawSprite(win);
	
	for(int i = 0; i < npc.size(); i++)
	{
		win.draw(npc[i]->getSprite());
	}

	for(int i = 0; i < npc.size(); i++)
	{
		npc[i]->collision(player);
	}
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
		battleLoaded = true;

		battle->setupBattle(enemyListStore, ally);

		//Set view
		view.setCenter(sf::Vector2f(512, 384));
		win.setView(view);
		overlay.setPosition(view);
	}
}

void StateManager::updateBattle(sf::RenderWindow& win, sf::View& view)
{
	//Activate window for OpenGL rendering
	win.clear();

	//TODO Maybe move currentBattleState into battle class
	switch (currentBattleState)
	{
		//Battle state 0
		//Fastest character is calculated and checks whether it is an ally, enemy, or nobody.
		case 0:
			battle->checkForNextChar(currentBattleState);
			break;
		//Battle state 1
		//if player or ally is attacking, user chooses next course of action
		case 1:
			battle->changeCurrentSkill();
			battle->chooseCurrentSkill(currentBattleState);
			break;
		//Battle state 2
		//if player chose a targetable skill, choose an enemy to attack
		case 2:
			battle->changeEnemyFocus();
			break;
		//Battle state 3
		//Move forward and attack (both enemies and allies)
		case 3:
			battle->attackManager(currentBattleState, currentState);
			break;
		//Battle state 4
		//calculate damage, animate hp going down, end animation
		case 4:
			//battle->hpCalculate(currentBattleState, overlay);
			break;
		//Battle state 5
		//check for game over. Go back to beginning if not game over. If all enemies/allies have attacked, reset their flags.
		case 5:
			battle->checkEndBattle(currentBattleState, currentState);
			break;
	}
}

void StateManager::renderBattle(sf::RenderWindow& win, sf::View& view)
{
	//Background image
	background->drawStatic(win, view);

	//Mid ground
	battle->drawAll(win, currentBattleState);

	//TODO On top
	overlay.drawAll(win);
}

//***** ACCESSORS ******
int StateManager::getCurrentState()
{
	return currentState;
}
