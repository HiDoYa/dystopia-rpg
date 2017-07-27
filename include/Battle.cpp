#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cmath>

#include "Battle.h"

Battle::Battle()
{
	//Default initializations
	currentPlayerForOption = 0;
	currentOptionAlly = 0;
	currentOptionEnemy = 0;
	currentSkillCheck = 0;
	oldBattlePos = -1;
	lastTimeSet = false;

	currentTime = lastTime = 0;
	goalPlace = 0;
	singularAllyFocus = false;
	singularEnemyFocus = false;
	
	//Displacement during character turn
	attackXDisp = 150;

	//TODO Set colors
	gridDefault = sf::Color(sf::Color::White);
	allyOptionSelect = sf::Color(sf::Color::Blue);
	allyOptionDeselect = sf::Color(150, 196, 255);

	//Ally positions
	allyPos = {sf::Vector2f(674, 200),
		   sf::Vector2f(674, 350),
		   sf::Vector2f(674, 500),
		   sf::Vector2f(874, 200),
		   sf::Vector2f(874, 350),
		   sf::Vector2f(874, 500)};

	//Enemy Positions
	enemyPos = {sf::Vector2f(100, 200),
		    sf::Vector2f(100, 350),
		    sf::Vector2f(100, 500),
		    sf::Vector2f(300, 200),
		    sf::Vector2f(300, 350),
		    sf::Vector2f(300, 500)};

	//Options positions
	std::vector<sf::Vector2f> optionsPos;
	optionsPos = {sf::Vector2f(50, 20),
		      sf::Vector2f(150, 20),
		      sf::Vector2f(250, 20),
		      sf::Vector2f(350, 20),
		      sf::Vector2f(450, 20),
		      sf::Vector2f(550, 20)};

	//Creates 6 circles for skills
	for(int i = 0; i < 6; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton(1));

		tempPtr->getCirc()->setRadius(30);
		tempPtr->setHoverText(true);
		tempPtr->getHoverText()->setCharacterSize(10);
		tempPtr->getHoverText()->setColor(sf::Color::Black);
		tempPtr->getCirc()->setPosition(optionsPos[i]);

		//X pos doesn't matter because it'll be set up later
		tempPtr->getHoverText()->setPosition(0, optionsPos[i].y + 70);

		allyOptions.push_back(tempPtr);
	}

	allyOptions[3]->getHoverText()->setString("Items");
	allyOptions[4]->getHoverText()->setString("Move");
	allyOptions[5]->getHoverText()->setString("Run");

	for(int i = 0; i < 6; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr->getRect()->setOutlineColor(sf::Color::Black);
		tempPtr->getRect()->setOutlineThickness(2);
		tempPtr->getRect()->setFillColor(gridDefault);
		tempPtr->getRect()->setSize(sf::Vector2f(150, 150));
		chooseAlly.push_back(tempPtr);
	}

	chooseAlly[0]->getRect()->setPosition(sf::Vector2f(624, 120));
	chooseAlly[1]->getRect()->setPosition(sf::Vector2f(624, 270));
	chooseAlly[2]->getRect()->setPosition(sf::Vector2f(624, 420));
	chooseAlly[3]->getRect()->setPosition(sf::Vector2f(824, 120));
	chooseAlly[4]->getRect()->setPosition(sf::Vector2f(824, 270));
	chooseAlly[5]->getRect()->setPosition(sf::Vector2f(824, 420));

	for(int i = 0; i < 6; i++)
	{
		std::shared_ptr<ClickButton> tempPtr (new ClickButton);
		tempPtr->getRect()->setOutlineColor(sf::Color::Black);
		tempPtr->getRect()->setOutlineThickness(2);
		tempPtr->getRect()->setFillColor(gridDefault);
		tempPtr->getRect()->setSize(sf::Vector2f(150, 150));
		chooseEnemy.push_back(tempPtr);
	}

	chooseEnemy[0]->getRect()->setPosition(sf::Vector2f(50, 120));
	chooseEnemy[1]->getRect()->setPosition(sf::Vector2f(50, 270));
	chooseEnemy[2]->getRect()->setPosition(sf::Vector2f(50, 420));
	chooseEnemy[3]->getRect()->setPosition(sf::Vector2f(250, 120));
	chooseEnemy[4]->getRect()->setPosition(sf::Vector2f(250, 270));
	chooseEnemy[5]->getRect()->setPosition(sf::Vector2f(250, 420));

	//Seeding
	srand(time(NULL));
}

void Battle::setupBattle(std::vector<std::shared_ptr<Character>> enemyList,
		std::vector<std::shared_ptr<Character>>& allyList,
		std::vector<std::shared_ptr<Skill>> skillTemp, std::vector<int> allyInParty)
{
	std::cout << "setupBattle\n";

	singularAllyFocus = singularEnemyFocus = false;
	//TODO Create function that updates the textures of circles (for skills) for when the ally moves to a different grid place
	
	//Initialize for clearing all previous battle data
	enemy.clear();

	//Initialize for req default data
	currentOptionAlly = 0;

	//Store skill sets
	skillList = skillTemp;

	for(int i = 0; i < allyInParty.size(); i++)
	{
		std::shared_ptr<Character> tempPtr (new Character);
		allyList[allyInParty[i]]->copy(tempPtr);
		ally.push_back(tempPtr);
	}

	//BATTLEPOS MUST BE SET DIFFERENTLY AT DEFAULT WHEN ALLIES ARE ADDED TO PARTY
	//Sets ally positions
	//TODO set battle position for allies in files
	for(int i = 0; i < ally.size(); i++)
	{
		//Make sure scale is set to 1-1
		ally[i]->setScale(1, 1);
		int allyBattlePos = ally[i]->getBattlePos();
		ally[i]->setPosition(allyPos[allyBattlePos].x, allyPos[allyBattlePos].y);
	}

	//Initialize enemy
	int numEnemies = rand() % 5 + 1;
	for(int i = 0; i < numEnemies; i++)
	{
		//Chooses enemy from list
		int maxRandChance = 0;
		int index = 0;
		for(int potentialEnemy = 0; potentialEnemy < enemyList.size(); potentialEnemy++)
		{
			int tempNum = ((rand() % 100) + 1) * enemyList[potentialEnemy]->getChance();
			if(tempNum > maxRandChance)
			{
				maxRandChance = tempNum;
				index = potentialEnemy;
			}
		}

		//Adds enemy
		std::shared_ptr<Character> tempPtr (new Character);
		enemyList[index]->copy(tempPtr);
		enemy.push_back(tempPtr);

		//TODO random set position
		bool foundRand;
		int posTemp;

		do
		{
			foundRand = true;
			posTemp = rand() % 6;
			for(int i = 0; i < enemy.size(); i++)
			{
				if(enemy[i]->getBattlePos() == posTemp)
				{
					foundRand = false;
					break;
				}
			}
		} while(!foundRand);

		enemy[i]->setBattlePos(posTemp);
		enemy[i]->setPosition(enemyPos[posTemp].x, enemyPos[posTemp].y);
	}
}

