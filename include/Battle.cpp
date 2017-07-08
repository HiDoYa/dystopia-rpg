#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Battle.h"

Battle::Battle()
{
	//Default initializations
	currentPlayerForOption = 0;
	currentOptionAlly = 0;
	currentOptionEnemy = 0;

	currentTime = lastTime = 0;
	newPos = 0;
	blinkTurn = true;
	goalPlace = 0;
	currentTarget = 0;
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	singularAllyFocus = false;
	singularEnemyFocus = false;
	
	//Displacement during character turn
	attackXDisp = 150;

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
		std::shared_ptr<sf::CircleShape> tempPtr (new sf::CircleShape);
		allyOptions.push_back(tempPtr);
		allyOptions[i]->setRadius(25);
		allyOptions[i]->setFillColor(sf::Color(150, 196, 255));
	}

	//Seeding
	srand(time(NULL));
}

void Battle::setupBattle(std::vector<std::shared_ptr<Character>> enemyList,
		std::vector<std::shared_ptr<Character>>& allyList,
		std::vector<Skill*> skillTemp, std::vector<int> allyInParty)
{
	std::cout << "setupBattle\n";

	//TODO Create function that updates the textures of circles (for skills) for when the ally moves to a different grid place
	
	//Initialize for clearing all previous battle data
	qNotPressed = wNotPressed = aNotPressed = sNotPressed = dNotPressed = false;
	enemy.clear();

	//Initialize for req default data
	currentOptionAlly = 0;

	//Store skill sets
	skillList = skillTemp;

	for(int i = 0; i < allyInParty.size(); i++)
	{
		ally.push_back(allyList[allyInParty[i]]);
	}

	//BATTLEPOS MUST BE SET DIFFERENTLY AT DEFAULT WHEN ALLIES ARE ADDED TO PARTY
	//Sets ally positions
	//TODO set battle position for allies in files
	for(int i = 0; i < ally.size(); i++)
	{
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
		enemy.push_back(enemyList[index]);

		//TODO random set position
		enemy[i]->setPosition(enemyPos[i].x, enemyPos[i].y);
		enemy[i]->updatePositionBattle();
	}
}

//*********** BATTLE STATE 0 *********************
//Finds fastest character and stores in nextCharType and nextCharCounter
void Battle::findFastestChar(int& currentBattleState)
{
	std::cout << "findFastestChar\n";
	int highestAgil = -1;
	nextCharType = -1;
	nextCharCounter = -1;

	//Reset the position of rectangle (for changing position)
	newPos = 0;

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

		//Current state is done
		currentBattleState = 1;
	}
	else if(nextCharType == 1)
	{
		enemy[nextCharCounter]->setCanAtk(false);

		//Current state is done
		currentBattleState = 1;
	}
}

