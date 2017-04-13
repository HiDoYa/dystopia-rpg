#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Ally.h"
#include "Player.h"

#include "Battle.h"

Battle::Battle()
{
	//Default initializations
	currentSkill = 0;
	currentOptionsShow = 0;
	playerCanAttack = true;
	blinkTurn = true;
	currentTime = lastTime = 0;
	initHp = 100;
	totalAlly = 0;
	nextAttack = 0;
	newPos = 0;
	goalPlace = 0;
	skillType = 0;
	currentEnemySelected = 0;
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	numEnemies = 1;
	hpComplete = animComplete = false;
	
	//Displacement during character turn
	attackXDisp = 125;

	//Ally positions
	allyPos.push_back(sf::Vector2f(650, 200));
	allyPos.push_back(sf::Vector2f(650, 400));
	allyPos.push_back(sf::Vector2f(650, 600));
	allyPos.push_back(sf::Vector2f(850, 200));
	allyPos.push_back(sf::Vector2f(850, 400));
	allyPos.push_back(sf::Vector2f(850, 600));

	//Enemy Positions
	enemyPos.push_back(sf::Vector2f(150, 200));
	enemyPos.push_back(sf::Vector2f(150, 400));
	enemyPos.push_back(sf::Vector2f(150, 600));
	enemyPos.push_back(sf::Vector2f(350, 200));
	enemyPos.push_back(sf::Vector2f(350, 400));
	enemyPos.push_back(sf::Vector2f(350, 600));

	//Options positions
	optionsPos.push_back(sf::Vector2f(-100, -100));
	optionsPos.push_back(sf::Vector2f(-100, 0));
	optionsPos.push_back(sf::Vector2f(-100, 100));
	optionsPos.push_back(sf::Vector2f(100, -100));
	optionsPos.push_back(sf::Vector2f(100, 0));
	optionsPos.push_back(sf::Vector2f(100, 100));
	
	//6 Skills
	numSkills = 6;
}

void Battle::setupBattle(std::vector<Enemy> enemyList, Player& player, std::vector<Ally*>& ally)
{
	//TODO Open file and get ally attacks 
	//TODO Create function that updates the textures of circles (for skills) for when the ally moves to a different grid place
	
	//Initialize for clearing all previous battle data
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	enemies.clear();

	//Initialize for req default data
	currentSkill = 0;
	playerCanAttack = true;
	currentEnemySelected = 0;
	animComplete = hpComplete = false;

	//Gets ally number
	totalAlly = 1;
	for(int idx = 0; idx < ally.size(); idx++)
	{
		if(ally[idx]->getAllyInParty())
		{
			totalAlly++;
		}
	}

	//NOTE: THIS IS JUST TO MAKE SURE. BATTLEPOS MUST BE SET DIFFERENTLY AT DEFAULT WHEN ALLIES ARE ADDED TO PARTY
	//Checks for player and ally position overlap. If overlapped, then change the position
	//totalAlly - 1 because I'm checking the player separately
	for(int i = 0; i < totalAlly - 1; i++)
	{
		if(player.getBattlePos() == ally[i]->getBattlePos())
		{
			ally[i]->setBattlePos((ally[i]->getBattlePos() + 1) % 6);
			i = 0;
		}
		//totalAlly = 2 because don't need to check ally with itself
		for(int j = 0; j < totalAlly - 2; j++)
		{
			if(ally[i]->getBattlePos() == ally[j]->getBattlePos())
			{
				ally[j]->setBattlePos((ally[j]->getBattlePos() + 1) % 6);
				//Set i/j to zero to recheck all
				i = 0;
				j = 0;
			}
		}
	}
	
	//Sets enemy and player positions
	for(int i = 0; i < totalAlly - 1; i++)
	{
		ally[i]->setPosition(allyPos[ally[i]->getBattlePos()].x, allyPos[ally[i]->getBattlePos()].y);
	}
	player.setPosition(allyPos[player.getBattlePos()].x, allyPos[player.getBattlePos()].y);

	//Get number of enemies
	srand(time(NULL));
	numEnemies = rand() % 4 + 1;
	
	//Creates 6 circles for skills
	for(int i = 0; i < numSkills; i++)
	{
		allyOptions.push_back(tempCircle);
		allyOptions[i].setRadius(25);
		allyOptions[i].setFillColor(sf::Color(150, 196, 255));
	}

	//Initialize enemies
	for(int i = 0; i < numEnemies; i++)
	{
		//Chooses enemy from list
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

		//Adds enemy
		enemies.push_back(enemyList[index]);
		enemies[i].setPosition(enemyPos[i].x, enemyPos[i].y);
		enemies[i].updatePosition();
	}
}

