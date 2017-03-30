#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>

#include "Ally.h"
#include "Battle.h"
#include "Dialogue.h"
#include "MainMenu.h"
#include "Map.h"
#include "Npc.h"
#include "Player.h"
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


		//Loads persistent player info
		//TODO Set overlay based on player stats
		//Set player stats
		player.setLevel(player.getLevel(), overlay);
		player.setMaxHp(player.getMaxHp(), overlay);
		player.setCurrentHp(player.getCurrentHp(), overlay);
		player.setMaxMana(player.getMaxMana(), overlay);
		player.setCurrentMana(player.getCurrentMana(), overlay);
		player.setAgility(player.getAgility());
		player.setAtk(player.getAtk());
		player.setExp(player.getExp(), overlay);
		player.setCurrency(player.getCurrency(), overlay);

		//Loads ally
		loadAlly();
	}
}

void StateManager::loadAlly()
{
	std::ifstream allyFile;
	allyFile.open("data/ally/allyList");

	std::string inp;
	int allyCounter = -1;

	allyFile >> inp;

	do 
	{
		if(inp == "Ally")
		{
			ally.push_back(new Ally());
			allyCounter++;
			ally[allyCounter]->setAllyInParty(false);
			allyFile >> inp;
		}
		if(inp == "Name")
		{
			char tempChar;
			inp = "";
			
			while(allyFile.peek() != '\n')
			{
				allyFile.get(tempChar);
				inp += tempChar;
			}
			ally[allyCounter]->setName(inp);

			//Just in case the npc name overlaps with keywords below
			inp = "";
		}
		if(inp == "Hp")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefaultHp(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setHpInc(atoi(inp.c_str()));
		}
		if(inp == "Mana")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefaultMana(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setManaInc(atoi(inp.c_str()));
		}
		if(inp == "Agility")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefaultAgility(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setAgilityInc(atoi(inp.c_str()));
		}
		if(inp == "Atk")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefaultAtk(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setAtkInc(atoi(inp.c_str()));
		}
		if(inp == "Image")
		{
			allyFile >> inp;
			ally[allyCounter]->setTextureSprite(inp);

			allyFile >> inp;
			ally[allyCounter]->setTextureRect(0, atoi(inp.c_str()));
		}
		allyFile >> inp;
	} while(!allyFile.eof());
	allyFile.close();

	//Initializes contents of ally assuming player is level 1
	for(int i = 0; i < ally.size(); i++)
	{
		ally[i]->levelUp(1);
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
			//TODO get ally current hp/mana. call levelUp(playerLevel) first, then call loadingAlly(3xint)
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
		loadMainMapFile(mapFileString1 + "main" + mapFileString2);

		//Set prevZ and prevM to the current
		prevZ = currentZone;
		prevM = currentMap;

		//TODO Load appropriate npcs w/ dynamic allocation and from files. Use some loop for number of npcs.
		//TODO When loading another map, pop_back all current npcs

		//TODO Set player position based on map or other factors
		player.setPosition(startPosX, startPosY);
	}
}

void StateManager::loadMapEnemies(std::string enemyList)
{
	//Temp variables
	std::string strInp;
	int tempCounter = -1;

	//Read from enemyFile to create enemies purely for storing enemy info
	enemyListStore.clear();
	std::ifstream enemyFile(enemyList);
	while(!enemyFile.eof())
	{
		enemyFile >> strInp;
		if(strInp == "Enemy")
		{
			//Increments counter and creates new enemy
			tempCounter++;
			enemyListStore.push_back(tempEnemy);
			enemyListStore[tempCounter].setAlive(true);
			enemyFile >> strInp;
		}
		if(strInp == "Name")
		{
			char nameChar;
			strInp = "";
			while(enemyFile.peek() != '\n')
			{
				enemyFile.get(nameChar);
				strInp += nameChar;
			}
			enemyListStore[tempCounter].setName(strInp);

			strInp = "";
		}
		if(strInp == "Chance")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setChance(atoi(strInp.c_str()));
		}
		if(strInp == "Level")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setLevel(atoi(strInp.c_str()));
		}
		if(strInp == "Hp")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setMaxHp(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setCurrentHp(atoi(strInp.c_str()));
		}
		if(strInp == "Mana")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setMaxMana(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setCurrentMana(atoi(strInp.c_str()));
		}
		if(strInp == "Agility")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setAgility(atoi(strInp.c_str()));
		}
		if(strInp == "Atk")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setAtk(atoi(strInp.c_str()));
		}
		if(strInp == "Image")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setTextureSprite(strInp);
			enemyFile >> strInp;
			//TODO where the enemy is located in the file (y loc)
			enemyListStore[tempCounter].setTextureRect(0, atoi(strInp.c_str()));
		}
	}
	enemyFile.close();
}