//********** BATTLE STATE 1 ****************
void Battle::statusHandle(int& currentBattleState)
{
	std::cout << "statusHandle\n";
	checkForStatus();

	switch (nextCharType)
	{
		case 0:
			//Ally attack
			currentBattleState = 2;
			break;
		case 1:
			//Enemy attack
			currentBattleState = 4;
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
			Skill* currentPersistentSkill = skillList[ally[nextCharCounter]->getPersistentSkillNum()[i]];
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
			delete currentPersistentSkill;
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
			Skill* currentPersistentSkill = skillList[enemy[nextCharCounter]->getPersistentSkillNum()[i]];
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
			delete currentPersistentSkill;
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
void Battle::allySkillChoiceHandler(int& currentBattleState)
{
	std::cout << "allySkillChoiceHandler\n";
	changeCurrentSkill();
	if(chooseCurrentSkill())
	{
		currentBattleState = 3;
	}
}

void Battle::setCirclePos()
{
	std::cout << "setCirclePos\n";
	for(int i = 0; i < allyOptions.size(); i++)
	{
		allyOptions[i]->setPosition(optionsPos[i] + allyPos[nextCharCounter]);
	}
}

void Battle::changeCurrentSkill()
{
	std::cout << "changeCurrentSkill\n";
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

bool Battle::chooseCurrentSkill()
{
	std::cout << "chooseCurrentSkill\n";
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(!spacePressed)
	{
		spaceNotPressed = true;
	}


	//Go to next battle state with currentOptionAlly storing the skill to use
	if(spacePressed && spaceNotPressed)
	{
		spaceNotPressed = false;
		return true;
	}
	return false;
}

//*********** BATTLE STATE 3 *********************
void Battle::allyChooseFocus(int& currentBattleState)
{
	std::cout << "chooseEnemyFocus\n";

	//Look for singular focus if both bools are false
	if(!singularAllyFocus && !singularEnemyFocus)
	{
		findSingularFocus();
	}
	//Only choose who to focus if bools are true. Otherwise, just skip to battle state 5
	if(singularAllyFocus)
	{
		changeAllyFocus();
	}
	else if(singularEnemyFocus)
	{
		changeEnemyFocus();
	}
	else
	{
		currentBattleState = 5;
	}

	//If singular focus and space is pressed, go to state 5
	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(!spacePressed)
	{
		spaceNotPressed = true;
	}

	if(spacePressed && spaceNotPressed)
	{
		spaceNotPressed = false;
		currentBattleState = 5;
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
	std::cout << "SingularAllyFocus: " << singularAllyFocus << "  SingularEnemyFocus: " << singularEnemyFocus << '\n';
}

void Battle::changeAllyFocus()
{
	std::cout << "changeAllyFocus\n";
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
		}while(!(enemy[currentTarget]->getAlive()));
	}
}

void Battle::changeEnemyFocus()
{
	std::cout << "changeEnemyFocus\n";
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	
	if(!qPressed)
	{
		qNotPressed = true;
	}

	//Initialize current target
	do
	{
		currentTarget++;
		if(currentTarget >= enemy.size())
		{
			currentTarget = 0;
		}
	}while(!(enemy[currentTarget]->getAlive()));

	//If q pressed, swap to next enemy that is not dead
	if(qPressed && qNotPressed)
	{
		qNotPressed = false;
		do
		{
			currentTarget++;
			if(currentTarget >= enemy.size())
			{
				currentTarget = 0;
			}
		}while(!(enemy[currentTarget]->getAlive()));
	}
}

//*********** BATTLE STATE 4 *********************
void Battle::enemyDecision(int& currentBattleState)
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
	currentBattleState = 5;
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
	if(allyInFront.size() > 0)
	{
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
	else
	{
		currentEnemySelected = allyInBack[rand() % allyInBack.size()];
	}
}

//*********** BATTLE STATE 5 *********************
void Battle::moveForwardAnimation(int& currentBattleState)
{
	std::cout << "moveForwardAnimation\n";
	switch (nextCharType)
	{
		case 0:
			allyAttackAnimation(currentBattleState);
			break;
		case 1:
			enemyAttackAnimation(currentBattleState);
			break;
	}
}
void Battle::allyAttackAnimation(int& currentBattleState)
{
	std::cout << "allyAttackAnimation\n";
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
		currentBattleState = 6;
	}
}

//Enemy simply moves forward
void Battle::enemyAttackAnimation(int& currentBattleState)
{
	std::cout << "enemyAttackAnimation\n";
	sf::Vector2f current = enemy[nextCharCounter]->getPosition();
	
	//Sets the area to stop
	goalPlace = enemyPos[nextCharCounter].x + attackXDisp;

	//Moves the enemy, otherwise increments battle state
	if(current.x < goalPlace)
	{
		enemy[nextCharCounter]->setPosition(current.x + 10, current.y);
	}
	else
	{ 
		currentBattleState = 6;
	}
}

//******** BATTLE STATE 6 **************
//Calculates hp/mana change for enemy and ally
void Battle::handleEffect(int& currentBattleState)
{
	std::cout << "handleEffect\n";

	switch(nextCharType)
	{
		case 0:
			allyTurnHandle(currentBattleState);
			break;
		case 1:
			enemyTurnHandle(currentBattleState);
			break;
	}
	currentBattleState = 7;
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
		skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionAlly];
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
void Battle::allyTurnHandle(int& currentBattleState)
{
	std::cout << "allyTurnHandle\n";
	switch(currentOptionAlly)
	{
		case 0:
		case 1:
		case 2:
			allySkillCalc();
			break;
		case 3:
			allyItem();
			break;
		case 4:
			allyChangePos();
			break;
		case 5:
			allyAttemptFlee(currentBattleState);
			break;
	}
}

void Battle::allySkillCalc()
{
	std::cout << "allySkillCalc\n";

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

void Battle::allySkillCalcHealth()
{
	std::cout << "allySkillCalcHealth\n";
	if(processSkillTargetting() != -1)
	{
		int skillNum = ally[nextCharCounter]->getSkillNum()[currentOptionAlly];
		if(singularAllyFocus)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetHp = ally[currentAllySelected]->getCurrentHp();

			int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
			ally[currentAllySelected]->setHpFinal(targetHpFinal);
		}
		else if(singularEnemyFocus)
		{
			int allyStrength = ally[nextCharCounter]->getStrength();
			int targetHp = enemy[currentEnemySelected]->getCurrentHp();
			int targetDef = enemy[currentEnemySelected]->getDefense();

			int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
			enemy[currentEnemySelected]->setHpFinal(targetHpFinal);
		}
		else if(multAllyFocus)
		{
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
}

void Battle::allySkillCalcStat()
{
	std::cout << "allySkillCalcStat\n";
	if(processSkillTargetting() != -1)
	{
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
			}
			else if(statType == 1)
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetStat = ally[currentAllySelected]->getDefense();
				int targetDef = ally[currentAllySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				ally[currentAllySelected]->setDefense(targetStatFinal);
			}
			else if(statType == 2)
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetStat = ally[currentAllySelected]->getAgility();
				int targetDef = ally[currentAllySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				ally[currentAllySelected]->setAgility(targetStatFinal);
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
			}
			else if(statType == 1)
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetStat = enemy[currentEnemySelected]->getDefense();
				int targetDef = enemy[currentEnemySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				enemy[currentEnemySelected]->setDefense(targetStatFinal);
			}
			else if(statType == 2)
			{
				int allyStrength = ally[nextCharCounter]->getStrength();
				int targetStat = enemy[currentEnemySelected]->getAgility();
				int targetDef = enemy[currentEnemySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				enemy[currentEnemySelected]->setAgility(targetStatFinal);
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
					}
					else if(statType == 1)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = ally[i]->getDefense();
						int targetDef = ally[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						ally[i]->setDefense(targetStatFinal);
					}
					else if(statType == 2)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = ally[i]->getAgility();
						int targetDef = ally[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						ally[i]->setAgility(targetStatFinal);
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
					}
					else if(statType == 1)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = enemy[i]->getDefense();
						int targetDef = enemy[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						enemy[i]->setDefense(targetStatFinal);
					}
					else if(statType == 2)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = enemy[i]->getAgility();
						int targetDef = enemy[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						enemy[i]->setAgility(targetStatFinal);
					}
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

void Battle::allyChangePos()
{
	std::cout << "allyChangePos\n";
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

//Calculate using the level difference between average of allies and the enemy
void Battle::allyAttemptFlee(int& currentBattleState)
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
		currentBattleState = 10;
	}
}

void Battle::enemyTurnHandle(int& currentBattleState)
{
	std::cout << "enemyTurnHandle\n";
	enemySkillCalc();
}

void Battle::enemySkillCalc()
{
	std::cout << "enemySkillCalc\n";

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

void Battle::enemySkillCalcHealth()
{
	std::cout << "enemySkillCalc\n";

	if(processSkillTargetting() != -1)
	{
		int skillNum = enemy[nextCharCounter]->getSkillNum()[currentOptionEnemy];
		if(singularAllyFocus)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetHp = enemy[currentAllySelected]->getCurrentHp();

			int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, 0, targetHp, currentSkillCheck);
			enemy[currentAllySelected]->setHpFinal(targetHpFinal);
		}
		else if(singularEnemyFocus)
		{
			int allyStrength = enemy[nextCharCounter]->getStrength();
			int targetHp = ally[currentEnemySelected]->getCurrentHp();
			int targetDef = ally[currentEnemySelected]->getDefense();

			int targetHpFinal = skillList[skillNum]->healthChangeHandle(allyStrength, targetDef, targetHp, currentSkillCheck);
			ally[currentEnemySelected]->setHpFinal(targetHpFinal);
		}
		else if(multAllyFocus)
		{
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
}

void Battle::enemySkillCalcStat()
{
	std::cout << "enemySkillCalcStat\n";
	if(processSkillTargetting() != -1)
	{
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
			}
			else if(statType == 1)
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetStat = enemy[currentAllySelected]->getDefense();
				int targetDef = enemy[currentAllySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				enemy[currentAllySelected]->setDefense(targetStatFinal);
			}
			else if(statType == 2)
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetStat = enemy[currentAllySelected]->getAgility();
				int targetDef = enemy[currentAllySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				enemy[currentAllySelected]->setAgility(targetStatFinal);
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
			}
			else if(statType == 1)
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetStat = ally[currentEnemySelected]->getDefense();
				int targetDef = ally[currentEnemySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				ally[currentEnemySelected]->setDefense(targetStatFinal);
			}
			else if(statType == 2)
			{
				int allyStrength = enemy[nextCharCounter]->getStrength();
				int targetStat = ally[currentEnemySelected]->getAgility();
				int targetDef = ally[currentEnemySelected]->getDefense();
				int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
				ally[currentEnemySelected]->setAgility(targetStatFinal);
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
					}
					else if(statType == 1)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = enemy[i]->getDefense();
						int targetDef = enemy[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						enemy[i]->setDefense(targetStatFinal);
					}
					else if(statType == 2)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = enemy[i]->getAgility();
						int targetDef = enemy[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						enemy[i]->setAgility(targetStatFinal);
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
					}
					else if(statType == 1)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = ally[i]->getDefense();
						int targetDef = ally[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						ally[i]->setDefense(targetStatFinal);
					}
					else if(statType == 2)
					{
						int allyStrength = ally[nextCharCounter]->getStrength();
						int targetStat = ally[i]->getAgility();
						int targetDef = ally[i]->getDefense();
						int targetStatFinal = skillList[skillNum]->statChangeHandle(allyStrength, targetDef, targetStat, currentSkillCheck);
						ally[i]->setAgility(targetStatFinal);
					}
				}
			}
		}
	}
}

//*************** BATTLE STATE 7 *********************
void Battle::hpAnimate(int& currentBattleState)
{
	allyHpChange();
	enemyHpChange();
	checkForCompletion(currentBattleState);
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
			if(ally[i]->getCurrentHp() > hpFinal + 3 || ally[i]->getCurrentHp() < hpFinal - 3)
			{
				ally[i]->setCurrentHp(ally[i]->getCurrentHp() + (3 * sign));
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
				if(currentEnemyHp > hpFinal + 3 || currentEnemyHp < hpFinal - 3)
				{
					enemy[i]->setCurrentHp(currentEnemyHp + (3 * sign));
				}
				else if (currentEnemyHp != hpFinal)
				{
					enemy[i]->setCurrentHp(hpFinal);
				}
			}
		}
	}
}

