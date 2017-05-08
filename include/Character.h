#include "SpriteManager.h"

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

		//Strength, defense, agility can be changed through battle, but resets after battle
		int strength;
		int currentStrength;
		int defense;
		int currentDefense;
		int agility;
		int currentAgility;

		std::vector<int> skillNum;
		std::vector<int> persistentSkillNum;
		int numTurnsSkill;

		bool alive;
		bool canAtk;
		//TODO need?
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
		void setCurrentStrength(int);
		void setDefense(int);
		void setCurrentDefense(int);
		void setAgility(int);
		void setCurrentAgility(int);

		void setSkillNum(std::vector<int>);
		void setPersistentSkillNum(std::vector<int>);
		void setNumTurnsSkill(int);

		void setAlive(bool);
		void setCanAtk(bool);
		void setFinalHp(int);
		void setBattlePos(int);

		void setAllyInParty(bool);
		void setCurrentExp(int);
		void setRequiredExp();

		void setChance(int);

		//****** Accessors ********
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();

		int getStrength();
		int getCurrentStrength();
		int getDefense();
		int getCurrentDefense();
		int getAgility();
		int getCurrentAgility();

		std::vector<int> getSkillNum();
		std::vector<int> getPersistentSkillNum();
		int getNumTurnsSkill();

		bool getAlive();
		bool getCanAtk();
		int getFinalHp();
		int getBattlePos();

		bool getAllyInParty();
		int getCurrentExp();
		int getRequiredExp();

		int getChance();

		//TODO Calculate requiredExp based on level and slight randomization
		//********* ETC ***********
		void levelUp();
};

#endif
