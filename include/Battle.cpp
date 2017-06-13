#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Battle.h"

Battle::Battle()
{
	//Default initializations
	currentOptionShow = 0;
	currentOptionAlly = 0;
	currentOptionEnem = 0;

	currentTime = lastTime = 0;
	newPos = 0;
	blinkTurn = true;
	goalPlace = 0;
	currentTarget = 0;
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	singularAllyFocus = false;
	singularEnemyFocus = false;
	
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

	//Creates 6 circles for skills
	for(int i = 0; i < 6; i++)
	{
		allyOptions.push_back(new sf::CircleShape);
		allyOptions[i]->setRadius(25);
		allyOptions[i]->setFillColor(sf::Color(150, 196, 255));
	}

	//Seeding
	srand(time(NULL));
}

void Battle::setupBattle(std::vector<Character> enemyList, std::vector<Character*>& allyList, std::vector<Skill> allySkillTemp, std::vector<Skill> enemySkillTemp)
{
	//TODO Open file and get ally attacks 
	//TODO Create function that updates the textures of circles (for skills) for when the ally moves to a different grid place
	
	//Initialize for clearing all previous battle data
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	enemies.clear();

	//Initialize for req default data
	currentOptionAlly = 0;
	animComplete = false;

	//Store skill sets
	allySkill = allySkillTemp;
	enemySkill = enemySkillTemp;

	//BATTLEPOS MUST BE SET DIFFERENTLY AT DEFAULT WHEN ALLIES ARE ADDED TO PARTY

	//Sets ally positions
	for(int i = 0; i < ally.size(); i++)
	{
		ally[i]->setPosition(allyPos[ally[i]->getBattlePos()].x, allyPos[ally[i]->getBattlePos()].y);
	}

	//Initialize enemies
	int numEnemies = rand() % 4 + 1;
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
		//TODO random set position
		enemies[i].setPosition(enemyPos[i].x, enemyPos[i].y);
		enemies[i].updatePositionBattle();
	}
	ally = allyList;
}

//*********** BATTLE STATE 0 *********************
//Finds fastest character and stores in nextCharType and nextCharCounter
void Battle::findFastestChar()
{
	int highestAgil = -1;
	nextCharType = -1;
	nextCharCounter = -1;

	//Reset the position of rectangle (for changing position)
	newPos = 0;

	//Checks agility for allies
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getCanAtk() && ally[i]->getAgility() > highestAgil)
		{
			highestAgil = ally[i]->getAgility();
			nextCharCounter = i;
			nextCharType = 0;
		}
	}

	//Checks agility for enemies
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i].getCanAtk() && highestAgil < enemies[i].getAgility())
		{
			highestAgil = enemies[i].getAgility();
			nextCharCounter = i;
			nextCharType = 1;
		}
	}
}

void Battle::checkForStatus(int nextCharType)
{
}

void Battle::checkForNextChar(int& currentBattleState)
{
	findFastestChar();

	switch (nextCharType)
	{
		case 0:
			//Ally attack
			//TODO Check for status here
			currentBattleState = 1;
		case 1:
			//Enemy attack
			//TODO Check for status here
			currentBattleState = 3;
			break;
	}
}

//********** BATTLE STATE 1 ****************
void Battle::setCirclePos()
{
	for(int i = 0; i < allyOptions.size(); i++)
	{
		allyOptions[i]->setPosition(optionsPos[i] + allyPos[nextCharCounter]);
	}
}

void Battle::changeCurrentSkill()
{
	//Moves circle to the current ally
	setCirclePos();

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

	//If key was released before being typed again
	if(wPressed && wNotPressed)
	{
		wNotPressed = false;
		currentOptionAlly--;
		
		//Special exceptions
		if(currentOptionAlly == -1)
		{
			currentOptionAlly = 0;
		}
		else if(currentOptionAlly == 2)
		{
			currentOptionAlly = 3;
		}
	}
	if(aPressed && aNotPressed)
	{
		aNotPressed = false;
		currentOptionAlly -= 3;

		//Special exceptions
		if(currentOptionAlly < 0)
		{
			currentOptionAlly += 3;
		}
	}
	if(sPressed && sNotPressed)
	{
		sNotPressed = false;
		currentOptionAlly++;
		
		//Special exceptions
		if(currentOptionAlly == 6)
		{
			currentOptionAlly = 5;
		}
		else if(currentOptionAlly == 3)
		{
			currentOptionAlly = 2;
		}
	}
	if(dPressed && dNotPressed)
	{
		dNotPressed = false;
		currentOptionAlly += 3;

		//Special exceptions
		if(currentOptionAlly > 5)
		{
			currentOptionAlly -= 3;
		}
	}
	
	//Reset all colors
	for(int i = 0; i < allyOptions.size(); i++)
	{
		allyOptions[i]->setFillColor(sf::Color(160, 196, 255));
	}

	//Highlight current
	allyOptions[currentOptionAlly]->setFillColor(sf::Color::Blue);
}

