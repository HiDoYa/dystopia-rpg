#include "Battle.h"

#include <SFML/Graphics.hpp>

#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Battle::Battle()
{
	//Initializations
	currentCombo = "";
	nextAttackBlock = false;
	lastImmobilizationTime = 0;
	currentEnemySelected = 0;

	//Time that player is immobilized if fail
	immobilizationTime = 3000;
}

void Battle::setupBattle(int minLevel, int maxLevel, int hp)
{
	//Temporary input
	char inp;
	std::string tempGarbage;

	//Set Hp
	playerHp = hp;

	//TODO Open file and get combos
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
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();
	srand(currentTime);
	
	//3 enemies at max
	int numEnemies = rand() % 2 + 1;

	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		//TODO HP and attack of enemy scales by level
		//Different character sheet holding data of enemies?
		enemyLvls.push_back(rand() % (maxLevel - minLevel) + 1);
		//Used to store sprite, attacks, etc. of enemy
		//enemyType.push_back();
		enemyHp.push_back(100);
		enemyAtk.push_back(10);
		enemyAttackDelay.push_back(5000);
		enemiesAliveIndex.push_back(1);
	}
}

void Battle::startBattle()
{
}

void Battle::endBattle(int& scene)
{
	bool gameWin = true;
	for(int i = 0; i < enemiesAliveIndex.size(); i++)
	{
		//If some enemies are still alive, you win
		if(enemiesAliveIndex[i] == 1)
		{
			gameWin = false;
		}
	}

	if(gameWin)
	{
		scene = 1;
	}
}

//Pressing Q scrolls through enemies that are alive
void Battle::changeEnemyTarget()
{
	bool keyQ = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	if(!keyQUp && !keyQ)
	{
		keyQUp = true;
	}

	if(keyQ && keyQUp)
	{
		//TODO Fix this shit
		currentEnemySelected++;

		if(currentEnemySelected > enemiesAliveIndex.size())
		{
			currentEnemySelected = enemiesAliveIndex[0];
		}

		if(enemyHp[currentEnemySelected] < 1)
		{
			currentEnemySelected++;
		}
	}
}

void Battle::checkEnemyDeaths()
{
	for(int i = 0 ; i < enemyHp.size(); i++)
	{
		if(enemyHp[i] < 1)
		{
			//enemy has died
			enemiesAliveIndex[i] = 0;
		}
	}
}

void Battle::playerAttack()
{
	bool keyW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool keyA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool keyS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool keyD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	//Make sure key goes up before pressing again
	if(currentTime > immobilizationTime + lastImmobilizationTime)
	{
		if(!keyWUp && !keyW)
		{
			keyWUp = true;
		}
		if(!keyAUp && !keyA)
		{
			keyAUp = true;
		}
		if(!keySUp && !keyS)
		{
			keySUp = true;
		}
		if(!keyDUp && !keyD)
		{
			keyDUp = true;
		}
		
		//Individual key presses
		if(keyW && keyWUp)
		{
			currentCombo.push_back('W');
			keyWUp = false;
		}
		if(keyA && keyAUp)
		{
			currentCombo.push_back('A');
			keyAUp = false;
		}
		if(keyS && keySUp)
		{
			currentCombo.push_back('S');
			keySUp = false;
		}
		if(keyD && keyDUp)
		{
			currentCombo.push_back('D');
			keyDUp = false;
		}
	}
}

void Battle::activateAttack()
{
	bool keySpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	time = clock.getElapsedTime();
	currentTime = time.asMilliseconds();

	if(keySpace)
	{
		if(currentCombo == "s")
		{
			nextAttackBlock = true;
			successCombo = true;
		}
		else
		{
			for(int i = 0; i < validCombos.size(); i++)
			{
				if(validCombos[i] == currentCombo)
				{
					//TODO Damage calc (based on combo size or file holding damage multiplier?)
					enemyHp[currentEnemySelected] -= 10;
					successCombo = true;
				}
			}
		}
	}

	//Resets combo if successful
	if(successCombo)
	{
		currentCombo = "";
	}
	else
	{
		lastImmobilizationTime = currentTime;
	}
}

void Battle::enemyAttack()
{
	//TODO

	//Player has died. Game over
	if(playerHp < 1)
	{
		//scene = 0;
	}
}

void Battle::setPlayerHp(int hpChange)
{
	playerHp += hpChange;
}

void Battle::setEnemyHp(int enemyNum, int hpChange)
{
	enemyHp[enemyNum] += hpChange;
}

int Battle::getPlayerHp()
{
	return playerHp;
}

//Input is which enemy hp you want
int Battle::getEnemyHp(int enemyNum)
{
	return enemyHp[enemyNum];
}

int Battle::getNumEnemies()
{
	return enemyHp.size();
}
