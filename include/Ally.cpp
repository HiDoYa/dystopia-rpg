#include <SFML/Graphics.hpp>
#include <iostream>

#include "Ally.h"

Ally::Ally()
{
}

//********* MUTATORS *************
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

void Ally::setAgility(int inp)
{
	agility = inp;
}

void Ally::setAtk(int inp)
{
	atk = inp;
}

void Ally::setBattlePos(int inp)
{
	battlePos = inp;
}

//********* ACCESSORS ***********

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

int Ally::getAgility()
{
	return agility;
}

int Ally::getAtk()
{
	return atk;
}

int Ally::getExp()
{
	return exp;
}

//BattlePos is 0-5 corresponding to battle grid pos
int Ally::getBattlePos()
{
	return battlePos;
}

