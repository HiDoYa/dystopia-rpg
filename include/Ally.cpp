#include <SFML/Graphics.hpp>
#include <iostream>

#include "Ally.h"

Ally::Ally()
{
}

//********* MUTATORS *************
void Ally::setName(std::string inp)
{
	name = inp;
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

//Default attributes
void Ally::setdefaultHp(int inp)
{
	defaultHp = inp;
}

void Ally::setDefaultMana(int inp)
{
	defaultMana = inp;
}

void Ally::setDefaultAgility(int inp)
{
	defaultAgility = inp;
}

void Ally::setDefaultAtk(int inp)
{
	defaultAtk = inp;
}

//Increase in attributes
void Ally::setHpInc(int inp)
{
	hpInc = inp;
}

void Ally::setManaInc(int inp)
{
	manaInc = inp;
}

void Ally::setAgilityInc(int inp)
{
	agilityInc = inp;
}

void Ally::setAtkInc(int inp)
{
	atkInc = inp;
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

//Default values
int Ally::getDefaultHp()
{
	return defaultHp;
}

int Ally::getDefaultMana()
{
	return defaultMana;
}

int Ally::getDefaultAgility()
{
	return defaultAgility;
}

int Ally:;getDefaultAtk()
{
	return defaultAtk;
}

//Stats increase
int Ally::getHpInc()
{
	return hpInc;
}

int Ally::getManaInc()
{
	return manaInc;
}

int Ally::getAgilityInc()
{
	return agilityInc;
}

int Ally::getAtkInc()
{
	return atkInc;
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

//********** USED FOR LEVELING UP ***********
void Ally::levelUp(int playerLevel)
{
	maxHp = currentHp = (playerLevel - 1) * hpInc + defaultHp;
	maxMana = currentMana = (playerLevel - 1) * maanInc + defaultMana;
	agility = (playerLevel - 1) * agilityInc + defaultAgility;
	atk = (playerLevel - 1) * atkInc + defaultAtk;
}

void Ally::loadingAlly(int playerLevel, int currentHpInp, int currentManaInp)
{
	maxHp = playerLevel * hpInc + defaultHp;
	maxMana = playerLevel * maanInc + defaultMana;
	agility = playerLevel * agilityInc + defaultAgility;
	atk = playerLevel * atkInc + defaultAtk;

	currentHp = currentHpInp;
	currentMana = currentManaInp;
}
