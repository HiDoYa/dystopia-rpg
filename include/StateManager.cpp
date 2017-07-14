#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>

#include "Battle.h"
#include "BattleOverlay.h"
#include "Character.h"
#include "Dialogue.h"
#include "FileReader.h"
#include "MainMenu.h"
#include "Map.h"
#include "MapMenu.h"
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
	mapMenuLoaded = false;

	battle.reset(new Battle);

	//By default, ally 0 is in party
	allyInParty.push_back(0);

	//Event has false and true by default
	stateFlag.push_back(false);
	stateFlag.push_back(true);

}

//********* MENU *************
void StateManager::loadMenu()
{
	if(!menuLoaded)
	{
		menuLoaded = true;
		mainMenu.setTextureSprite("images/ui/mainMenu.png");

		fileReader.loadAlly(ally);
		fileReader.loadSkill(skillList);
	}
}

void StateManager::updateMenu(sf::RenderWindow& win)
{
	switch (mainMenu.clickCheck(win))
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

	//Draw menu
	mainMenu.drawAll(win);
}

//********* MAP *************
void StateManager::loadMap(sf::RenderWindow& win)
{
	if(!mapLoaded)
	{
		mapLoaded = true;

		std::string mapFileString = "data/maps/z" + std::to_string(currentZone) + "/m" + std::to_string(currentMap) + "/";

		//Set maps
		ground.reset(new Map);
		collision.reset(new Map);
		background.reset(new Map);

		ground->setupBitmap(mapFileString + "ground", win);
		collision->setupBitmap(mapFileString + "collision", win);
		background->setupStatic("images/maps/background0.png");

		//Loads npcs from main map file
		std::string fileNm = mapFileString + "main";
		fileReader.loadMainMapFile(fileNm, npc, enemyListStore,
				prevZ, prevM, startPosX, startPosY,
				currentZone, currentMap, encounterRate);

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
		npc[i]->speak(stateFlag, textbox, player);
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
	
	if(overlay.checkForMapMenu(menuOption, win))
	{
		currentState = 3;
	}

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
	overlay.drawAll(win);
	textbox.drawAll(win);
}

//******** BATTLE *********
void StateManager::loadBattle(sf::RenderWindow& win, sf::View& view)
{
	if(!battleLoaded)
	{
		battleLoaded = true;

		battle->setupBattle(enemyListStore, ally, skillList, allyInParty);

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

	std::cout << "CURRENT BATTLE STATE: " << currentBattleState << '\n';

	switch (currentBattleState)
	{
		//Fastest character is calculated and checks whether it is an ally, enemy, or nobody.
		case 0:
			battle->findFastestChar(currentBattleState);
			break;
		//Checks whether a persistent skill needs to be reapplied or removed
		case 1:
			battle->statusHandle(currentBattleState);
			break;
		//[Ally] Options display and user chooses next course of action
		case 2:
			battle->allySkillChoiceHandler(currentBattleState, win);
			break;
		//[Ally] If targetable skill, choose who to target. Else, go straight to state 5
		case 3:
			battle->allyChooseFocus(currentBattleState);
			break;
		//[Enemy] Chooses skill and who to target
		case 4:
			battle->enemyDecision(currentBattleState);
			break;
		//Move forward and attack animations
		case 5:
			battle->moveForwardAnimation(currentBattleState);
			break;
		//Calculate damage/buffs
		case 6:
			battle->handleEffect(currentBattleState);
			break;
		//Animate hp
		case 7:
			battle->hpAnimate(currentBattleState);
			break;
		//Move backward animation
		case 8:
			battle->moveBackwardAnimation(currentBattleState);
			break;
		//Check for game over. Go back to beginning if not game over. 
		//If all enemies/allies have attacked, reset their flags.
		case 9:
			battle->checkEndBattle(currentBattleState, currentState, allyInParty, ally);
			break;
	}
	//TODO Update battle log here
}

void StateManager::renderBattle(sf::RenderWindow& win, sf::View& view)
{
	//Background image
	background->drawStatic(win, view);

	//Mid ground
	battle->drawAll(win, currentBattleState);

	//On top
	overlay.drawAll(win);
}

//***** MAP MENU ******
//TODO Remove view if not used
void StateManager::loadMapMenu(sf::RenderWindow& win, sf::View view)
{
	if(!mapMenuLoaded)
	{
		mapMenuLoaded = true;
		switch(menuOption)
		{
			case 0:
				mapMenu.setupChar(ally);
				break;
			case 1:
				break;
			case 2:
				break;
		}
		mapMenu.setTitle(menuOption);
	}
}

void StateManager::updateMapMenu(sf::RenderWindow& win, sf::View view)
{
	//TODO Move all updatePosition to setup? (Don't need to rerun because view stays same)
	if(overlay.checkForMapMenu(menuOption, win))
	{
		//Reload the menu
		mapMenuLoaded = false;
	}

	mapMenu.updatePosition(view);

	//Check for back button press
	mapMenu.checkForBackButton(currentState, win);

	switch(menuOption)
	{
		case 0:
			mapMenu.checkForCharacterButton(ally, win);
			//This needs to be run here because text height is determined one frame late
			mapMenu.updateCharacterCardPosition(view);
			break;
		case 1:
			break;
		case 2:
			break;
	}
}

void StateManager::renderMapMenu(sf::RenderWindow& win)
{
	switch(menuOption)
	{
		case 0:
			mapMenu.drawAllChar(win);
			break;
		case 1:
			mapMenu.drawAllSkills(win);
			break;
		case 2:
			mapMenu.drawAllBattlePos(win);
			break;
	}

	overlay.drawAll(win);
	mapMenu.drawBack(win);
}

//***** ACCESSORS ******
int StateManager::getCurrentState()
{
	return currentState;
}
