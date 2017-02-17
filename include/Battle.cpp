#include "Battle.h"
#include "Enemy.h"

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

	//Sets player health bars
	playerHealth.setSize(sf::Vector2f());
	playerDamage.setSize(sf::Vector2f());

	//Time that player is immobilized if fail
	immobilizationTime = 3000;
}

void Battle::setupBattle(int minLevel, int maxLevel, int hp)
{
	//Temporary input
	char inp;
	std::string tempGarbage;

	//Lists off the possible area that the enemy can be spawned in
	std::vector<sf::Vector2f> enemyPlaces;
	enemyPlaces.push_back(sf::Vector2f(100, 100));
	enemyPlaces.push_back(sf::Vector2f(300, 300));
	enemyPlaces.push_back(sf::Vector2f(100, 500));

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
	
	//3 enemies max
	numEnemies = rand() % 2 + 1;

	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		Enemy temp(enemyPlaces[i].x, enemyPlaces[i].y, 64);
		enemies.push_back(temp);
		//TODO HP and attack of enemy scales by level
		//Different character sheet holding data of enemies?
		enemies[i].setLevel(rand() % (maxLevel - minLevel) + 1);
		enemies[i].setHp(100);
		enemies[i].setAtk(10);
		enemies[i].setDelay(5000);
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
		bool enemiesAllDead = true;
		
		for(int ndx = 0; ndx < 3 && !enemiesAllDead; ndx++)
		{
			currentEnemySelected++;

			if(currentEnemySelected > numEnemies)
			{
				currentEnemySelected = 0;
			}

			if(enemies[currentEnemySelected].getHp() > 1)
			{
				enemiesAllDead = false;
				break;
			}
		}

		if(enemiesAllDead)
		{
			//battle ends
		}
	}
}

void Battle::checkEnemyDeaths()
{
	for(int i = 0 ; i < numEnemies; i++)
	{
		if(enemies[i].getHp() < 1)
		{
			//enemy has died
			enemies[i].setAlive(false);
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
					enemies[currentEnemySelected].setHp(enemies[currentEnemySelected].getHp() - 10);
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

void Battle::enemyAttack(int enemNum)
{
	//TODO
	playerHp -= enemies[enemNum].getAtk();

	if(playerHp < 1)
	{
		//Player has died. Game over
		//scene = 0;
	}
}

void Battle::drawEnemies(sf::RenderWindow& win)
{
	for(int i = 0; i < numEnemies; i++)
	{
		win.draw(enemies[i].getSprite());
	}
}

void Battle::setPlayerHp(int hpChange)
{
	playerHp += hpChange;
}

void Battle::setEnemyHp(int enemyNum, int newHp)
{
	enemies[enemyNum].setHp(newHp);
}

int Battle::getPlayerHp()
{
	return playerHp;
}

//Input is which enemy hp you want
int Battle::getEnemyHp(int enemyNum)
{
	return enemies[enemyNum].getHp();
}

int Battle::getNumEnemies()
{
	return numEnemies;
}


