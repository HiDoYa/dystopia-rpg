#include <SFML/Graphics.hpp>
#include <iostream>

#include "Ally.h"

Ally::Ally()
{
	//Initialization default
	name = "default";
	level = 1;
	maxHp = currentHp = 100;
	maxMana = currentMana = 100;
	strength = defense = agility = 10;
	allyInParty = false;
	battlePos = 0;
}

//********* MUTATORS *************
void Ally::setName(std::string inp)
{
	name = inp;
}

void Ally::setLevel(int inp)
{
	level = inp;
}

void Ally::setCurrentHp(int inp)
{
	currentHp = inp;
}

void Ally::setMaxHp(int inp)
{
	maxHp = inp;
}

void Ally::setCurrentMana(int inp)
{
	currentMana = inp;
}

void Ally::setMaxMana(int inp)
{
	maxMana = inp;
}

void Ally::setStrength(int inp)
{
	strength = inp;
}

void Ally::setDefense(int inp)
{
	defense = inp;
}

void Ally::setAgility(int inp)
{
	agility = inp;
}

//Etc
void Ally::setBattlePos(int inp)
{
	battlePos = inp;
}

void Ally::setAllyInParty(bool inp)
{
	allyInParty = inp;
}

//********* ACCESSORS ***********
std::string Ally::getName()
{
	return name;
}

int Ally::getLevel()
{
	return level;
}

int Ally::getCurrentHp()
{
	return currentHp;
}

int Ally::getMaxHp()
{
	return maxHp;
}

int Ally::getCurrentMana()
{
	return currentMana;
}

int Ally::getMaxMana()
{
	return maxMana;
}

int Ally::getStrength()
{
	return strength;
}

int Ally::getDefense()
{
	return defense;
}

int Ally::getAgility()
{
	return agility;
}

//ETC
//BattlePos is 0-5 corresponding to battle grid pos
int Ally::getBattlePos()
{
	return battlePos;
}

bool Ally::getAllyInParty()
{
	return allyInParty;
}

