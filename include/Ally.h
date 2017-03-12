#include "SpriteManage.h"

#ifndef ALLY_H
#define ALLY_H

class Ally: public SpriteManage
{
	private:
		//TODO Usage

		//Attributes
		int level;
		int maxHp;
		int currentHp;
		int maxMana;
		int currentMana;
		int agility;
		int atk;
		int exp;

		//Battle
		int battlePos;
	public:
		Ally();

		//****** Mutators ********
		void setLevel(int);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);
		void setAgility(int);
		void setAtk(int);
		void setExp(int);
		void setBattlePos(int);

		//****** Mutators ********
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();
		int getAgility();
		int getAtk();
		int getExp();
		int getBattlePos();
};

#endif