//*********** BATTLE STATE 0 *********************
//Finds fastest character and stores in nextCharType and nextCharCounter
void Battle::findFastestChar(int& nextBattleState)
{
	std::cout << "findFastestChar\n";
	int highestAgil = -1;
	nextCharType = -1;
	nextCharCounter = -1;

	//Checks agility for allies
	for(int i = 0; i < ally.size(); i++)
	{
		int allyAgil = ally[i]->getAgility();
		if(ally[i]->getCanAtk() && allyAgil > highestAgil && ally[i]->getAlive())
		{
			highestAgil = allyAgil;
			nextCharCounter = i;
			nextCharType = 0;
		}
	}

	//Checks agility for enemy
	for(int i = 0; i < enemy.size(); i++)
	{
		int enemAgil = enemy[i]->getAgility();
		if(enemy[i]->getCanAtk() && enemAgil > highestAgil && enemy[i]->getAlive())
		{
			highestAgil = enemAgil;
			nextCharCounter = i;
			nextCharType = 1;
		}
	}

	//If everybody is done attacking
	if(nextCharType == -1)
	{
		for(int i = 0; i < ally.size(); i++)
		{
			if(ally[i]->getAlive())
			{
				ally[i]->setCanAtk(true);
			}
		}
		for(int i = 0; i < enemy.size(); i++)
		{
			if(enemy[i]->getAlive())
			{
				enemy[i]->setCanAtk(true);
			}
		}
	}
	//Set flag to false
	else if(nextCharType == 0)
	{
		ally[nextCharCounter]->setCanAtk(false);

		setSkillNames();

		//Current state is done
		nextBattleState = 1;
	}
	else if(nextCharType == 1)
	{
		enemy[nextCharCounter]->setCanAtk(false);

		//Current state is done
		nextBattleState = 1;
	}
}

void Battle::setSkillNames()
{
	for(int i = 0; i < 3; i++)
	{
		std::string skillName = skillList[ally[nextCharCounter]->getSkillNum()[i]]->getName();
		allyOptions[i]->getHoverText()->setString(skillName);
	}
}

//********** BATTLE STATE 1 ****************
void Battle::statusHandle(int& nextBattleState)
{
	std::cout << "statusHandle\n";
	checkForStatus();

	switch (nextCharType)
	{
		case 0:
			//Ally attack
			nextBattleState = 2;
			break;
		case 1:
			//Enemy attack
			nextBattleState = 4;
			break;
	}
}

void Battle::checkForStatus()
{
	std::cout << "checkforStatus\n";
	switch (nextCharType)
	{
		case 0:
			if(ally[nextCharCounter]->getPersistentSkillNum().size() > 0)
			{
				allyStatusEffect();
			}
			break;
		case 1:
			if(enemy[nextCharCounter]->getPersistentSkillNum().size() > 0)
			{
				enemyStatusEffect();
			}
			break;
	}
}

//TODO What if two characters have the same ability and both use oldVal? maybe recalculate for status effect?
void Battle::allyStatusEffect()
{
	std::cout << "allyStatusEffect\n";
	for(int i = 0; i < ally[nextCharCounter]->getPersistentSkillNum().size(); i++)
	{
		ally[nextCharCounter]->decrementNumTurnsSkill(i);
		int numTurnsRemaining = ally[nextCharCounter]->getNumTurnsSkill()[i];
		for(int j = 0; j < 4; j++)
		{
			std::shared_ptr<Skill> currentPersistentSkill = skillList[ally[nextCharCounter]->getPersistentSkillNum()[i]];
			int reapplyNumTurns = currentPersistentSkill->getReapplyTurn()[j];
			if(reapplyNumTurns > 0)
			{
				//Damage or heal
				if((j == 0 || j == 1) && numTurnsRemaining > 0)
				{
					ally[nextCharCounter]->setCurrentHp(ally[nextCharCounter]->getCurrentHp() + currentPersistentSkill->getOldVal()[j]);
				}
				//Buff or debuff
				//If the debuff duration is over, return the stats to normal
				else if((j == 2 || j == 3) && numTurnsRemaining == 0)
				{
					int statType;
					if(j == 2)
					{
						statType = currentPersistentSkill->getDebuffType();
					}
					else if(j == 3)
					{
						statType = currentPersistentSkill->getBuffType();
					}
					
					if(statType == 0)
					{
						ally[nextCharCounter]->setStrength(ally[nextCharCounter]->getStrength() + currentPersistentSkill->getOldVal()[j]);
					}
					else if(statType == 1)
					{
						ally[nextCharCounter]->setDefense(ally[nextCharCounter]->getDefense() + currentPersistentSkill->getOldVal()[j]);
					}
					else if(statType == 2)
					{
						ally[nextCharCounter]->setAgility(ally[nextCharCounter]->getAgility() + currentPersistentSkill->getOldVal()[j]);
					}
				//Do nothing if debuff isn't over yet
				}
			}
		}
		if(numTurnsRemaining == 0)
		{
			std::vector<int> persistDelete = enemy[nextCharCounter]->getPersistentSkillNum();
			persistDelete.erase(persistDelete.begin() + i);
			enemy[nextCharCounter]->setPersistentSkillNum(persistDelete);
			i--;
		}

	}
}

