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
	
	//3 enemies max (pick randomly)
	//numEnemies = rand() % 3 + 1;
	numEnemies = 3;
	currentEnemySelected = 0;

	//Gets the number of monsters to choose from
	int inp, numEnemiesInFile;
	std::ifstream enemyFile(enemyList);
	enemyFile >> inp;
	numEnemiesInFile = inp;

	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		//TODO
		//std::ifstream enemyFile(enemyList);
		//enemyFile >> inp;

		Enemy temp(enemyPlaces[i].x, enemyPlaces[i].y);
		enemies.push_back(temp);
		//TODO HP and attack of enemy scales by level
		//Different character sheet holding data of enemies?
		enemies[i].setLevel(3);
		enemies[i].setCurrentHp(100);
		enemies[i].setMaxHp(100);
		enemies[i].setMaxMana(100);
		enemies[i].setAtk(10);
		enemies[i].setAgility(50);
		enemies[i].setAlive(true);
	}
}

void Battle::startBattle()
{
}

void Battle::endBattle(int& scene)
{
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
		return false;
	}
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

void Battle::setEnemyHp(int enemyNum, int newHp)
{
	enemies[enemyNum].setCurrentHp(newHp);
}

//Input is which enemy hp you want
int Battle::getEnemyHp(int enemyNum)
{
	return enemies[enemyNum].getCurrentHp();
}

int Battle::getNumEnemies()
{
	return numEnemies;
}

