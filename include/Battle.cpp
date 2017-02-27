#include "Battle.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>

#include <cctype>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Battle::Battle()
{
}

void Battle::setupBattle(sf::String enemyList)
{
	//Lists off the possible area that the enemy can be spawned in
	std::vector<sf::Vector2f> enemyPlaces;
	enemyPlaces.push_back(sf::Vector2f(200, 300));
	enemyPlaces.push_back(sf::Vector2f(400, 450));
	enemyPlaces.push_back(sf::Vector2f(200, 600));

	//TODO Open file and get player attacks 
	//std::ifstream comboFile("combo");
	//comboFile >> inp;

	//while(!comboFile.eof())
	//{
	//	if(inp == 'u')
	//	{
	//		validCombos.push_back("");
	//		comboFile >> validCombos[validCombos.size() - 1];
	//	}
	//	else
	//	{
	//		comboFile >> tempGarbage;
	//	}

	//	comboFile >> inp;
	//}

	//comboFile.close();

	//Get enemies
	srand(time(NULL));
	
	numEnemies = rand() % 3 + 1;
	currentEnemySelected = 0;

	//TODO Gets the number of monsters to choose from
	//STORE ENEMY INFORMATION FROM FILE INTO A VECTOR/CLASS IN GAME
	//MAKE MEMBER FUNCTION FOR ENEMY TO GET INFO FROM FILE
	//int inp, numEnemiesInFile;
	//std::ifstream enemyFile(enemyList);
	//enemyFile >> inp;
	//numEnemiesInFile = inp;
	

	//Initialize circle shape
	//TODO Get player optins from file and get numSkills from file
	numSkills = 2;
	for(int i = 0; i < numSkills; i++)
	{
		sf::CircleShape temp;
		playerOptions.push_back(temp);
		playerOptions[i].setRadius(15);
		playerOptions[i].setPosition(sf::Vector2f(900, 500));
		playerOptions[i].setFillColor(sf::Color::Blue);
	}

	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		//TODO
		//std::ifstream enemyFile(enemyList);
		//enemyFile >> inp;
		
		//TODO Make unique_ptrs
		Enemy temp;
		enemies.push_back(temp);
		
		//TODO Different character sheet holding data of enemies?
		enemies[i].setPosition(enemyPlaces[i].x, enemyPlaces[i].y);
		enemies[i].setName("Bob");
		enemies[i].setLevel(3);
		enemies[i].setMaxHp(100);
		enemies[i].setCurrentHp(100);
		enemies[i].setMaxMana(100);
		enemies[i].setCurrentMana(90);
		enemies[i].setAgility(50);
		enemies[i].setAtk(10);

		enemies[i].setAlive(true);
		enemies[i].updatePosition();
	}
}

void Battle::startBattle()
{
	//TODO Animation to transition from map to battle
}

void Battle::tickBattle()
{
	tme = clock.getElapsedTime();
	currentTime = tme.asMilliseconds();
}
void Battle::endBattle(int& scene) {
	bool gameWin = true;
	for(int i = 0; i < numEnemies; i++)
	{
		//If some enemies are still alive, you don't win
		if(enemies[i].getAlive())
		{
			gameWin = false;
		}
	}

	if(gameWin)
	{
		scene = 1;
	}
}

void Battle::changeEnemyFocus()
{
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	
	if(!qPressed)
	{
		qNotPressed = true;
	}

	if(qPressed && qNotPressed)
	{
		for(int i = 0; i < numEnemies; i++)
		{
			currentEnemySelected++;
			if(currentEnemySelected >= numEnemies)
			{
				currentEnemySelected = 0;
			}

			if(!(enemies[currentEnemySelected].getAlive()))
			{
				break;
			}
		}
	}
}

//Returns true if player is dead
bool Battle::checkPlayerDeath(Player player)
{
	if(player.getCurrentHp() < 1)
	{
		//Player dies, game over
		return true;
	}
	return false;
}

//Returns true if all enemies are dead
bool Battle::checkEnemyDeaths()
{
	bool allDead = true;

	for(int i = 0 ; i < numEnemies; i++)
	{
		if(enemies[i].getCurrentHp() < 1)
		{
			//enemy has died
			enemies[i].setAlive(false);
			allDead = false;
		}
	}

	return allDead;
}

void Battle::enemyAttack(int enemNum, Player player)
{
	//TODO player.setCurrentHp(player.getCurrentHp() - enemies[enemNum].getAtk());
}

void Battle::drawEnemies(sf::RenderWindow& win)
{
	for(int i = 0; i < numEnemies; i++)
	{
		enemies[i].drawAll(win);
	}
}

void Battle::drawAll(sf::RenderWindow& win)
{
	drawEnemies(win);
	for(int i = 0; i < playerOptions.size(); i++)
	{
		win.draw(playerOptions[i]);
	}
}

//*************** MUTATORS ******************

void Battle::setEnemyHp(int enemyNum, int newHp)
{
	enemies[enemyNum].setCurrentHp(newHp);
}

//*************** ACCESSORS ******************
//Input is which enemy hp you want
int Battle::getEnemyHp(int enemyNum)
{
	return enemies[enemyNum].getCurrentHp();
}

int Battle::getNumEnemies()
{
	return numEnemies;
}

