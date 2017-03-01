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
	numSkills = 6;
	currentSkill = 0;
}

void Battle::setupBattle(sf::String enemyList)
{
	//Lists off the possible area that the enemy can be spawned in
	std::vector<sf::Vector2f> enemyPlaces;
	enemyPlaces.push_back(sf::Vector2f(200, 300));
	enemyPlaces.push_back(sf::Vector2f(400, 450));
	enemyPlaces.push_back(sf::Vector2f(200, 600));

	std::vector<sf::Vector2f> skillsPlaces;
	skillsPlaces.push_back(sf::Vector2f(610, 300));
	skillsPlaces.push_back(sf::Vector2f(600, 400));
	skillsPlaces.push_back(sf::Vector2f(610, 500));
	skillsPlaces.push_back(sf::Vector2f(890, 300));
	skillsPlaces.push_back(sf::Vector2f(900, 400));
	skillsPlaces.push_back(sf::Vector2f(890, 500));

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
	for(int i = 0; i < numSkills; i++)
	{
		sf::CircleShape temp;
		playerOptions.push_back(temp);
		playerOptions[i].setRadius(25);
		playerOptions[i].setPosition(skillsPlaces[i]);
		playerOptions[i].setFillColor(sf::Color(160, 196, 255));
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

//*********** BATTLE STATE 0 *********************
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

void Battle::changeCurrentSkill()
{
	bool wPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool aPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool sPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool dPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	//Reset and prevent full press
	if(!wPressed)
	{
		wNotPressed = true;
	}
	if(!aPressed)
	{
		aNotPressed = true;
	}
	if(!sPressed)
	{
		sNotPressed = true;
	}
	if(!dPressed)
	{
		dNotPressed = true;
	}

	//TODO Change skill
	if(wPressed && wNotPressed)
	{
		wNotPressed = false;
		currentSkill--;
		
		//Special exceptions
		if(currentSkill == -1)
		{
			currentSkill = 0;
		}
		else if(currentSkill == 2)
		{
			currentSkill = 3;
		}
	}
	if(aPressed && aNotPressed)
	{
		aNotPressed = false;
		currentSkill -= 3;

		//Special exceptions
		if(currentSkill < 0)
		{
			currentSkill += 3;
		}
	}
	if(sPressed && sNotPressed)
	{
		sNotPressed = false;
		currentSkill++;
		
		//Special exceptions
		if(currentSkill == 6)
		{
			currentSkill = 5;
		}
		else if(currentSkill == 3)
		{
			currentSkill = 2;
		}
	}
	if(dPressed && dNotPressed)
	{
		dNotPressed = false;
		currentSkill += 3;

		//Special exceptions
		if(currentSkill > 5)
		{
			currentSkill -= 3;
		}
	}
	
	//Reset all colors
	for(int i = 0; i < numSkills; i++)
	{
		playerOptions[i].setFillColor(sf::Color(160, 196, 255));
	}

	//Highlight current
	playerOptions[currentSkill].setFillColor(sf::Color::Blue);
}

int Battle::chooseCurrentSkill()
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(spacePressed)
	{
		return 1;
	}
	return 0;
}

//*********** BATTLE STATE 1 *********************
//Sets nextAttack based on who is the fastest (-1 for player, -2 if everybody is done)
void Battle::findFastestChar(Player& player)
{
	int highestAgil = -1;

	for(int i = 0; i < numEnemies; i++)
	{
		if(enemies[i].getCanAtk() && highestAgil < enemies[i].getAgility())
		{
			highestAgil = enemies[i].getAgility();
			nextAttack = i;
		}
	}

	if(playerCanAttack && player.getAgility() > highestAgil)
	{
		nextAttack = -1;
	}
}

void Battle::attackManager(int& currentBattleState, Player& player)
{
	findFastestChar(player);
	nextAttack = 0;

	switch (nextAttack)
	{
		//Game exits
		case -2:
			currentBattleState = 0;
			break;
		//Player Attacks
		case -1:
			currentBattleState = 2;
			playerAttackAnimation(currentBattleState, player);
			break;
		//Enemy Attacks
		case 0:
		case 1:
		case 2:
			enemyAttackAnimation(currentBattleState);
			break;
	}
}

void Battle::playerAttackAnimation(int& currentBattleState, Player& player)
{
	if(player.getPosition().x > 650)
	{
		player.setPosition(player.getPosition().x - 5, player.getPosition().y);
	}
	else
	{
		currentBattleState++;
	}
}

void Battle::enemyAttackAnimation(int& currentBattleState)
{
	sf::Vector2f current = enemies[nextAttack].getPosition();
	
	//Sets the area to stop
	int goalPlace;
	if(nextAttack == 2)
	{
		goalPlace = 300;
	}
	else
	{
		goalPlace = 500;
	}
	
	//Moves the enemy, otherwise increments battle state
	if(current.x < goalPlace)
	{
		enemies[nextAttack].setPosition(current.x + 5, current.y);
	}
	else
	{ 
		currentBattleState++;
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

void Battle::drawAll(sf::RenderWindow& win, int currentBattleState)
{
	drawEnemies(win);
	if(currentBattleState == 0)
	{
		for(int i = 0; i < playerOptions.size(); i++)
		{
			win.draw(playerOptions[i]);
		}
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

