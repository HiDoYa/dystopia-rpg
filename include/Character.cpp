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
	buffStr = buffDef = buffAgi = 0;

	alive = true;
	canAtk = true;
	//agiMarker

	hpFinal = 100;
	manaFinal = 100;
	battlePos = 0;

	currentExp = 0;
	requiredExp = 1;

	itemEquipped = {-1, -1, -1};

	chance = 5;

	hp.setMaxSize(sf::Vector2f(150, 18));
	mana.setMaxSize(sf::Vector2f(150, 18));

	hp.getCurrentRect()->setFillColor(sf::Color::Red);
	mana.getCurrentRect()->setFillColor(sf::Color::Yellow);

	hp.getLabel()->setCharacterSize(13);
	mana.getLabel()->setCharacterSize(13);
	
	hp.getLabel()->setColor(sf::Color(106, 106, 106));
	mana.getLabel()->setColor(sf::Color(106, 106, 106));

	hp.setLabelPos(2);
	mana.setLabelPos(2);
	
	//Everybody starts off with these 3 basic skills
	possibleSkillNum = {0, 1, 2};
	skillNum = {0, 1, 2};
}

//********* MUTATORS *************
void Character::setName(std::string inp)
{
	name = inp;
}

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

void Character::setBuffStr(int inp)
{
	buffStr = inp;
}

void Character::setBuffDef(int inp)
{
	buffDef = inp;
}

void Character::setBuffAgi(int inp)
{
	buffAgi = inp;
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
	float numToPow = 1.05;
	requiredExp = pow(numToPow, level);
}

void Character::setChance(int inp)
{
	chance = inp;
}

void Character::setDropItemId(std::vector<int> inp)
{
	dropItemId = inp;
}

void Character::setDropItemChance(std::vector<int> inp)
{
	dropItemChance = inp;
}

void Character::pushDropItemId(int inp)
{
	dropItemId.push_back(inp);
}

void Character::pushDropItemChance(int inp)
{
	dropItemChance.push_back(inp);
}

void Character::setHpFinal(int inp)
{
	if(inp < 0)
	{
		inp = 0;
	}
	hpFinal = inp;
}

void Character::setManaFinal(int inp)
{
	if(inp < 0)
	{
		inp = 0;
	}
	manaFinal = inp;
}
//********* ACCESSORS ***********
std::string Character::getName()
{
	return name;
}

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

int Character::getBuffStr()
{
	return buffStr;
}

int Character::getBuffDef()
{
	return buffDef;
}

int Character::getBuffAgi()
{
	return buffAgi;
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

std::vector<int> Character::getDropItemId()
{
	return dropItemId;
}

std::vector<int> Character::getDropItemChance()
{
	return dropItemChance;
}

int Character::getHpFinal()
{
	return hpFinal;
}

int Character::getManaFinal()
{
	return manaFinal;
}

int Character::getTotalStrength()
{
	return strength + buffStr;
}

int Character::getTotalDefense()
{
	return defense + buffDef;
}

int Character::getTotalAgility()
{
	return agility + buffAgi;
}

//ETC

void Character::statBarUpdate()
{
	hp.setStats(currentHp, maxHp, "Health");
	mana.setStats(currentMana, maxMana, "Energy");

	hp.setPosition(sf::Vector2f(getPosition().x - 50, getPosition().y - 65));
	mana.setPosition(sf::Vector2f(getPosition().x - 50, getPosition().y - 35));
}

void Character::drawBars(sf::RenderWindow& win)
{
	hp.drawAll(win);
	mana.drawAll(win);
}

//Recalculates required exp and increments level
//TODO Need indication of level up
bool Character::levelUp()
{
	if(currentExp > requiredExp)
	{
		level++;
		strength += strength / 5;
		defense += defense / 5;
		agility += agility / 5;
		currentExp -= requiredExp;
		setRequiredExp();
		return true;
	}
	return false;
}

void Character::copy(std::shared_ptr<Character> other)
{
	other->setLevel(getLevel());
	other->setName(getName());
	other->setCurrentHp(getCurrentHp());
	other->setMaxHp(getMaxHp());
	other->setCurrentMana(getCurrentMana());
	other->setMaxMana(getMaxMana());
	other->setStrength(getStrength());
	other->setDefense(getDefense());
	other->setAgility(getAgility());
	other->setSkillNum(getSkillNum());
	other->setPossibleSkillNum(getPossibleSkillNum());
	other->setPersistentSkillNum(getPersistentSkillNum());
	other->setNumTurnsSkill(getNumTurnsSkill());
	other->setAlive(getAlive());
	other->setCanAtk(getCanAtk());
	other->setBattlePos(getBattlePos());
	other->setCurrentExp(getCurrentExp());
	other->setRequiredExp();
	other->setChance(getChance());
	other->setDropItemId(getDropItemId());
	other->setDropItemChance(getDropItemChance());
	other->setHpFinal(getHpFinal());
	other->setManaFinal(getManaFinal());
	other->setBuffStr(getBuffStr());
	other->setBuffDef(getBuffDef());
	other->setBuffAgi(getBuffAgi());

	*other->getTexture() = *getTexture();
	other->getSprite()->setTexture(*getTexture());
	other->getSprite()->setTextureRect(getSprite()->getTextureRect());
	other->getSprite()->setScale(getSprite()->getScale());
	other->getSprite()->setPosition(getSprite()->getPosition());
}