void Battle::enemyStatusEffect()
{
	std::cout << "enemyStatusEffect\n";
	for(int i = 0; i < enemy[nextCharCounter]->getPersistentSkillNum().size(); i++)
	{
		enemy[nextCharCounter]->decrementNumTurnsSkill(i);
		int numTurnsRemaining = enemy[nextCharCounter]->getNumTurnsSkill()[i];
		for(int j = 0; j < 4; j++)
		{
			std::shared_ptr<Skill> currentPersistentSkill = skillList[enemy[nextCharCounter]->getPersistentSkillNum()[i]];
			int reapplyNumTurns = currentPersistentSkill->getReapplyTurn()[j];
			if(reapplyNumTurns > 0)
			{
				//Damage or heal
				if((j == 0 || j == 1) && numTurnsRemaining > 0)
				{
					enemy[nextCharCounter]->setCurrentHp(enemy[nextCharCounter]->getCurrentHp() + currentPersistentSkill->getOldVal()[j]);
				}
				//Buff or debuff
				//If the debuff duration is over, return the stats to normal
				else if((j == 2 || j == 3) && numTurnsRemaining == 0)
				{
					int statType;
					if(j == 2)
					{
						statType = currentPersistentSkill->getDebuffType();
					}
					else if(j == 3)
					{
						statType = currentPersistentSkill->getBuffType();
					}

					if(statType == 0)
					{
						enemy[nextCharCounter]->setStrength(enemy[nextCharCounter]->getStrength() + currentPersistentSkill->getOldVal()[j]);
					}
					else if(statType == 1)
					{
						enemy[nextCharCounter]->setDefense(enemy[nextCharCounter]->getDefense() + currentPersistentSkill->getOldVal()[j]);
					}
					else if(statType == 2)
					{
						enemy[nextCharCounter]->setAgility(enemy[nextCharCounter]->getAgility() + currentPersistentSkill->getOldVal()[j]);
					}
					//Do nothing if debuff isn't over yet
				}
			}
		}
		if(numTurnsRemaining == 0)
		{
			std::vector<int> persistDelete = enemy[nextCharCounter]->getPersistentSkillNum();
			persistDelete.erase(persistDelete.begin() + i);
			enemy[nextCharCounter]->setPersistentSkillNum(persistDelete);
			i--;
		}
	}
}
//********** BATTLE STATE 2 ****************
void Battle::allySkillChoiceHandler(int& nextBattleState, sf::RenderWindow& win)
{
	std::cout << "allySkillChoiceHandler\n";

	for(int i = 0; i < allyOptions.size(); i++)
	{
		allyOptions[i]->centerHoverHorizontal();
		if(allyOptions[i]->mouseClickedInButton(allyOptionSelect, allyOptionDeselect, win)) {
			currentOptionAlly = i;
			if(i < 3)
			{
				//Skills
				nextBattleState = 3;
			}
			else
			{
				//Not skills
				nextBattleState = 6;
			}
		}
	}
}

//*********** BATTLE STATE 3 *********************
void Battle::allyChooseFocus(int& nextBattleState, sf::RenderWindow& win)
{
	std::cout << "allyChooseFocus\n";

	//Look for singular focus if both bools are false
	if(!singularAllyFocus && !singularEnemyFocus)
	{
		findSingularFocus();
	}

	//Only choose who to focus if bools are true. Otherwise, just skip to battle state 5
	if(singularAllyFocus)
	{
		if(changeAllyFocus(win))
		{
			resetGrid();
			nextBattleState = 5;
		}
	}
	else if(singularEnemyFocus)
	{
		if(changeEnemyFocus(win))
		{
			resetGrid();
			nextBattleState = 5;
		}
	}
	else
	{
		resetGrid();
		nextBattleState = 5;
	}
}

void Battle::findSingularFocus()
{
	std::cout << "findSingularFocus\n";

	int skillNum = 0;

	if(nextCharType == 0)
	{
		skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
	}
	else if(nextCharType == 1)
	{
		skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionAlly];
	}

	for(int i = 0; i < 4; i++)
	{
		bool skillMult = skillList[skillNum]->getMult()[i] > 0;
		int skillTarget = skillList[skillNum]->getTarget()[i];
		if(skillMult && skillTarget == 0)
		{
			singularAllyFocus = true;
		}
		else if(skillMult && skillTarget == 1)
		{
			singularEnemyFocus = true;
		}
	}
}

bool Battle::changeAllyFocus(sf::RenderWindow& win)
{
	std::cout << "changeAllyFocus\n";
	bool pressed = false;

	for(int i = 0; i < chooseAlly.size(); i++)
	{
		for(int j = 0; j < ally.size(); j++)
		{
			if(ally[j]->getAlive() && ally[j]->getBattlePos() == i)
			{
				if(chooseAlly[i]->mouseClickedInButton(allyOptionSelect, allyOptionDeselect, win))
				{
					pressed = true;
					currentAllySelected = j;
					break;
				}
			}
		}
	}

	return pressed;
}

bool Battle::changeEnemyFocus(sf::RenderWindow& win)
{
	std::cout << "changeEnemyFocus\n";
	bool pressed = false;

	for(int i = 0; i < chooseEnemy.size(); i++)
	{
		for(int j = 0; j < enemy.size(); j++)
		{
			if(enemy[j]->getBattlePos() == i && enemy[j]->getAlive())
			{
				if(chooseEnemy[i]->mouseClickedInButton(allyOptionSelect, allyOptionDeselect, win))
				{
					pressed = true;
					currentEnemySelected = j;
					break;
				}
			}
		}
	}

	return pressed;
}

