#include <SFML/Graphics.hpp>
#include <iostream>

#include "Skill.h"

Skill::Skill()
{
	//Default
	currentlyEquipped = false;
	manaCost = 0;
	numTurns = 1;
	reapplyTurn = false;

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
	pierce = 0;
	element = 0;
}

//****** MUTATORS *********
void Skill::setName(string str)
{
	text.setString(str);
}

void Skill::setMult(int inp)
{
	mult = inp;
}

void Skill::setMax(int inp)
{
	max = inp;
}

void Skill::setMin(int inp)
{
	min = inp;
}

void Skill::setCrit(int inp)
{
	crit = inp;
}

void Skill::setAccuracy(int inp)
{
	accuracy = inp;
}

void Skill::setPierce(int inp)
{
	pierce = inp;
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

int Skill::getPierce()
{
	return pierce;
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

int Skill::checkForMaxMin(int tempDmg)
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
}

int Skill::checkForMiss()
{
}

int Skill::addPierceDamage()
{
}

int Skill::addForElementDamage()
{
}

//******** DAMAGE CALCULATION *************

int Skill::getNormDamageCalc(int allyStrength, int enemyDef)
{
	int tempDmg = (allyStrength - enemyDef) * mult;

	checkForMaxMin(tempDmg);

	if((rand() % 100 + 1) < crit)
	{
		tempDmg *= 1.5;
	}

	return tempDmg;
}

int Skill::getPercentDamageCalc(int allyStrength, int enemyDef, int enemyHealth)
{	
	int tempDmg = (allyStrength - enemyDef) / 100 * enemyHealth;

	checkForMaxMin(tempDmg);

	if((rand() % 100 + 1) < crit)
	{
		tempDmg *= 1.5;
	}

	return 
}

