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
		bool canAtk;
		bool allyInParty;
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
		void setCanAtk(bool);
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
		bool getCanAtk();
		int getBattlePos();
		std::vector<Skill> getSkill();

		bool getAllyInParty();
};

#endif
