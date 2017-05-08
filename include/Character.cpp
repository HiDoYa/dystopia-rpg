#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Character.h"

Character::Character()
{
	//Initialization default
	level = 1;
	maxHp = currentHp = 100;
	maxMana = currentMana = 100;

	strength = defense = agility = 10;

	alive = true;
	canAtk = true;
	finalHp = 100;
	battlePos = 0;

	allyInParty = false;
	currentExp = 0;
	requiredExp = 1;

	chance = 5;
}

//********* MUTATORS *************
void Character::setLevel(int inp)
{
	level = inp;
}

void Character::setCurrentHp(int inp)
{
	currentHp = inp;
}

void Character::setMaxHp(int inp)
{
	maxHp = inp;
}

void Character::setCurrentMana(int inp)
{
	currentMana = inp;
}

void Character::setMaxMana(int inp)
{
	maxMana = inp;
}

void Character::setStrength(int inp)
{
	strength = inp;
}

void Character::setCurrentStrength(int inp)
{
	currentStrength = inp;
}

void Character::setDefense(int inp)
{
	defense = inp;
}

void Character::setCurrentDefense(int inp)
{
	currentDefense = inp;
}

void Character::setAgility(int inp)
{
	agility = inp;
}

void Character::setCurrentAgility(int inp)
{
	currentAgility = inp;
}

void Character::setSkillNum(std::vector<int> inp)
{
	skillNum = inp;
}

void Character::setPersistentSkillNum(std::vector<int> inp)
{
	persistentSkillNum = inp;
}

void setNumTurnsSkill(int inp)
{
	numTurnsSkill = inp;
}

void Character::setAlive(bool inp)
{
	alive = inp;
}

void Character::setCanAtk(bool inp)
{
	canAtk = inp;
}

void Character::setFinalHp(int inp)
{
	finalHp = inp;
}

void Character::setBattlePos(int inp)
{
	battlePos = inp;
}

void Character::setAllyInParty(bool inp)
{
	allyInParty = inp;
}

void Character::setCurrentExp(int inp)
{
	currentExp = inp;
}

void Character::setRequiredExp()
{
	int numToPow = 1.05;
	requiredExp = pow(numToPow, level);
}

void Character::setChance(int inp)
{
	chance = inp;
}

//********* ACCESSORS ***********
int Character::getLevel()
{
	return level;
}

int Character::getCurrentHp()
{
	return currentHp;
}

int Character::getMaxHp()
{
	return maxHp;
}

int Character::getCurrentMana()
{
	return currentMana;
}

int Character::getMaxMana()
{
	return maxMana;
}

int Character::getStrength()
{
	return strength;
}

int Character::getCurrentStrength()
{
	return currentStrength;
}

int Character::getDefense()
{
	return defense;
}

int Character::getCurrentDefense()
{
	return currentDefense;
}

int Character::getAgility()
{
	return agility;
}

int Character::getCurrentAgility()
{
	return currentAgility;
}	

std::vector<int> Character::getSkillNum()
{
	return skillNum;
}

std::vector<int> Character::getPersistentSkillNum()
{
	return persistentSkillNum;
}

int Character::getNumTurnsSkill()
{
	return numTurnsSkill;
}

bool Character::getAlive()
{
	return alive;
}

bool Character::getCanAtk()
{
	return canAtk;
}

int Character::getFinalHp()
{
	return finalHp;
}

//BattlePos is 0-5 corresponding to battle grid pos
int Character::getBattlePos()
{
	return battlePos;
}

bool Character::getAllyInParty()
{
	return allyInParty;
}

int Character::getCurrentExp()
{
	return currentExp;
}

int Character::getRequiredExp()
{
	return requiredExp;
}

int Character::getChance()
{
	return chance;
}

//ETC
//Recalculates required exp and increments level
//TODO Need indication of level up
void Character::levelUp()
{
	if(currentExp > requiredExp)
	{
		level++;
		currentExp -= requiredExp;
		setRequiredExp();
	}
}