void Battle::checkForCompletion(int& currentBattleState)
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
		currentBattleState = 8;
	}
}

//*************** BATTLE STATE 8 *********************
void Battle::moveBackwardAnimation(int& currentBattleState)
{
	std::cout << "moveBackwardAnimation\n" << nextCharCounter;
	switch(nextCharType)
	{
		case 0:
			allyPostAttackAnimation(currentBattleState);
			break;
		case 1:
			enemyPostAttackAnimation(currentBattleState);
			break;
	}
}

void Battle::allyPostAttackAnimation(int& currentBattleState)
{
	std::cout << "allyPostAttackAnimation\n";
	goalPlace = allyPos[ally[nextCharCounter]->getBattlePos()].x;
	if(ally[nextCharCounter]->getPosition().x < goalPlace)
	{
		ally[nextCharCounter]->setPosition(ally[nextCharCounter]->getPosition().x + 10, ally[nextCharCounter]->getPosition().y);
	}
	else
	{
		currentBattleState = 9;
	}
}

void Battle::enemyPostAttackAnimation(int& currentBattleState)
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
		currentBattleState = 9;
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

void Battle::checkEndBattle(int& currentBattleState, int& currentState, std::vector<int> allyInParty, std::vector<std::shared_ptr<Character>> allyOrig)
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
		currentEnemyDeath();
		currentBattleState = 0;
	}
}

//Change current enemy selected if the current enemy is dead (and battle is not over yet)
void Battle::currentEnemyDeath()
{
	std::cout << "currentEnemyDeath\n";
	if(!enemy[currentTarget]->getAlive())
	{
		do
		{
			currentTarget++;
			if(currentTarget >= enemy.size())
			{
				currentTarget = 0;
			}
		}while(!enemy[currentTarget]->getAlive());
	}
}

//Sets up for new turn by resetting all canAtk flags for those who are still alive
//Also resets flag for finishing enemy focus
void Battle::newTurn()
{
	std::cout << "newTurn\n";
}

//************ DRAWING ***************

void Battle::drawAll(sf::RenderWindow& win, int currentBattleState)
{
	std::cout << "drawAll\n";
	for(int i = 0; i < ally.size(); i++)
	{
		if(ally[i]->getAlive())
		{
			ally[i]->drawSpriteBattle(win);
		}
	}

	for(int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getAlive())
		{
			enemy[i]->drawSpriteBattle(win);
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
