#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Player.h"

#include "Battle.h"

Battle::Battle()
{
}

void Battle::setupBattle(std::vector<Enemy> enemyList)
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
	
	//Initialize
	currentSkill = 0;
	playerCanAttack = true;
	numSkills = 6;
	currentEnemySelected = 0;
	animComplete = hpComplete = false;

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

	//Get number of enemies
	srand(time(NULL));
	numEnemies = rand() % 3 + 1;
	
	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		int maxRandChance = 0;
		int index = 0;
		
		for(int potentialEnem = 0; potentialEnem < enemyList.size(); potentialEnem++)
		{
			int tempNum = ((rand() % 100) + 1) * enemyList[potentialEnem].getChance();
			if(tempNum > maxRandChance)
			{
				maxRandChance = tempNum;
				index = potentialEnem;
			}
		}
		enemies.push_back(enemyList[index]);
		enemies[i].setPosition(enemyPlaces[i].x, enemyPlaces[i].y);
		enemies[i].updatePosition();
	}
}

void Battle::startBattle()
{
	//TODO Animation to transition from map to battle
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

//*********** BATTLE STATE 0 *********************
void Battle::changeEnemyFocus()
{
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	
	if(!qPressed)
	{
		qNotPressed = true;
	}

	//If q pressed, swap to next enemy that is not dead
	if(qPressed && qNotPressed)
	{
		do
		{
			currentEnemySelected++;
			if(currentEnemySelected >= numEnemies)
			{
				currentEnemySelected = 0;
			}
		}while(!(enemies[currentEnemySelected].getAlive()));
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
	nextAttack = -2;

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

	switch (nextAttack)
	{
		case -2:
			currentBattleState = 3;
			break;
		//Player Attacks
		case -1:
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

//********** BATTLE STATE 1.5 ****************
//Player simply moves forward
void Battle::playerAttackAnimation(int& currentBattleState, Player& player)
{
	if(player.getPosition().x > 700)
	{
		player.setPosition(player.getPosition().x - 10, player.getPosition().y);
	}
	else
	{
		playerCanAttack = false;
		currentBattleState++;
	}
}

//Enemy simply moves forward
void Battle::enemyAttackAnimation(int& currentBattleState)
{
	sf::Vector2f current = enemies[nextAttack].getPosition();
	
	//Sets the area to stop
	int goalPlace;
	if(nextAttack == 1)
	{
		goalPlace = 500;
	}
	else
	{
		goalPlace = 300;
	}
	
	//Moves the enemy, otherwise increments battle state
	if(current.x < goalPlace)
	{
		enemies[nextAttack].setPosition(current.x + 10, current.y);
	}
	else
	{ 
		enemies[nextAttack].setCanAtk(false);
		currentBattleState++;
	}
}

//******** BATTLE STATE 2 **************
//Calculates hp change for enemy and player
void Battle::hpCalculate(int& currentBattleState, Player& player, UIOverlay& overlay)
{
	int tempHpFinal;
	switch (nextAttack)
	{
		case -1:
			tempHpFinal = enemies[currentEnemySelected].getInitHp() - player.getAtk();
			//Makes sure the lowest hp possible is 0
			tempHpFinal = getMaxNum(0, tempHpFinal);
			playerPostAttackAnimation(player);
			if(animComplete)
			{
				enemyHpChange(tempHpFinal, currentBattleState);
			}
			//Animate enemy hp decrease with new hp and old hp and currentselectedenemy
			break;
		case 0:
		case 1:
		case 2:
			tempHpFinal = initHp - enemies[nextAttack].getAtk();
			//Makes sure the lowest hp possible is 0
			tempHpFinal = getMaxNum(0, tempHpFinal);
			enemyPostAttackAnimation();
			if(animComplete)
			{
				playerHpChange(tempHpFinal, player, overlay, currentBattleState);
			}
			//Animate player hp with new hp and old hp
			break;
	}

	//For incrementing currentBattleState
	checkForCompletion(currentBattleState);
}

int Battle::findHpChangeSign(int hpFinal, int hpInit)
{
	int sign;
	if(hpFinal < hpInit)
	{
		sign = -1;
	}
	else if(hpFinal > hpInit)
	{
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	return sign;
}

//TODO Cases in which hp doesn't decrease? low prio - (FILE BASED) (ADD STATUS EFFECTS)
void Battle::playerHpChange(int hpFinal, Player& player, UIOverlay& overlay, int& currentBattleState)
{
	int sign = findHpChangeSign(hpFinal, player.getCurrentHp());
	if(player.getCurrentHp() > hpFinal + 3 || player.getCurrentHp() < hpFinal - 3)
	{
		player.setCurrentHp(player.getCurrentHp() + (3 * sign), overlay);
	}
	else if (player.getCurrentHp() != hpFinal)
	{
		player.setCurrentHp(hpFinal, overlay);
	}
	else
	{
		hpComplete = true;
	}
}

void Battle::enemyHpChange(int hpFinal, int& currentBattleState)
{
	int currentEnemyHp = enemies[currentEnemySelected].getCurrentHp();
	int sign = findHpChangeSign(hpFinal, currentEnemyHp);
	if(currentEnemyHp > hpFinal + 3 || currentEnemyHp < hpFinal - 3)
	{
		enemies[currentEnemySelected].setCurrentHp(currentEnemyHp + (3 * sign));
	}
	else if (currentEnemyHp != hpFinal)
	{
		enemies[currentEnemySelected].setCurrentHp(hpFinal);
	}
	else
	{
		hpComplete = true;
	}
}

void Battle::playerPostAttackAnimation(Player& player)
{
	if(player.getPosition().x < 750)
	{
		player.setPosition(player.getPosition().x + 10, player.getPosition().y);
	}
	else
	{
		animComplete = true;
	}
}

void Battle::enemyPostAttackAnimation()
{
	sf::Vector2f current = enemies[nextAttack].getPosition();
	
	//Sets the area to stop
	int goalPlace;
	if(nextAttack == 1)
	{
		goalPlace = 400;
	}
	else
	{
		goalPlace = 200;
	}
	
	//Moves the enemy, otherwise increments battle state
	if(current.x > goalPlace)
	{
		enemies[nextAttack].setPosition(current.x - 10, current.y);
	}
	else
	{
		animComplete = true;
	}
}

void Battle::checkForCompletion(int& currentBattleState)
{
	if(hpComplete && animComplete)
	{
		hpComplete = animComplete = false;
		currentBattleState = 1;
	}
	
}

//*************** BATTLE STATE 3 *********************
//Returns true if player is dead
bool Battle::checkPlayerDeath(Player& player)
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
		if(enemies[i].getCurrentHp() > 1)
		{
			allDead = false;
		}
		else 
		{
			//enemy has died
			enemies[i].setAlive(false);
		}
	}
	return allDead;
}

void Battle::checkEndBattle(Player& player, int& currentBattleState, int& currentState)
{
	if(checkPlayerDeath(player))
	{
		//TODO Gameover
		currentState = 0;
	}
	else if(checkEnemyDeaths())
	{
		//TODO Wins the battle
		currentState = 1;
	}
	else
	{
		newTurn();
		currentEnemyDeath();
		currentBattleState = 0;
	}
}

//Change current enemy selected if the current enemy is dead (and battle is not over yet)
void Battle::currentEnemyDeath()
{
	if(!enemies[currentEnemySelected].getAlive())
	{
		do
		{
			currentEnemySelected++;
			if(currentEnemySelected >= numEnemies)
			{
				currentEnemySelected = 0;
			}
		}while(!enemies[currentEnemySelected].getAlive());
	}
}

//Sets up for new turn
void Battle::newTurn()
{
	playerCanAttack = true;
	for(int i = 0; i < numEnemies; i++)
	{
		//Enemies can only attack next turn if they are still alive
		if(enemies[i].getAlive())
		{
			enemies[i].setCanAtk(true);
		}
	}
}

//************ DRAWING ***************

void Battle::drawEnemies(sf::RenderWindow& win)
{
	for(int i = 0; i < numEnemies; i++)
	{
		if(enemies[i].getAlive())
		{
			enemies[i].drawAll(win);
		}
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

//For both enemy and player
void Battle::setInitHp(int inp)
{
	initHp = inp;
	for(int i = 0; i < numEnemies; i++)
	{
		enemies[i].setInitHp(enemies[i].getCurrentHp());
	}
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

//*************** UTILITY *******************
int Battle::getMaxNum(int numOne, int numTwo)
{
	if(numOne > numTwo)
	{
		return numOne;
	}
	else if(numTwo > numOne)
	{
		return numTwo;
	}
}