void Battle::resetGrid()
{
	for(int i = 0; i < 6; i++)
	{
		chooseAlly[i]->getRect()->setFillColor(gridDefault);
		chooseEnemy[i]->getRect()->setFillColor(gridDefault);
	}
}

//*********** BATTLE STATE 4 *********************
void Battle::enemyDecision(int& nextBattleState)
{
	std::cout << "enemyDecision\n";
	enemyChooseSkill();
	for(int i = 0; i < 4; i++)
	{
		if(skillList[currentOptionEnemy]->getMult()[i] > 0)
		{
			if(skillList[currentOptionEnemy]->getTarget()[i] == 0)
			{
				enemyChooseAlly();
			}
			else if(skillList[currentOptionEnemy]->getTarget()[i] == 1)
			{
				enemyChooseEnemy();
			}
		}
	}
	nextBattleState = 5;
}

void Battle::enemyChooseSkill()
{
	std::cout << "enemyChooseSkill\n";
	int totalSkill = 0;
	//Add up all the chances of the skills
	for(int i = 0; i < enemy[nextCharCounter]->getSkillNum().size(); i++)
	{
		totalSkill += skillList[enemy[nextCharCounter]->getSkillNum()[i]]->getChance();
	}

	//Get random number between 0 and the the totalSkill
	int chanceRoll = rand() % totalSkill;
	
	//If the random number is less than the current skill chance (plus all the previous chances), that skill is chosen
	int pastSkills = 0;
	for(int i = 0; i < enemy[nextCharCounter]->getSkillNum().size(); i++)
	{
		int currentSkillNumber = enemy[nextCharCounter]->getSkillNum()[i];
		int currentChance = skillList[currentSkillNumber]->getChance();
		pastSkills += currentChance;
		if(pastSkills < chanceRoll)
		{
			currentOptionEnemy = i;
			break;
		}
	}
}

void Battle::enemyChooseAlly()
{
	std::cout << "enemyChooseAlly\n";
	std::vector<int> enemiesAlive;
	for(int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getAlive())
		{
			enemiesAlive.push_back(i);
		}
	}
	currentAllySelected = enemiesAlive[rand() % enemiesAlive.size()];
}

void Battle::enemyChooseEnemy()
{
	std::cout << "enemyChooseEnemy\n";
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
	if(allyInFront.size() > 0 && allyInBack.size() > 0)
	{
	std::cout << allyInFront[0] << '\n';
	std::cout << allyInBack[0] << '\n';
		if((rand() % 3) <= 1)
		{
			currentEnemySelected = allyInFront[rand() % allyInFront.size()];
		}
		else
		{
			currentEnemySelected = allyInBack[rand() % allyInBack.size()];
		}
	}
	//Just choose a character randomly
	else if(allyInFront.size() > 0)
	{
		currentEnemySelected = allyInFront[rand() % allyInFront.size()];
	}
	else if(allyInBack.size() > 0)
	{
		currentEnemySelected = allyInBack[rand() % allyInBack.size()];
	}
}

//*********** BATTLE STATE 5 *********************
void Battle::moveForwardAnimation(int& nextBattleState)
{
	std::cout << "moveForwardAnimation\n";
	switch (nextCharType)
	{
		case 0:
			allyAttackAnimation(nextBattleState);
			break;
		case 1:
			enemyAttackAnimation(nextBattleState);
			break;
	}
}
void Battle::allyAttackAnimation(int& nextBattleState)
{
	std::cout << "allyAttackAnimation\n";
	sf::Vector2f current = ally[nextCharCounter]->getPosition();
	
	//Sets the area to stop
	goalPlace = allyPos[ally[nextCharCounter]->getBattlePos()].x - attackXDisp;
	
	//Moves the enemy, otherwise increments battle state
	if(current.x > goalPlace)
	{
		ally[nextCharCounter]->setPosition(current.x - 10, current.y);
	}
	else
	{ 
		nextBattleState = 6;
	}
}

//Enemy simply moves forward
void Battle::enemyAttackAnimation(int& nextBattleState)
{
	std::cout << "enemyAttackAnimation\n";
	sf::Vector2f current = enemy[nextCharCounter]->getPosition();

	//Sets the area to stop
	goalPlace = enemyPos[enemy[nextCharCounter]->getBattlePos()].x + attackXDisp;

	//Moves the enemy, otherwise increments battle state
	if(current.x < goalPlace)
	{
		enemy[nextCharCounter]->setPosition(current.x + 10, current.y);
	}
	else
	{ 
		nextBattleState = 6;
	}
}

//******** BATTLE STATE 6 **************
//Calculates hp/mana change for enemy and ally
void Battle::handleEffect(int& nextBattleState, sf::RenderWindow& win)
{
	std::cout << "handleEffect\n";

	//Used for allyChangePos
	bool done = false;

	switch(nextCharType)
	{
		case 0:
			done = allyTurnHandle(nextBattleState, win);
			break;
		case 1:
			enemyTurnHandle(nextBattleState);
			done = true;
			break;
	}
	
	if(done)
	{
		nextBattleState = 7;
	}
}

//Returns target type for the next effect of the skill
int Battle::findNextTarget(int skillNum)
{
	std::cout << "findNextTarget\n";

	while(currentSkillCheck < 4)
	{
		if(skillList[skillNum]->getMult()[currentSkillCheck] > 0)
		{
			return skillList[skillNum]->getTarget()[currentSkillCheck];
		}
		currentSkillCheck++;
	}

	currentSkillCheck = 0;

	return -1;
}