void StateManager::loadMainMapFile(std::string fileNm)
{
	//Temp var
	std::string strInp;
	int numOne, numTwo, numThree;
	numOne = numTwo = numThree = 0;

	int npcCounter = -1;
	int currentTextNum = -1;
	npc.clear();

	std::ifstream mainMapFile(fileNm);
	do
	{
		mainMapFile >> strInp;
		if(strInp == "EncRate")
		{
			mainMapFile >> strInp;
			encounterRate = atoi(strInp.c_str());
		}
		if(strInp == "EnemList")
		{
			mainMapFile >> strInp;
			std::string tempEnemyList = "data/enemies/" + strInp;
			loadMapEnemies(tempEnemyList);
		}
		if(strInp == "PrevZM")
		{
			//TODO 
			mainMapFile >> strInp;
			int potenPrevZ = atoi(strInp.c_str());
			mainMapFile >> strInp;
			int potenPrevM = atoi(strInp.c_str());

			//TODO
			//Gets "NewPos"
			mainMapFile >> strInp;

			if(potenPrevZ == prevZ && potenPrevM == prevM)
			{
				mainMapFile >> strInp;
				startPosX = atoi(strInp.c_str()) * 64;
				mainMapFile >> strInp;
				startPosY = atoi(strInp.c_str()) * 64;
			}
			else
			{
				mainMapFile >> strInp;
				mainMapFile >> strInp;
			}
			
		}
		if(strInp == "Npc")
		{
			//Resets text number
			currentTextNum = -1;

			//Increments and makes new npc
			npcCounter++;
			npc.push_back(new Npc());
		}
		if(strInp == "Image")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->setTextureSprite(strInp);
		}
		if(strInp == "ImagePos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			mainMapFile >> numThree;
			npc[npcCounter]->setTextureRect(numOne, numTwo, numThree);
		}
		if(strInp == "Pos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			npc[npcCounter]->setPosition(numOne * 64, numTwo * 64);
		}
		if(strInp == "Name")
		{
			char nameChar;
			strInp = "";
			
			//Gets the whole text (including whitespace)
			while(mainMapFile.peek() != '\n')
			{
				mainMapFile.get(nameChar);
				strInp += nameChar;
			}

			npc[npcCounter]->setName(strInp);

			//Just in case the text overlaps with keywords below
			strInp = "";
		}
		if(strInp == "Start")
		{
			//The beginning of new text for a npc
			currentTextNum++;
			npc[npcCounter]->pushNextText();
		}
		if(strInp == "CondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(true);
		}
		if(strInp == "CondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(false);
		}
		if(strInp == "Text")
		{
			char readText;
			strInp = "";
			
			//Gets the whole text (including whitespace)
			while(mainMapFile.peek() != '\n')
			{
				mainMapFile.get(readText);
				strInp += readText;
			}

			npc[npcCounter]->pushText(strInp);
			//Just in case the text overlaps with keywords below
			strInp = "";

		}
		if(strInp == "SetCondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(true);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
		if(strInp == "SetCondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(false);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
	} while(!mainMapFile.eof());
	mainMapFile.close();
}

void StateManager::updateMap(sf::RenderWindow& win, sf::View& view)
{
	//Battles must be loaded when going from map
	battleLoaded = false;
	player.setPosition(startPosX, startPosY);

	//Activate window for OpenGL rendering
	win.clear();

	//TODO NPC speak
	speaking = false;

//	npc[0]->speak("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eu diam eget magna ullamcorper", textbox, player);
//	npc[1]->speak("hii there", textbox, player);
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
	
	//TODO Loop so all npcs are checked
	if(!speaking)
	{
		player.movePos();
		startPosX = player.getPosition().x;
		startPosY = player.getPosition().y;
	} 
	//TODO Set encounter rate based on map
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
	
	//TODO Loop for npcs
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

		//TODO Load battle data
		battle->setupBattle(enemyListStore, player, ally);

		//Set view
		view.setCenter(sf::Vector2f(512, 384));
		win.setView(view);
		overlay.setPosition(view);

		//TODO Set background image
	}
}

void StateManager::updateBattle(sf::RenderWindow& win, sf::View& view)
{
	//Activate window for OpenGL rendering
	win.clear();

	switch (currentBattleState)
	{
		//Battle state 0 Menu shows and player can make decision
		case 0:
			//For damage calc
			battle->setInitHp(player.getCurrentHp());

			//For skill
			battle->changeCurrentSkill();
			battle->changeEnemyFocus();
			currentBattleState = battle->chooseCurrentSkill();
			break;
		//Battle state 1 (find enemies that should attack, start animating, and go to 2 OR go to 0)
		case 1:
			battle->attackManager(currentBattleState, player, ally);
			break;
		//Battle state 2 (calculate damage, animate hp going down, ending animation)
		case 2:
			battle->hpCalculate(currentBattleState, player, overlay);
			break;
		//Battle state 3 (check for game over. go back to 0 if not game over)
		case 3:
			battle->checkEndBattle(player, currentBattleState, currentState);
			break;
	}
}

void StateManager::renderBattle(sf::RenderWindow& win, sf::View& view)
{
	//Background image
	background->drawStatic(win, view);

	//TODO Mid ground
	player.drawSprite(win);
	battle->drawAll(win, currentBattleState);

	//TODO On top
	overlay.drawAll(win);
}

//***** ACCESSORS ******
int StateManager::getCurrentState()
{
	return currentState;
}