void Battle::chooseCurrentSkill(int& currentBattleState)
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(!spacePressed)
	{
		spaceNotPressed = true;
	}


	//Go to next battle state with currentOptionAlly storing the skill to use
	if(spacePressed && spaceNotPressed)
	{
		spaceNotPressed = false;
		currentBattleState++;
	}
}

//*********** BATTLE STATE 2 *********************
void Battle::attackEnemyType()
{
	if(singularAllyFocus)
	{
		changeAllyFocus();
	}
	else if (singularEnemyFocus)
	{
		changeEnemyFocus();
	}
	else
	{
		int skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
		int targetType = allySkill[skillNum].checkForSelection();
		switch(targetType)
		{
			case 0:
				singularAllyFocus = true;
				break;
			case 1:
				singularEnemyFocus = true;
				break;
		}
	}
}

void Battle::changeAllyFocus()
{
	//TODO Change from q press to WASD pressing
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	
	if(!qPressed)
	{
		qNotPressed = true;
	}

	//Initialize current target
	do
	{
		currentTarget++;
		if(currentTarget >= ally.size())
		{
			currentTarget = 0;
		}
	}while(!(ally[currentTarget]->getAlive()));


	//If q pressed, swap to next enemy that is not dead
	if(qPressed && qNotPressed)
	{
		qNotPressed = false;
		do
		{
			currentTarget++;
			if(currentTarget >= ally.size())
			{
				currentTarget = 0;
			}
		}while(!(enemies[currentTarget].getAlive()));
	}
}

void Battle::changeEnemyFocus()
{
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	
	if(!qPressed)
	{
		qNotPressed = true;
	}

	//Initialize current target
	do
	{
		currentTarget++;
		if(currentTarget >= enemies.size())
		{
			currentTarget = 0;
		}
	}while(!(enemies[currentTarget].getAlive()));

	//If q pressed, swap to next enemy that is not dead
	if(qPressed && qNotPressed)
	{
		qNotPressed = false;
		do
		{
			currentTarget++;
			if(currentTarget >= enemies.size())
			{
				currentTarget = 0;
			}
		}while(!(enemies[currentTarget].getAlive()));
	}
}

void Battle::chooseEnemyFocus(int& currentBattleState)
{
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(!spacePressed)
	{
		spaceNotPressed = true;
	}

	if(spacePressed && spaceNotPressed)
	{
		spaceNotPressed = false;
		currentBattleState++;
	}
}

//*********** BATTLE STATE 3 *********************
void Battle::attackManager(int& currentBattleState, int& currentState)
{
	switch (nextCharType)
	{
		case 0:
			allyTurnHandle(currentState, currentBattleState);
			break;
		case 1:
			enemyChooseSkill();
			enemyChooseTarget();
			enemyAttackAnimation(currentBattleState);
			break;
	}
}

void Battle::allyTurnHandle(int& currentState, int& currentBattleState)
{
	switch(currentOptionAlly)
	{
		case 0:
		case 1:
		case 2:
			break;
		case 3:
			break;
		case 4:
			allyAttackAnimation(currentBattleState);
			break;
		case 5:
			attemptFlee(currentState);
			break;
	}
			allyChangePos();
			allyItem();
}

//Calculate using the level difference between average of allies and the enemies
void Battle::attemptFlee(int& currentState)
{
	int avgAlly = 0;
	int avgEnem = 0;
	for(int i = 0; i < ally.size(); i++)
	{
		avgAlly += ally[i]->getLevel();
	}
	avgAlly /= (ally.size() + 1);

	for(int i = 0; i < enemies.size(); i++)
	{
		avgEnem += enemies[i].getLevel();
	}
	avgEnem  /= (enemies.size() + 1);

	int randChance = rand() % 15 + 85;
	if(avgAlly * randChance > avgEnem)
	{
		//TODO end the game properly
		currentState = 5;
	}
}