//*********** BATTLE STATE 0 *********************
//Sets nextAttack based on who is the fastest (-1 for player, -2 if everybody is done)
void Battle::findFastestChar(Player& player, std::vector<Ally*> ally)
{
	int highestAgil = -1;
	nextCharType = -1;
	nextCharCounter = -1;

	//Reset the position of rectangle (for changing position)
	newPos = 0;

	if(playerCanAtk)
	{
		highestAgil = player.getAgility();
		nextCharType = 0;
	}

	//Checks agility for allies
	for(int i = 0; i < totalAlly - 1; i++)
	{
		if(ally[i]->getCanAtk() && ally[i]->getAgility() > highestAgil)
		{
			highestAgil = ally[i]->getAgility();
			nextCharCounter = i;
			nextCharType = 1;
		}
	}

	for(int i = 0; i < numEnemies; i++)
	{
		if(enemies[i].getCanAtk() && highestAgil < enemies[i].getAgility())
		{
			highestAgil = enemies[i].getAgility();
			nextCharCounter = i;
			nextCharType = 2;
		}
	}
}

void Battle::checkForChoice(int& currentBattleState, Player& player, std::vector<Ally*>& ally)
{
	findFastestChar(player, ally);

	switch (nextCharType)
	{
		case -1:
			//All characters have already attacked
			currentBattleState = 4;
			break;
		case 0:
		case 1:
			//Player or ally attack
			currentBattleState = 1;
			break;
		case 2:
			//Enemy attack
			currentBattleState = 2;
			break;
	}
}

//********** BATTLE STATE 1 ****************
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
		allyOptions[i].setFillColor(sf::Color(160, 196, 255));
	}

	//Highlight current
	allyOptions[currentSkill].setFillColor(sf::Color::Blue);
}

void Battle::chooseCurrentSkill(int& currentBattleState)
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(spacePressed)
	{
		currentBattleState++;
	}
}

//*********** BATTLE STATE 1 *********************
void Battle::attackManager(int& currentBattleState, Player& player, std::vector<Ally*>& ally, int& currentState)
{
	switch (nextCharType)
	{
		case -1:
			currentBattleState = 3;
			break;
		case 0:
			playerTurnHandle(currentState);
			playerAttackAnimation(currentBattleState, player);
			break;
		case 1:
			allyTurnHandle(currentState, ally);
			allyAttackAnimation(currentBattleState, ally);
			break;
		case 2:
			enemyTurnHandle();
			enemyAttackAnimation(currentBattleState);
			break;
	}
}

//TODO
void Battle::playerTurnHandle(int& currentState)
{
	switch(currentSkill)
	{
		case 0:
		case 1:
		case 2:
			playerAllyAttackHandle();
			break;
		case 3:
			playerItem();
			break;
		case 4:
			playerChangePos();
			break;
		case 5:
			attemptFlee(currentState);
			break;
	}
}

//TODO
void Battle::allyTurnHandle(int& currentState, std::vector<Ally*>& ally)
{
	switch(currentSkill)
	{
		case 0:
		case 1:
		case 2:
			playerAllyAttackHandle();
			break;
		case 3:
			allyItem(ally);
			break;
		case 4:
			allyChangePos(ally);
			break;
		case 5:
			attemptFlee(currentState);
			break;
	}
}

//TODO
void Battle::enemyTurnHandle()
{
	switch (skillType)
	{
		case 0:
			//basic single target atk
			break;
		case 1:
			//change attributes of enemy
			break;
		case 2:
			//aoe atk all targets
			break;
		case 3:
			//heal ally or self 
			break;
		case 4:
			//change attributes of ally or self
			break;
		case 5:
			//change current position
			break;
	}
}

void Battle::playerAllyAttackHandle()
{	
	switch (skillType)
	{
		case 0:
			//basic single target atk
			break;
		case 1:
			//change attributes of enemy
			break;
		case 2:
			//aoe atk all targets
			break;
		case 3:
			//heal ally or self 
			break;
		case 4:
			//change attributes of ally or self
			break;
		case 5:
			//change current position
			break;
	}
}

//Calculate using the level difference between average of allies and the enemies
void Battle::attemptFlee(int& currentState)
{
	int avgAlly = 0;
	int avgEnem = 0;
	if(avgAlly > rand() % 15 + avgEnem)
	{
		currentState = 4;
	}
}

void Battle::playerItem()
{
	//TODO
}

void Battle::playerChangePos()
{
	//TODO
	blinkTurn = !blinkTurn;

	tme = clk.getElapsedTime();
	currentTime = tme.asMilliseconds();

	if(lastTime + 300 > currentTime)
	{
		lastTime = currentTime;
		if(blinkTurn && lastTime + 300 > currentTime)
		{
			gridRect[newPos].setFillColor(sf::Color::Red);
		}
		else if(!blinkTurn && lastTime + 300 > currentTime)
		{
			gridRect[newPos].setFillColor(sf::Color::Blue);
		}
	}
}

