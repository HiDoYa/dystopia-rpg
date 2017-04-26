#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Skill.h"

Skill::Skill()
{
	//Default
	currentlyEquipped = false;
	manaCost = 0;
	numTurns = 1;
	reapplyTurn = false;
	numAtksPerHit = 1;
	missed = false;

	for(int i = 0; i < 4; i++)
	{
		max.push_back(0);
		max.push_back(0);
		min.push_back(0);
		target.push_back(0);
		targetNum.push_back(true);
	}

	crit = 0;
	accuracy = 0;
	element = 0;

	//Seeding
	srand(time(NULL));
}

//****** MUTATORS *********
void Skill::setName(std::string str)
{
	name = str;
}

void Skill::setMult(int type, int inp)
{
	mult[type] = inp;
}

void Skill::setMax(int type, int inp)
{
	max[type] = inp;
}

void Skill::setMin(int type, int inp)
{
	min[type] = inp;
}

void Skill::setCrit(int inp)
{
	crit = inp;
}

void Skill::setAccuracy(int inp)
{
	accuracy = inp;
}

void Skill::setElement(int inp)
{
	element = inp;
}

void Skill::setTarget(int type, int inp)
{
	target[type] = inp;
}

void Skill::setTargetNum(int type, bool inp)
{
	targetNum[type] = inp;
}

//********** ACCESSOR *********
std::vector<int> Skill::getMult()
{
	return mult;
}

std::vector<int> Skill::getMax()
{
	return max;
}

std::vector<int> Skill::getMin()
{
	return min;
}

int Skill::getCrit()
{
	return crit;
}

int Skill::getAccuracy()
{
	return accuracy;
}

int Skill::getElement()
{
	return element;
}

std::vector<int> Skill::getTarget()
{
	return target;
}

std::vector<bool> Skill::getTargetNum()
{
	return targetNum;
}

// ********* UTILITY *************

int Skill::checkForMaxMin(int tempDmg, int type)
{
	if(tempDmg > max[type])
	{
		tempDmg = max[type];
	}
	if(tempDmg < min[type])
	{
		tempDmg = min[type];
	}

	return tempDmg;
}

int Skill::checkForCrit(int tempDmg)
{
	if((rand() % 100 + 1) < crit)
	{
		tempDmg *= 1.5;
	}
	return tempDmg;
}

void Skill::checkForMiss()
{
	missed = false;
	if((rand() % 100 + 1) < (100 - accuracy))
	{
		missed = true;
	}
}

int Skill::addForElementDamage()
{
}

//******** DAMAGE CALCULATION *************

int Skill::getNormDamageCalc(int allyStrength, int enemyDef, int type)
{
	int tempDmg = 0;
	tempDmg = (allyStrength - enemyDef) * mult[type];

	//TODO Type
	checkForMaxMin(tempDmg, type);

	if((rand() % 100 + 1) < crit)
	{
		tempDmg *= 1.5;
	}

	return tempDmg;
}

int Skill::getPercentDamageCalc(int allyStrength, int enemyDef, int enemyHealth, int type)
{	
	int tempDmg = 0;
	tempDmg = (allyStrength - enemyDef) / 100 * enemyHealth;

	checkForMaxMin(tempDmg, type);
	checkForMiss();
	return tempDmg;
}

//******** TEXT *************
std::string Skill::dispText(std::string chrName, int tempDmg)
{
	std::string returnText = "";
	if(missed)
	{
		returnText = chrName + " missed the attack!";
	}
	//TODO
	else if(true)
	{
		returnText = chrName + " hit the enemy for " + std::to_string(tempDmg) + " damage!";
	}
	return returnText;
}
