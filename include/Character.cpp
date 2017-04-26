#include <SFML/Graphics.hpp>
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

void Character::setDefense(int inp)
{
	defense = inp;
}

void Character::setAgility(int inp)
{
	agility = inp;
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

void Character::setAllyInParty(bool inp)
{
	allyInParty = inp;
}

void Character::setCurrentExp(int inp)
{
	currentExp = inp;
}

void Character::setRequiredExp(int inp)
{
	requiredExp = inp;
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

int Character::getDefense()
{
	return defense;
}

int Character::getAgility()
{
	return agility;
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

std::vector<Skill> Character::getSkill()
{
	return skill;
}