//Calls findNextTarget (increments currentSkillCheck) and returns targetType
//If targetType is -1, the current skill check is over
int Battle::processSkillTargetting()
{
	std::cout << "processSkillTargetting\n";
	int skillNum = 0;
	int targetType = -1;

	if(nextCharType == 0)
	{
		skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
	}
	else if(nextCharType == 1)
	{
		skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionEnemy];
	}
	
	targetType = findNextTarget(skillNum);

	//Reset all flags
	singularAllyFocus = singularEnemyFocus = multAllyFocus = multEnemyFocus = false;

	//Set flags based on who is attacking
	switch(targetType)
	{
		case 0:
			singularAllyFocus = true;
			break;
		case 1:
			singularEnemyFocus = true;
			break;
		case 2:
			multAllyFocus = true;
			break;
		case 3:
			multEnemyFocus = true;
			break;
		case 4:
			singularAllyFocus = true;

			if(nextCharType == 0)
			{
				currentAllySelected = nextCharCounter;
			}
			else if(nextCharType == 1)
			{
				currentEnemySelected = nextCharCounter;
			}
			break;
	}
	return targetType;
}

int Battle::findHpChangeSign(int hpFinal, int hpInit)
{
	std::cout << "findHpChangeSign\n";
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

//TODO Apply effect for both enemy AND allies
//TODO get mana change as well
bool Battle::allyTurnHandle(int& nextBattleState, sf::RenderWindow& win)
{
	std::cout << "allyTurnHandle\n";
	switch(currentOptionAlly)
	{
		case 0:
		case 1:
		case 2:
			allySkillCalc();
			return true;
		case 3:
			allyItem();
			return true;
			break;
		case 4:
			return allyChangePos(win);
			break;
		case 5:
			allyAttemptFlee(nextBattleState);
			return true;
			break;
	}
}

void Battle::allySkillCalc()
{
	std::cout << "allySkillCalc\n";

	if(processSkillTargetting() != -1)
	{
		switch(currentSkillCheck)
		{
			case 0:
			case 1:
				allySkillCalcHealth();
				break;
			case 2:
			case 3:
				allySkillCalcStat();
				break;
		}
	}
}

void Battle::allySkillCalcHealth()
{
	std::cout << "allySkillCalcHealth\n";
	int skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
	if(singularAllyFocus)
	{
		int allyStrength = ally[nextCharCounter]->getStrength();
		int targetHp = ally[currentAllySelected]->getCurrentHp();

		int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
		ally[currentAllySelected]->setHpFinal(targetHpFinal);

		battleOverlay.healedLog(ally[nextCharCounter]->getName(), ally[currentAllySelected]->getName(), targetHpFinal - targetHp);
	}
	else if(singularEnemyFocus)
	{
		int allyStrength = ally[nextCharCounter]->getStrength();
		int targetHp = enemy[currentEnemySelected]->getCurrentHp();
		int targetDef = enemy[currentEnemySelected]->getDefense();

		int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
		enemy[currentEnemySelected]->setHpFinal(targetHpFinal);

		battleOverlay.attackedLog(ally[nextCharCounter]->getName(), enemy[currentEnemySelected]->getName(), targetHp - targetHpFinal);
	}
	else if(multAllyFocus)
	{
		battleOverlay.healedLog(ally[nextCharCounter]->getName(), "all allies");

		for(int i = 0; i < ally.size(); i++)
		{
			if(ally[i]->getAlive())
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetHp = ally[i]->getCurrentHp();

				int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
				ally[i]->setHpFinal(targetHpFinal);
			}
		}
	}
	else if(multEnemyFocus)
	{
		battleOverlay.attackedLog(ally[nextCharCounter]->getName(), "all enemies");

		for(int i = 0; i < enemy.size(); i++)
		{
			if(enemy[i]->getAlive())
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetHp = enemy[i]->getCurrentHp();
				int targetDef = enemy[i]->getDefense();

				int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
				enemy[i]->setHpFinal(targetHpFinal);
			}
		}
	}
}

void Battle::allySkillCalcStat()
{
	std::cout << "allySkillCalcStat\n";
	//If buff or debuff type is str, set to str, etc.
	int skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
	int statType;
	if(currentSkillCheck == 2)
	{
		statType = skillList[skillNum]->getDebuffType();
	}
	else if(currentSkillCheck == 3)
	{
		statType = skillList[skillNum]->getBuffType();
	}

	if(singularAllyFocus)
	{
		if(statType == 0)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = ally[currentAllySelected]->getStrength();
			int targetDef = ally[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentAllySelected]->setStrength(targetStatFinal);

			battleOverlay.buffedLog(ally[nextCharCounter]->getName(), ally[currentAllySelected]->getName(), "strength", targetStatFinal - targetStat);
		}
		else if(statType == 1)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = ally[currentAllySelected]->getDefense();
			int targetDef = ally[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentAllySelected]->setDefense(targetStatFinal);

			battleOverlay.buffedLog(ally[nextCharCounter]->getName(), ally[currentAllySelected]->getName(), "defense", targetStatFinal - targetStat);
		}
		else if(statType == 2)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = ally[currentAllySelected]->getAgility();
			int targetDef = ally[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentAllySelected]->setAgility(targetStatFinal);

			battleOverlay.buffedLog(ally[nextCharCounter]->getName(), ally[currentAllySelected]->getName(), "agility", targetStatFinal - targetStat);
		}
	}
	else if(singularEnemyFocus)
	{
		if(statType == 0)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = enemy[currentEnemySelected]->getStrength();
			int targetDef = enemy[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentEnemySelected]->setStrength(targetStatFinal);

			battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), enemy[currentEnemySelected]->getName(), "strength", targetStat - targetStatFinal);
		}
		else if(statType == 1)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = enemy[currentEnemySelected]->getDefense();
			int targetDef = enemy[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentEnemySelected]->setDefense(targetStatFinal);

			battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), enemy[currentEnemySelected]->getName(), "defense", targetStat - targetStatFinal);
		}
		else if(statType == 2)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetStat = enemy[currentEnemySelected]->getAgility();
			int targetDef = enemy[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentEnemySelected]->setAgility(targetStatFinal);

			battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), enemy[currentEnemySelected]->getName(), "agility", targetStat - targetStatFinal);
		}
	}
	else if(multAllyFocus)
	{
		for(int i = 0; i < ally.size(); i++)
		{
			if(ally[i]->getAlive())
			{
				if(statType == 0)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getStrength();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setStrength(targetStatFinal);

					battleOverlay.buffedLog(ally[nextCharCounter]->getName(), "all allies", "strength");
				}
				else if(statType == 1)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getDefense();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setDefense(targetStatFinal);

					battleOverlay.buffedLog(ally[nextCharCounter]->getName(), "all allies", "defense");
				}
				else if(statType == 2)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getAgility();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setAgility(targetStatFinal);

					battleOverlay.buffedLog(ally[nextCharCounter]->getName(), "all allies", "agility");
				}
			}
		}
	}
	else if(multEnemyFocus)
	{
		for(int i = 0; i < enemy.size(); i++)
		{
			if(enemy[i]->getAlive())
			{
				if(statType == 0)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getStrength();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setStrength(targetStatFinal);

					battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), "all enemies", "strength");
				}
				else if(statType == 1)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getDefense();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setDefense(targetStatFinal);

					battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), "all enemies", "defense");
				}
				else if(statType == 2)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getAgility();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setAgility(targetStatFinal);

					battleOverlay.debuffedLog(ally[nextCharCounter]->getName(), "all enemies", "agility");
				}
			}
		}
	}
}

