#include "SpriteManage.h"

#include "Skill.h"

#ifndef ALLY_H
#define ALLY_H

class Ally: public SpriteManage
{
	private:
		//Skills
		std::vector<Skill> skills;
		
		//Attributes
		std::string name;
		int level; //TODO 
		int maxHp;
		int currentHp;
		int maxMana;
		int currentMana;
		int agility;
		int atk;

		//Default attributes (lvl 1)
		int defaultHp;
		int defaultMana;
		int defaultAgility;
		int defaultAtk;

		//Attributes increase
		int hpInc;
		int manaInc;
		int agilityInc;
		int atkInc;

		//Etc
		bool allyInParty;
		int battlePos;
	public:
		Ally();

		//****** Mutators ********
		void setName(std::string);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);
		void setAgility(int);
		void setAtk(int);

		//Default at lvl 1
		void setDefaultHp(int);
		void setDefaultMana(int);
		void setDefaultAgility(int);
		void setDefaultAtk(int);

		//Stat increase level up
		void setHpInc(int);
		void setManaInc(int);
		void setAgilityInc(int);
		void setAtkInc(int);

		//Etc
		void setBattlePos(int);
		void setAllyInParty(bool);

		//****** Mutators ********
		std::string getName();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();
		int getAgility();
		int getAtk();

		//Default at level 1
		int getDefaultHp();
		int getDefaultMana();
		int getDefaultAgility();
		int getDefaultAtk();

		//Stat increase level up
		int getHpInc();
		int getManaInc();
		int getAgilityInc();
		int getAtkInc();

		//Etc
		int getBattlePos();
		bool getAllyInParty();

		//******* USED FOR LEVELING UP **********
		void levelUp(int);
		void loadingAlly(int, int, int);
};

#endif
