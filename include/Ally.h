#include "SpriteManage.h"

#include "Skill.h"

#ifndef ALLY_H
#define ALLY_H

class Ally: public SpriteManage
{
	private:
		//Skills
		std::vector<Skill> skill;
		
		//Attributes
		std::string name;
		int level;
		int currentHp;
		int maxHp;
		int currentMana;
		int maxMana;

		int strength;
		int defense;
		int agility;

		//Etc
		int currentExp;
		int requiredExp;

		bool canAtk;
		bool allyInParty;
		bool alive;
		int battlePos;
	public:
		Ally();

		//****** Mutators ********
		void setName(std::string);
		void setLevel(int);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);

		void setStrength(int);
		void setDefense(int);
		void setAgility(int);

		//Etc
		void setCurrentExp(int);
		void setRequiredExp(int);

		void setCanAtk(bool);
		void setAlive(bool);
		void setBattlePos(int);
		void setAllyInParty(bool);

		//****** Mutators ********
		std::string getName();
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();

		int getStrength();
		int getDefense();
		int getAgility();

		//Etc
		int getCurrentExp();
		int getRequiredExp();

		//TODO CREATE HEALTH BARS/MANA BARS FOR ALLIES LIKE FOR ENEMIES
		bool getCanAtk();
		bool getAlive();
		int getBattlePos();
		bool getAllyInParty();

		std::vector<Skill> getSkill();
};

#endif
