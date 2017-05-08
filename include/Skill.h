#ifndef SKILL_H
#define SKILL_H

class Skill
{
	private:
		//For enemy, all skills are equipped.
		//For ally/player, only some skills are equipped
		std::string name;
		int chance;
		bool currentlyEquipped;
		int manaCost;

		//Number of turns for effect
		int maxNumTurns;
		//Whether to reapply effect each turn. Uses oldVal and adds newVal on top for the new change.
		bool reapplyTurn;
		//Old value stores the past health change and buff amounts. Used because buff/debuff amounts are constant for the duration in which they act, and health changes can increase each turn 
		std::vector<int> oldVal;

		//Shows multiple damage nums for one attack (think trip strike)
		int numAtksPerHit;

		//If attack misses
		bool missed;

		//Element 0 for damage, 1 for heals, 2 for debuffs, 3 for buffs
		std::vector<float> mult;
		std::vector<int> max;
		std::vector<int> min;
		//Percent is for percent damage, heals, debuffs, buffs
		//Still uses mult, max, min for percent, max dmg possible, min dmg possible
		//If percent is true, multiplier becomes percent (out of 100)
		std::vector<bool> percent;
		//Accuracy, pierce, crit are percent based (out of 100)
		//Crit increases the magnitude of effect. Only applies for attacks
		int crit;
		int accuracy;
		//Elements (fire/ice/water/etc). Only applies for attacks
		int element;
		//0 for selected ally, 1 for selected enemy, 2 for all allies, 4 for all enemies
		std::vector<int> target;
	public:
		Skill();
		
		//TODO Formulas based on attacker stats/attacked stats. Return damage amount
		
		//****** MUTATORS *********
		void setName(std::string);
		void setChance(int);
		void setCurrentlyEquipped(bool);
		void setManaCost(int);
		void setMult(int, int);
		void setMax(int, int);
		void setMin(int, int);
		void setPercent(int, bool);
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
		std::vector<int> getMult();
		std::vector<int> getMax();
		std::vector<int> getMin();
		std::vector<bool> getPercent();
		int getCrit();
		int getAccuracy();
		int getElement();
		std::vector<int> getTarget();
		std::vector<bool> getTargetNum();
		
		//***** UTILITY ************
		int checkForMaxMin(int, int);
		int checkForCrit(int);
		int checkForMiss(int);

		//****** DAMAGE CALC *********
		int healthChangeHandle(int, int, int);
		int normCalc(int, int, int);
		int percentCalc(int, int, int, int);

		int statChangeHandle(int, int);

		//****** TEXT *********
		std::string dispText(std::string, int);
};

#endif