void Battle::allyItem(std::vector<Ally*>& ally)
{
}

void Battle::allyChangePos(std::vector<Ally*>& ally)
{
}

//Player simply moves forward
void Battle::playerAttackAnimation(int& currentBattleState, Player& player)
{
	goalPlace = allyPos[player.getBattlePos()].x - attackXDisp;
	if(player.getPosition().x > goalPlace)
	{
		player.setPosition(player.getPosition().x - 10, player.getPosition().y);
	}
	else
	{
		playerCanAttack = false;
		currentBattleState++;
	}
}

void Battle::allyAttackAnimation(int& currentBattleState, std::vector<Ally*>& ally)
{
	sf::Vector2f current = ally[nextCharCounter]->getPosition();
	
	//Sets the area to stop
	goalPlace = allyPos[nextCharCounter].x - attackXDisp;

	
	//Moves the enemy, otherwise increments battle state
	if(current.x > goalPlace)
	{
		ally[nextCharCounter]->setPosition(current.x - 10, current.y);
	}
	else
	{ 
		ally[nextCharCounter]->setCanAtk(false);
		currentBattleState++;
	}
}

//Enemy simply moves forward
void Battle::enemyAttackAnimation(int& currentBattleState)
{
	sf::Vector2f current = enemies[nextCharCounter].getPosition();
	
	//Sets the area to stop
	goalPlace = enemyPos[nextCharCounter].x + attackXDisp;

	
	//Moves the enemy, otherwise increments battle state
	if(current.x < goalPlace)
	{
		enemies[nextCharCounter].setPosition(current.x + 10, current.y);
	}
	else
	{ 
		enemies[nextCharCounter].setCanAtk(false);
		currentBattleState++;
	}
}

//******** BATTLE STATE 2 **************
//Calculates hp change for enemy and player
void Battle::hpCalculate(int& currentBattleState, Player& player, UIOverlay& overlay)
{
	int tempHpFinal;
	//TODO OLD OLD OLD
	switch (nextAttack)
	{
		case -1:
			//TODO 
			tempHpFinal = enemies[currentEnemySelected].getInitHp() - player.getStrength();
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
			//TODO
			tempHpFinal = initHp - enemies[nextAttack].getStrength();
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

void Battle::allyHpChange(int hpFinal, std::vector<Ally*>& ally, int& currentBattleState)
{
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
	goalPlace = allyPos[player.getBattlePos()].x;
	if(player.getPosition().x < goalPlace)
	{
		player.setPosition(player.getPosition().x + 10, player.getPosition().y);
	}
	else
	{
		animComplete = true;
	}
}

void Battle::allyPostAttackAnimation(std::vector<Ally*>& ally)
{
}

void Battle::enemyPostAttackAnimation()
{
	sf::Vector2f current = enemies[nextCharCounter].getPosition();
	
	//Sets the area to stop
	goalPlace = enemyPos[nextCharCounter].x;
	
	//Moves the enemy, otherwise increments battle state
	if(current.x > goalPlace)
	{
		enemies[nextCharCounter].setPosition(current.x - 10, current.y);
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

//Just sets ally to dead if less than 0 hp. Doesn't matter in terms of game over
void Battle::checkAllyDeath(std::vector<Ally*>& ally)
{
	for(int i = 0; i < totalAlly - 1; i++)
	{
		if(ally[i]->getCurrentHp() < 1)
		{
			ally[i]->setAlive(false);
		}
	}
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

void Battle::checkEndBattle(Player& player, std::vector<Ally*>& ally, int& currentBattleState, int& currentState)
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
		checkAllyDeath(ally);
		newTurn(ally);
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

//Sets up for new turn by resetting all canAtk flags
void Battle::newTurn(std::vector<Ally*>& ally)
{
	playerCanAttack = true;
	for(int i = 0; i < totalAlly - 1; i++)
	{
		if(ally[i]->getAlive())
		{
			ally[i]->setCanAtk(true);
		}
	}
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

//TODO has to be called
void Battle::setCirclePos()
{
	//TODO set circlePosition
	for(int i = 0; i < numSkills; i++)
	{
		allyOptions[i].setPosition(optionsPos[i] + allyPos[totalAlly]);
	}
}

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
	if(currentBattleState == 1)
	{
		for(int i = 0; i < numSkills; i++)
		{
			win.draw(allyOptions[i]);
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
	else if(numTwo == numOne)
	{
		//If both numbers are equal, return one randomly
		if((rand() % 2) == 0)
		{
			return numOne;
		}
		else
		{
			return numTwo;
		}
	}
}
