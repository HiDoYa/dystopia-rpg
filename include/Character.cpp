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

	hpFinal = 100;
	manaFinal = 100;
	battlePos = 0;

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

void Character::setDefense(int inp)
{
	defense = inp;
}

void Character::setAgility(int inp)
{
	agility = inp;
}

void Character::setSkillNum(std::vector<int> inp)
{
	skillNum = inp;
}

void Character::setPossibleSkillNum(std::vector<int> inp)
{
	possibleSkillNum = inp;
}

void Character::setPersistentSkillNum(std::vector<int> inp)
{
	persistentSkillNum = inp;
}

void Character::setNumTurnsSkill(std::vector<int> inp)
{
	numTurnsSkill = inp;
}

void Character::decrementNumTurnsSkill(int element)
{
	if(numTurnsSkill[element] != 0)
	{
		numTurnsSkill[element] -= 1;
	}
}

void Character::setAlive(bool inp)
{
	alive = inp;
}

void Character::setCanAtk(bool inp)
{
	canAtk = inp;
}

void Character::setBattlePos(int inp)
{
	battlePos = inp;
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

void Character::setHpFinal(int inp)
{
	hpFinal = inp;
}

void Character::setManaFinal(int inp)
{
	manaFinal = inp;
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

int Character::getDefense()
{
	return defense;
}

int Character::getAgility()
{
	return agility;
}

std::vector<int> Character::getSkillNum()
{
	return skillNum;
}

std::vector<int> Character::getPossibleSkillNum()
{
	return possibleSkillNum;
}

std::vector<int> Character::getPersistentSkillNum()
{
	return persistentSkillNum;
}

std::vector<int> Character::getNumTurnsSkill()
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

//BattlePos is 0-5 corresponding to battle grid pos
int Character::getBattlePos()
{
	return battlePos;
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

int Character::getHpFinal()
{
	return hpFinal;
}

int Character::getManaFinal()
{
	return manaFinal;
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
