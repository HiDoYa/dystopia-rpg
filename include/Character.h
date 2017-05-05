#include "SpriteManager.h"

#include "Skill.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character: public SpriteManager
{
	private:
		//Attributes
		int level;
		int currentHp;
		int maxHp;
		int currentMana;
		int maxMana;

		int strength;
		int defense;
		int agility;

		std::vector<Skill> skill;

		bool alive;
		bool canAtk;
		int finalHp; //For calculations
		int battlePos;

		//For allies
		bool allyInParty;
		int currentExp;
		int requiredExp;
		
		//For enemies
		int chance;
	public:
		Character();

		//****** Mutators ********
		void setLevel(int);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);

		void setStrength(int);
		void setDefense(int);
		void setAgility(int);

		void setAlive(bool);
		void setCanAtk(bool);
		void setFinalHp(int);
		void setBattlePos(int);

		void setAllyInParty(bool);
		void setCurrentExp(int);
		void setRequiredExp(int);

		void setChance(int);

		//****** Accessors ********
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();

		int getStrength();
		int getDefense();
		int getAgility();

		bool getAlive();
		bool getCanAtk();
		int getFinalHp();
		int getBattlePos();

		bool getAllyInParty();
		int getCurrentExp();
		int getRequiredExp();

		int getChance();

		std::vector<Skill> getSkill();

		//TODO Calculate requiredExp based on level and slight randomization
};

#endif
