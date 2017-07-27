#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Skill.h"

Skill::Skill()
{
	//Default
	powerRating = 1;
	manaCost = 0;
	numAtksPerHit = 1;
	missed = false;
	buffType = -1;
	debuffType = -1;
	primaryType = -1;

	for(int i = 0; i < 4; i++)
	{
		reapplyTurn.push_back(0);
		oldVal.push_back(0);
		mult.push_back(0);
		max.push_back(999999);
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

void Skill::setDescription(std::string str)
{
	description = str;
}

void Skill::setPowerRating(int inp)
{
	powerRating = inp;
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

void Skill::setBuffType(int inp)
{
	buffType = inp;
}

void Skill::setDebuffType(int inp)
{
	debuffType = inp;
}

void Skill::setPrimaryType(int inp)
{
	primaryType = inp;
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

void Skill::setAllyEquip(std::vector<int> inp)
{
	allyEquip = inp;
}

//********** ACCESSOR *********
std::string Skill::getName()
{
	return name;
}

std::string Skill::getDescription()
{
	return description;
}

int Skill::getPowerRating()
{
	return powerRating;
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

int Skill::getBuffType()
{
	return buffType;
}

int Skill::getDebuffType()
{
	return debuffType;
}

int Skill::getPrimaryType()
{
	return primaryType;
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

std::vector<int> Skill::getAllyEquip()
{
	return allyEquip;
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

	//If persistent, store in oldVal
	if(reapplyTurn[type] > 0)
	{
		oldVal[type] = healthCh;
	}

	return healthCh + percentMax;
}

int Skill::statChangeHandle(int posMult, int negMult, int percentMax, int type)
{
	int statCh = 0;

	if(percent[type] > 0)
	{
		//percent
		statCh = percentCalc(posMult, negMult, percentMax, type);
	}
	else
	{
		//norm
		statCh = normCalc(posMult, negMult, type);
	}

	//If type is 2, stat change is negative (debuff)
	if(type == 2)
	{
		statCh *= -1;
	}
	
	//If persistent, store in oldVal
	if(reapplyTurn[type] > 0)
	{
		oldVal[type] = -statCh;
	}

	return statCh + percentMax;
}

int Skill::normCalc(int posMult, int negMult, int type)
{
	int val = 0;
	//Generates random number between 0.95 - 1.05 and uses it to multiple att
	float randNum = (rand() % 10 + 95.0) / 100;
	int att = (posMult + mult[type]) * randNum;
	val = (att * att) / (negMult + att);

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
	float randNum = (rand() % 10 + 95.0) / 100;
	int att = (posMult + mult[type]) * randNum;
	val = (att * att) / (100 * percentMax + att);

	checkForMaxMin(val, type);
	checkForMiss();
	return val;
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