void Battle::allyItem()
{
	std::cout << "allyItem\n";
	//TODO Access item vector to find effect
}

bool Battle::allyChangePos(sf::RenderWindow& win)
{
	std::cout << "allyChangePos\n";
	//TODO make the grid blink to display where to move to
	//Use buttons with alpha
	if(oldBattlePos == -1)
	{
		for(int i = 0; i < chooseAlly.size(); i++)
		{
			if(chooseAlly[i]->mouseClickedInButton(allyOptionSelect, allyOptionDeselect, win))
			{
				resetGrid();
				oldBattlePos = ally[nextCharCounter]->getBattlePos();
				ally[nextCharCounter]->setBattlePos(i);
				return false;
			}

		}
	}
	else
	{
		if(changePosAnimation())
		{
			return true;
		}
	}
	return false;
}

bool Battle::changePosAnimation()
{
	int newBattlePos = ally[nextCharCounter]->getBattlePos();

	int xMove = (allyPos[newBattlePos].x - allyPos[oldBattlePos].x) / 20;
	int yMove = (allyPos[newBattlePos].y - allyPos[oldBattlePos].y) / 20;

	sf::Vector2f curPos = ally[nextCharCounter]->getPosition();

	bool withinX = allyPos[newBattlePos].x + abs(xMove) >= curPos.x && 
			allyPos[newBattlePos].x - abs(xMove) <= curPos.x;
	bool withinY = allyPos[newBattlePos].y + abs(yMove) >= curPos.y && 
			allyPos[newBattlePos].y - abs(yMove) <= curPos.y;

	if(withinX && withinY)
	{
		oldBattlePos = -1;
		ally[nextCharCounter]->setPosition(allyPos[newBattlePos].x, allyPos[newBattlePos].y);
		return true;
	}
	else
	{
		ally[nextCharCounter]->setPosition(curPos.x + xMove, curPos.y + yMove);
	}
	return false;

}

//Calculate using the level difference between average of allies and the enemy
void Battle::allyAttemptFlee(int& nextBattleState)
{
	std::cout << "allyAttemptFlee\n";
	int avgAlly = 0;
	int avgEnemy = 0;
	for(int i = 0; i < ally.size(); i++)
	{
		avgAlly += ally[i]->getLevel();
	}
	avgAlly /= (ally.size() + 1);

	for(int i = 0; i < enemy.size(); i++)
	{
		avgEnemy += enemy[i]->getLevel();
	}
	avgEnemy  /= (enemy.size() + 1);

	int randChance = rand() % 15 + 85;
	if(avgAlly * randChance > avgEnemy)
	{
		//TODO end the game properly
		nextBattleState = 10;
	}
}

void Battle::enemyTurnHandle(int& nextBattleState)
{
	std::cout << "enemyTurnHandle\n";
	enemySkillCalc();
}

void Battle::enemySkillCalc()
{
	std::cout << "enemySkillCalc\n";

	if(processSkillTargetting() != -1)
	{
		switch(currentSkillCheck)
		{
			case 0:
			case 1:
				enemySkillCalcHealth();
				break;
			case 2:
			case 3:
				enemySkillCalcStat();
				break;
		}
	}
}

void Battle::enemySkillCalcHealth()
{
	std::cout << "enemySkillCalc\n";

	int skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionEnemy];
	if(singularAllyFocus)
	{
		int allyStrength = enemy[nextCharCounter]->getStrength();
		int targetHp = enemy[currentAllySelected]->getCurrentHp();

		int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
		enemy[currentAllySelected]->setHpFinal(targetHpFinal);

		battleOverlay.healedLog(enemy[nextCharCounter]->getName(), enemy[currentAllySelected]->getName(), targetHpFinal - targetHp);
	}
	else if(singularEnemyFocus)
	{
		int allyStrength = enemy[nextCharCounter]->getStrength();
		int targetHp = ally[currentEnemySelected]->getCurrentHp();
		int targetDef = ally[currentEnemySelected]->getDefense();

		int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
		ally[currentEnemySelected]->setHpFinal(targetHpFinal);

		battleOverlay.attackedLog(enemy[nextCharCounter]->getName(), ally[currentEnemySelected]->getName(), targetHp - targetHpFinal);
	}
	else if(multAllyFocus)
	{
		battleOverlay.healedLog(enemy[nextCharCounter]->getName(), "all enemies");

		for(int i = 0; i < enemy.size(); i++)
		{
			if(enemy[i]->getAlive())
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetHp = enemy[i]->getCurrentHp();

				int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
				enemy[i]->setHpFinal(targetHpFinal);
			}
		}
	}
	else if(multEnemyFocus)
	{
		battleOverlay.attackedLog(enemy[nextCharCounter]->getName(), "all allies");

		for(int i = 0; i < ally.size(); i++)
		{
			if(ally[i]->getAlive())
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetHp = ally[i]->getCurrentHp();
				int targetDef = ally[i]->getDefense();

				int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
				ally[i]->setHpFinal(targetHpFinal);
			}
		}
	}
}