void Battle::allyChangePos()
{
	//TODO make the grid blink to display where to move to
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

void Battle::allyItem()
{
}

void Battle::allyAttackAnimation(int& currentBattleState)
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

void Battle::enemyChooseSkill()
{
	int totalSkill = 0;
	//Add up all the chances of the skills
	for(int i = 0; i < enemies[nextCharCounter].getSkillNum().size(); i++)
	{
		totalSkill += enemySkill[enemies[nextCharCounter].getSkillNum()[i]].getChance();
	}

	//Get random number between 0 and the the totalSkill
	int chanceRoll = rand() % totalSkill;
	
	//If the random number is less than the current skill chance (plus all the previous chances), that skill is chosen
	int pastSkills = 0;
	for(int i = 0; i < enemies[nextCharCounter].getSkillNum().size(); i++)
	{
		int currentChance = enemySkill[enemies[nextCharCounter].getSkillNum()[i]].getChance();
		pastSkills += currentChance;
		if(pastSkills < chanceRoll)
		{
			currentOptionEnem = i;
		}
	}
}

void Battle::enemyChooseTarget()
{
	std::vector<int> allyInFront;
	std::vector<int> allyInBack;

	for(int i = 0; i < ally.size(); i++)
	{
		//Segregate allies into back and front sections
		if(ally[i]->getAlive())
		{
			if((ally[i]->getBattlePos()) <= 2)
			{
				allyInFront.push_back(i);
			}
			else
			{
				allyInBack.push_back(i);
			}
		}
	}

	//If there are allies in the front row, there is a 2/3 chance of the ally being selected from the front and 1/3 chance of the ally being selected from the back
	if(allyInFront.size() > 0)
	{
		if((rand() % 3) <= 1)
		{
			currentAllySelected.push_back(allyInFront[rand() % allyInFront.size()]);
		}
		else
		{
			currentAllySelected.push_back(allyInBack[rand() % allyInBack.size()]);
		}
	}
	//Just choose a character randomly
	else
	{
		currentAllySelected.push_back(allyInBack[rand() % allyInBack.size()]);
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

//******** BATTLE STATE 4 **************
//Calculates hp/mana change for enemy and ally
void Battle::effectCalc(int& currentBattleState)
{
	//TODO Apply effect for both enemies AND allies
	//TODO get mana change as well

	for(int i = 0; i < currentAllySelected.size(); i++)
	{
		if(nextCharType == 0)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetHp = ally[currentAllySelected[i]]->getCurrentHp();
			//Skill checks for both type 0 and type 1 (healing and damaging) for enemies and allies
			ally[i]->setHpChange(allySkill[currentOptionAlly].healthChangeHandle(allyStrength, 0, targetHp));
		}
		else if(nextCharType == 1)
		{
			int enemyStrength = enemies[nextCharCounter].getStrength();
			int targetDef = ally[currentAllySelected[i]]->getDefense();
			int targetHp = ally[currentAllySelected[i]]->getCurrentHp();
			ally[i]->setHpChange(enemySkill[currentOptionEnem].healthChangeHandle(enemyStrength, targetDef, targetHp));
		}
	}

	for(int i = 0; i < currentEnemySelected.size(); i++)
	{
		if(nextCharType == 0)
		{
			int allyStrength = enemies[nextCharCounter].getStrength();
			int targetDef = ally[currentEnemySelected[i]]->getDefense();
			int targetHp = ally[currentEnemySelected[i]]->getCurrentHp();
			enemies[i].setHpChange(allySkill[currentOptionAlly].healthChangeHandle(allyStrength, targetDef, targetHp));
		}
		if(nextCharType == 1)
		{
			int enemyStrength = enemies[nextCharCounter].getStrength();
			int targetHp = enemies[currentEnemySelected[i]].getCurrentHp();
			enemies[i].setHpChange(enemySkill[currentOptionEnem].healthChangeHandle(enemyStrength, 0, targetHp));
		}
	}
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

void Battle::allyHpChange(int& currentBattleState)
{
	int hpFinal = ally[i]->getHpChange();
	int sign = findHpChangeSign(hpFinal, ally[currentAllySelected].getCurrentHp());
	if(ally[currentAllySelected].getCurrentHp() > hpFinal + 3 || ally[currentAllySelected].getCurrentHp() < hpFinal - 3)
	{
		ally[currentAllySelected].setCurrentHp(ally[currentAllySelected].getCurrentHp() + (3 * sign), overlay);
	}
	else if (ally[currentAllySelected].getCurrentHp() != hpFinal)
	{
		ally[currentAllySelected].setCurrentHp(hpFinal, overlay);
	}
}

void Battle::enemyHpChange(int& currentBattleState)
{
	for(int i = 0; i < currentEnemySelected.size(); i++)
	{
		int hpFinal = enemies[currentEnemySelected[i]].getHpChange();
		int currentEnemyHp = enemies[currentEnemySelected[i]].getCurrentHp();
		if(hpFinal != currentEnemyHp)
		{
			int sign = findHpChangeSign(hpFinal, currentEnemyHp);
			if(currentEnemyHp > hpFinal + 3 || currentEnemyHp < hpFinal - 3)
			{
				enemies[currentEnemySelected].setCurrentHp(currentEnemyHp + (3 * sign));
			}
			else if (currentEnemyHp != hpFinal)
			{
				enemies[currentEnemySelected].setCurrentHp(hpFinal);
			}
		}
	}
}

void Battle::allyPostAttackAnimation()
{
	goalPlace = allyPos[ally[nextCharCounter]->getBattlePos()].x;
	if(ally[nextCharCounter]->getPosition().x < goalPlace)
	{
		ally[nextCharCounter]->setPosition(ally[nextCharCounter]->getPosition().x + 10, ally[nextCharCounter]->getPosition().y);
	}
	else
	{
		animComplete = true;
	}
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
	bool allDone = true;

	for(int i = 0; i < currentAllySelected.size(); i++)
	{
		int currentHp = ally[currentAllySelected[i]].getCurrentHp();
		int targetHp = ally[currentAllySelected[i]].getHpChange();
		if(currentHp != targetHp)
		{
			allDone = false;
		}
	}

	for(int i = 0; i < currentEnemySelected.size(); i++)
	{
		int currentHp = enemy[currentEnemySelected[i]].getCurrentHp();
		int targetHp = enemy[currentEnemySelected[i]].getHpChange();
		if(currentHp != targetHp)
		{
			allDone = false;
		}
	}

	if(allDone && animComplete)
	{
		animComplete = false;
		currentBattleState = 1;
	}
	
}

//*************** BATTLE STATE 5 *********************
//Sets ally to dead if less than 0 hp. Returns true if all allies are dead
bool Battle::checkAllyDeath()
{
	bool allDead = true;
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getCurrentHp() < 1)
		{
			ally[i]->setAlive(false);
		}
		else
		{
			allDead = false;
		}
	}
	return allDead;
}

//Returns true if all enemies are dead
bool Battle::checkEnemyDeaths()
{
	bool allDead = true;

	for(int i = 0 ; i < enemies.size(); i++)
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

void Battle::checkEndBattle(int& currentBattleState, int& currentState)
{
	if(checkAllyDeath())
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
	if(!enemies[currentTarget].getAlive())
	{
		do
		{
			currentTarget++;
			if(currentTarget >= enemies.size())
			{
				currentTarget = 0;
			}
		}while(!enemies[currentTarget].getAlive());
	}
}

//Sets up for new turn by resetting all canAtk flags for those who are still alive
void Battle::newTurn()
{
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			ally[i]->setCanAtk(true);
		}
	}
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i].getAlive())
		{
			enemies[i].setCanAtk(true);
		}
	}
}

//************ DRAWING ***************

void Battle::drawAll(sf::RenderWindow& win, int currentBattleState)
{
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			ally[i]->drawSpriteBattle(win);
		}
	}

	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i].getAlive())
		{
			enemies[i].drawSpriteBattle(win);
		}
	}

	if(currentBattleState == 2)
	{
		for(int i = 0; i < allyOptions.size(); i++)
		{
			win.draw(*allyOptions[i]);
		}
	}
}

//*************** MUTATORS ******************

void Battle::setEnemyHp(int enemyNum, int newHp)
{
	enemies[enemyNum].setCurrentHp(newHp);
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
