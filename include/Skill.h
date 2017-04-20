#ifndef SKILL_H
#define SKILL_H

class Skill
{
	private:
		//For enemy, all skills are equipped.
		//For ally/player, only some skills are equipped
		std::string name;
		bool currentlyEquipped;
		int manaCost;

		//Number of turns for effect
		int numTurns;
		//Whether to reapply effect each turn
		bool reapplyTurn;

		//Shows multiple damage nums for one attack (think trip strike)
		int numAtksPerHit;

		//If attack misses
		bool missed;

		//Used to calculate damage
		int tempDmg;

		//Element 0 for damage, 1 for heals, 2 for buffs, 3 for debuffs
		std::vector<int> mult;
		std::vector<int> max;
		std::vector<int> min;
		//Accuracy, pierce, crit are percent based (out of 100)
		//Crit increases the magnitude of effect. Only applies for attacks
		int crit;
		int accuracy;
		//Elements (fire/ice/water/etc). Only applies for attacks
		int element;
		//0 for self, 1 for ally, 2 for enemy. If 0/1 and target is multiple, it targets all of allies
		std::vector<int> target;
		//true if single target, false if multiple targets
		std::vector<bool> targetNum;
	public:
		Skill();
		
		//TODO Formulas based on attacker stats/attacked stats. Return damage amount
		
		//****** MUTATORS *********
		void setMult(int);
		void setMax(int);
		void setMin(int);
		void setCrit(int);
		void setAccuracy(int);
		void setElement(int);
		void setTarget(int, int);
		void setTargetNum(int, bool);

		//****** UTILITY *********
		int checkForMaxMin();
		int checkForCrit();
		void checkForMiss();
		int addForElementDamage();

		//****** ACCESSORS *********
		int getMult();
		int getMax();
		int getMin();
		int getCrit();
		int getAccuracy();
		int getElement();
		std::vector<int> getTarget();
		std::vector<bool> getTargetNum();
		
		//***** UTILITY ************
		int checkForMaxMin(int);

		//****** DAMAGE CALC *********
		int getDamageCalc(int, int, int);
		int getNormDamageCalc(int, int);
		int getPercentDamageCalc(int, int, int);
};

#endif
