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
	tempDmg = 0;

	//Initializes mult/max/min
	for(int i = 0; i < 2; i++)
	{
		target.push_back(0);
		targetNum.push_back(true);
	}

	mult = 0;
	max = 0;
	min = 0;
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
int Skill::getMult()
{
	return mult;
}

int Skill::getMax()
{
	return max;
}

int Skill::getMin()
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

int Skill::checkForMaxMin()
{
	if(tempDmg > max)
	{
		tempDmg = max;
	}
	if(tempDmg < min)
	{
		tempDmg = min;
	}

	return tempDmg;
}

int Skill::checkForCrit()
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

int Skill::getNormDamageCalc(int allyStrength, int enemyDef)
{
	tempDmg = (allyStrength - enemyDef) * mult;

	checkForMaxMin(tempDmg);

	if((rand() % 100 + 1) < crit)
	{
		tempDmg *= 1.5;
	}

	return tempDmg;
}

int Skill::getPercentDamageCalc(int allyStrength, int enemyDef, int enemyHealth)
{	
	tempDmg = (allyStrength - enemyDef) / 100 * enemyHealth;

	checkForMaxMin(tempDmg);
	checkForMiss();
	return tempDmg;
}

//******** DAMAGE CALCULATION *************
std::string Skill::dispText(std::string chrName)
{
	int returnText;
	if(missed)
	{
		returnText = chrName + " missed the attack!";
	}
	//TODO
	else if(true)
	{
		returnText = chrName + " hit the enemy for " + tempDmg + " damage!";
	}
}
