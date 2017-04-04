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
		mult.push_back(0);
		max.push_back(0);
		min.push_back(0);
		crit.push_back(0);
		accuracy.push_back(0);
		pierce.push_back(0);
		element.push_back(0);
		target.push_back(0);
		targetNum.push_back(true);
	}
}

//****** MUTATORS *********
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

void Skill::setCrit(int type, int inp)
{
	crit[type] = inp;
}

void Skill::setAccuracy(int type, int inp)
{
	accuracy[type] = inp;
}

void Skill::setPierce(int type, int inp)
{
	pierce[type] = inp;
}

void Skill::setElement(int type, int inp)
{
	element[type] = inp;
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

std::vector<int> Skill::getCrit()
{
	return crit;
}

std::vector<int> Skill::getAccuracy()
{
	return accuracy;
}

std::vector<int> Skill::getPierce()
{
	return pierce;
}

std::vector<int> Skill::getElement()
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

//******** DAMAGE CALCULATION *************

int Skill:getDamageCalc(int allyStrength, int enemyDef, int enemyHealth)
{
}

int Skill::getNormDamageCalc(int allyStrength, int enemyDef)
{
}

int Skill::getPercentDamageCalc(int allyStrength, int enemyDef, int enemyHealth)
{
}