void Battle::enemySkillCalcStat()
{
	std::cout << "enemySkillCalcStat\n";
	//If buff or debuff type is str, set to str, etc.
	int skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionEnemy];
	int statType;
	if(currentSkillCheck == 2)
	{
		statType = skillList[skillNum]->getDebuffType();
	}
	else if(currentSkillCheck == 3)
	{
		statType = skillList[skillNum]->getBuffType();
	}

	if(singularAllyFocus)
	{
		if(statType == 0)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = enemy[currentAllySelected]->getStrength();
			int targetDef = enemy[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentAllySelected]->setStrength(targetStatFinal);

			battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), enemy[currentAllySelected]->getName(), "strength", targetStatFinal - targetStat);
		}
		else if(statType == 1)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = enemy[currentAllySelected]->getDefense();
			int targetDef = enemy[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentAllySelected]->setDefense(targetStatFinal);

			battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), enemy[currentAllySelected]->getName(), "defense", targetStatFinal - targetStat);
		}
		else if(statType == 2)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = enemy[currentAllySelected]->getAgility();
			int targetDef = enemy[currentAllySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			enemy[currentAllySelected]->setAgility(targetStatFinal);

			battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), enemy[currentAllySelected]->getName(), "agility", targetStatFinal - targetStat);
		}
	}
	else if(singularEnemyFocus)
	{
		if(statType == 0)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = ally[currentEnemySelected]->getStrength();
			int targetDef = ally[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentEnemySelected]->setStrength(targetStatFinal);

			battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), ally[currentEnemySelected]->getName(), "strength", targetStat - targetStatFinal);
		}
		else if(statType == 1)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = ally[currentEnemySelected]->getDefense();
			int targetDef = ally[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentEnemySelected]->setDefense(targetStatFinal);

			battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), ally[currentEnemySelected]->getName(), "defense", targetStat - targetStatFinal);
		}
		else if(statType == 2)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetStat = ally[currentEnemySelected]->getAgility();
			int targetDef = ally[currentEnemySelected]->getDefense();
			int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
			ally[currentEnemySelected]->setAgility(targetStatFinal);

			battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), ally[currentEnemySelected]->getName(), "agility", targetStat - targetStatFinal);
		}
	}
	else if(multAllyFocus)
	{
		for(int i = 0; i < enemy.size(); i++)
		{
			if(enemy[i]->getAlive())
			{
				if(statType == 0)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getStrength();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setStrength(targetStatFinal);

					battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), "all enemies", "strength");
				}
				else if(statType == 1)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getDefense();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setDefense(targetStatFinal);

					battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), "all enemies", "defense");
				}
				else if(statType == 2)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = enemy[i]->getAgility();
					int targetDef = enemy[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					enemy[i]->setAgility(targetStatFinal);

					battleOverlay.buffedLog(enemy[nextCharCounter]->getName(), "all enemies", "agility");
				}
			}
		}
	}
	else if(multEnemyFocus)
	{
		for(int i = 0; i < ally.size(); i++)
		{
			if(ally[i]->getAlive())
			{
				if(statType == 0)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getStrength();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setStrength(targetStatFinal);

					battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), "all allies", "strength");
				}
				else if(statType == 1)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getDefense();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setDefense(targetStatFinal);

					battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), "all allies", "defense");
				}
				else if(statType == 2)
				{
					int allyStrength = ally[nextCharCounter]->getStrength();
					int targetStat = ally[i]->getAgility();
					int targetDef = ally[i]->getDefense();
					int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
					ally[i]->setAgility(targetStatFinal);

					battleOverlay.debuffedLog(enemy[nextCharCounter]->getName(), "all allies", "agility");
				}
			}
		}
	}
}

//*************** BATTLE STATE 7 *********************
void Battle::hpAnimate(int& nextBattleState)
{
	allyHpChange();
	enemyHpChange();
	checkForCompletion(nextBattleState);
}

void Battle::allyHpChange()
{
	std::cout << "allyHpChange\n";
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			int hpFinal = ally[i]->getHpFinal();
			//Replace hpFinal with hpFinal of specific character
			int sign = findHpChangeSign(hpFinal, ally[i]->getCurrentHp());
			if(ally[i]->getCurrentHp() > hpFinal + 2 || ally[i]->getCurrentHp() < hpFinal - 2)
			{
				ally[i]->setCurrentHp(ally[i]->getCurrentHp() + (2 * sign));
			}
			else if (ally[i]->getCurrentHp() != hpFinal)
			{
				ally[i]->setCurrentHp(hpFinal);
			}
		}
	}
}

void Battle::enemyHpChange()
{
	std::cout << "enemyHpChange\n";
	for(int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getAlive())
		{
			int hpFinal = enemy[i]->getHpFinal();
			int currentEnemyHp = enemy[i]->getCurrentHp();

			if(hpFinal != currentEnemyHp)
			{
				int sign = findHpChangeSign(hpFinal, currentEnemyHp);
				if(currentEnemyHp > hpFinal + 2 || currentEnemyHp < hpFinal - 2)
				{
					enemy[i]->setCurrentHp(currentEnemyHp + (2 * sign));
				}
				else if (currentEnemyHp != hpFinal)
				{
					enemy[i]->setCurrentHp(hpFinal);
				}
			}
		}
	}
}

void Battle::allySkillAnimate()
{
}

void Battle::enemySkillAnimate()
{
}

void Battle::checkForCompletion(int& nextBattleState)
{
	std::cout << "checkForCompletion\n";
	bool allDone = true;

	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			int currentHp = ally[i]->getCurrentHp();
			int targetHp = ally[i]->getHpFinal();
			if(currentHp != targetHp)
			{
				allDone = false;
			}
		}
	}

	for(int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getAlive())
		{
			int currentHp = enemy[i]->getCurrentHp();
			int targetHp = enemy[i]->getHpFinal();
			if(currentHp != targetHp)
			{
				allDone = false;
			}
		}
	}

	if(allDone)
	{
		nextBattleState = 8;
	}
}

