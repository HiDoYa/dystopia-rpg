#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Skill.h"

Skill::Skill()
{
	//Default
	manaCost = 0;
	numAtksPerHit = 1;
	missed = false;
	debuffType = -1;

	for(int i = 0; i < 4; i++)
	{
		reapplyTurn.push_back(0);
		oldVal.push_back(0);
		mult.push_back(0);
		max.push_back(0);
		min.push_back(0);
		percent.push_back(false);
		target.push_back(-1);
	}

	crit = 0;
	accuracy = 0;

	chance = 5;

	//Seeding
	srand(time(NULL));
}

//****** MUTATORS *********
void Skill::setName(std::string str)
{
	name = str;
}

void Skill::setChance(int inp)
{
	chance = inp;
}

void Skill::setManaCost(int inp)
{
	manaCost = inp;
}

void Skill::setNumAtksPerHit(int inp)
{
	numAtksPerHit = inp;
}

void Skill::setReapplyTurn(int type, int inp)
{
	reapplyTurn[type] = inp;
}

void Skill::setOldVal(int type, int inp)
{
	oldVal[type] = inp;
}

void Skill::setMult(int type, float inp)
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

void Skill::setDebuffType(int inp)
{
	debuffType = inp;
}

void Skill::setPercent(int type, bool inp)
{
	percent[type] = inp;
}

void Skill::setCrit(int inp)
{
	crit = inp;
}

void Skill::setAccuracy(int inp)
{
	accuracy = inp;
}

void Skill::setTarget(int type, int inp)
{
	target[type] = inp;
}

//********** ACCESSOR *********
std::string Skill::getName()
{
	return name;
}

int Skill::getChance()
{
	return chance;
}

int Skill::getManaCost()
{
	return manaCost;
}

int Skill::getNumAtksPerHit()
{
	return numAtksPerHit;
}

std::vector<int> Skill::getReapplyTurn()
{
	return reapplyTurn;
}

std::vector<int> Skill::getOldVal()
{
	return oldVal;
}

std::vector<float> Skill::getMult()
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

int Skill::getDebuffType()
{
	return debuffType;
}

std::vector<bool> Skill::getPercent()
{
	return percent;
}

int Skill::getCrit()
{
	return crit;
}

int Skill::getAccuracy()
{
	return accuracy;
}

std::vector<int> Skill::getTarget()
{
	return target;
}

// ********* UTILITY *************
int Skill::checkForSelection()
{
	for(int i = 0; i < 4; i++)
	{
		//If this skill is active, return who the skill targets
		if(mult[i] > 0)
		{
			return target[i];
		}
	}
	return -1;
}

// ********* DAMAGE UTILITY *************

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

//******** DAMAGE CALCULATION *************
int Skill::healthChangeHandle(int posMult, int negMult, int percentMax, int type)
{
	int healthCh;

	//Decide whether to use percent or normal calculation
	if(percent[type] > 0)
	{
		healthCh = percentCalc(posMult, negMult, percentMax, type);
	}
	else
	{
		healthCh = normCalc(posMult, negMult, type);
	}

	//If type 0, the health change is negative
	if(type == 0)
	{
		healthCh *= -1;
	}

	return healthCh;
}

int Skill::normCalc(int posMult, int negMult, int type)
{
	int val = 0;
	val = (posMult - negMult) * mult[type];

	//TODO Type
	checkForMaxMin(val, type);

	if((rand() % 100 + 1) < crit)
	{
		val *= 1.5;
	}

	return val;
}

//Percent max is usually health
int Skill::percentCalc(int posMult, int negMult, int percentMax, int type)
{	
	int val = 0;
	val = (posMult - negMult) / 100.0 * percentMax;

	checkForMaxMin(val, type);
	checkForMiss();
	return val;
}

int Skill::statChangeHandle(int posMult, int negMult, int percentMax)
{
	int statCh = 0;
	for(int type = 2; type < 4; type++)
	{
		if(percent[type])
		{
			//percent
		}
		else
		{
			//norm
		}

		if(type == 2)
		{
		}
	}
}

//******** TEXT *************
std::string Skill::dispText(std::string chrName, std::string target, int tempDmg)
{
	std::string returnText = "";

	if(missed)
	{
		returnText = chrName + " missed the attack";
	}
	//TODO
	else if(true)
	{
		returnText = chrName + " hit " + target + " for " + std::to_string(tempDmg);
	}

	returnText += '!';
	return returnText;
}