//*************** BATTLE STATE 8 *********************
void Battle::moveBackwardAnimation(int& nextBattleState)
{
	std::cout << "moveBackwardAnimation\n" << nextCharCounter;
	switch(nextCharType)
	{
		case 0:
			allyPostAttackAnimation(nextBattleState);
			break;
		case 1:
			enemyPostAttackAnimation(nextBattleState);
			break;
	}
}

void Battle::allyPostAttackAnimation(int& nextBattleState)
{
	std::cout << "allyPostAttackAnimation\n";
	goalPlace = allyPos[ally[nextCharCounter]->getBattlePos()].x;
	if(ally[nextCharCounter]->getPosition().x < goalPlace)
	{
		ally[nextCharCounter]->setPosition(ally[nextCharCounter]->getPosition().x + 10, ally[nextCharCounter]->getPosition().y);
	}
	else
	{
		nextBattleState = 9;
	}
}

void Battle::enemyPostAttackAnimation(int& nextBattleState)
{
	std::cout << "enemyPostAttackAnimation\n";
	sf::Vector2f current = enemy[nextCharCounter]->getPosition();
	
	//Sets the area to stop
	goalPlace = enemyPos[enemy[nextCharCounter]->getBattlePos()].x;
	
	//Moves the enemy, otherwise increments battle state
	if(current.x > goalPlace)
	{
		enemy[nextCharCounter]->setPosition(current.x - 10, current.y);
	}
	else
	{
		nextBattleState = 9;
	}
}

//*************** BATTLE STATE 8 *********************
//Sets ally to dead if less than 0 hp. Returns true if all allies are dead
bool Battle::checkAllyDeath()
{
	std::cout << "checkAllyDeath\n";
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

//Returns true if all enemy are dead
bool Battle::checkEnemyDeaths()
{
	std::cout << "checkEnemyDeaths\n";
	bool allDead = true;

	for(int i = 0 ; i < enemy.size(); i++)
	{
		if(enemy[i]->getCurrentHp() > 1)
		{
			allDead = false;
		}
		else 
		{
			//enemy has died
			enemy[i]->setAlive(false);
		}
	}
	return allDead;
}

void Battle::checkEndBattle(int& nextBattleState, int& currentState, std::vector<int> allyInParty, std::vector<std::shared_ptr<Character>> allyOrig)
{
	std::cout << "checkEndBattle\n";
	//TODO Loses the battle
	if(checkAllyDeath())
	{
		currentState = 0;
	}
	//TODO Wins the battle
	else if(checkEnemyDeaths())
	{
		//Transfer effects on ally over to the actual ally in map storage
		for(int i = 0; i < allyInParty.size(); i++)
		{
			allyOrig[allyInParty[i]]->setCurrentHp(ally[i]->getCurrentHp());
			allyOrig[allyInParty[i]]->setCurrentMana(ally[i]->getCurrentMana());
			allyOrig[allyInParty[i]]->setAlive(ally[i]->getAlive());
		}

		currentState = 1;
	}
	else
	{
		newTurn();
		nextBattleState = 0;
	}
}

//Sets up for new turn by resetting all canAtk flags for those who are still alive
//Also resets flag for finishing enemy focus
void Battle::newTurn()
{
	std::cout << "newTurn\n";
	singularAllyFocus = singularEnemyFocus = false;
}

//************ DRAWING ***************

void Battle::drawAll(sf::RenderWindow& win, int nextBattleState)
{
	std::cout << "drawAll\n";

	for(int i = 0; i < chooseAlly.size(); i++)
	{
		chooseAlly[i]->drawAll(win);
		chooseEnemy[i]->drawAll(win);
	}

	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			ally[i]->drawSprite(win);

			ally[i]->statBarUpdate();
			ally[i]->drawBars(win);
		}
	}

	for(int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getAlive())
		{
			enemy[i]->drawSprite(win);

			enemy[i]->statBarUpdate();
			enemy[i]->drawBars(win);
		}
	}

	battleOverlay.drawAll(win);

	if(nextBattleState == 2)
	{
		for(int i = 0; i < allyOptions.size(); i++)
		{
			allyOptions[i]->drawAll(win);
		}
	}
}

//*************** UTILITY *******************
int Battle::getMaxNum(int numOne, int numTwo)
{
	std::cout << "getMaxNum\n";
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

void Battle::showCharacterInfo(sf::RenderWindow& win)
{
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < ally.size(); j++)
		{
			bool allyCond = ally[j]->getAlive() && ally[j]->getBattlePos() == i;
			if(chooseAlly[i]->mouseInButton(win) && allyCond)
			{
				battleOverlay.showCurrentCharDesc(*ally[j]);
				return;
			}
		}
		for(int j = 0; j < enemy.size(); j++)
		{
			bool enemCond = enemy[j]->getAlive() && enemy[j]->getBattlePos() == i;
			if(chooseEnemy[i]->mouseInButton(win) && enemCond)
			{
				battleOverlay.showCurrentCharDesc(*enemy[j]);
				return;
			}
		}
	}

	battleOverlay.showCurrentCharDesc();
}

void Battle::delayState(int& currentBattleState, int nextBattleState)
{
	int milliDelay = 0;

	switch(nextBattleState)
	{
		case 0:
			milliDelay = 100;
			break;
		case 2:
			milliDelay = 50;
			break;
		case 3:
			milliDelay = 50;
			break;
		case 6:
			milliDelay = 100;
			break;
		case 8:
			milliDelay = 100;
			break;
	}
	tme = clk.getElapsedTime();

	if(!lastTimeSet)
	{
		lastTimeSet = true;
		lastTime = tme.asMilliseconds();
	}

	currentTime = tme.asMilliseconds();

	if(lastTime + milliDelay < currentTime)
	{
		currentBattleState = nextBattleState;
		lastTimeSet = false;
	}
}
