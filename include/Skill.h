#ifndef SKILL_H
#define SKILL_H

class Skill
{
	private:
		//For enemy, all skills are equipped.
		//For ally/player, only some skills are equipped
		std::string name;
		int manaCost;

		//Number of turns for effect
		int maxNumTurns;

		//Shows multiple damage nums for one attack (think trip strike)
		int numAtksPerHit;

		//If attack misses
		bool missed;

		//Whether to reapply effect each turn. Uses oldVal and adds newVal on top for the new change.
		std::vector<bool> reapplyTurn;
		//Old value stores the past health change and buff amounts. Used because buff/debuff amounts are constant for the duration in which they act, and health changes can increase each turn 
		std::vector<int> oldVal;

		//Element 0 for damage, 1 for heals, 2 for debuffs, 3 for buffs
		std::vector<float> mult;
		std::vector<int> max;
		std::vector<int> min;
		//Percent is for percent damage, heals, debuffs, buffs
		//Still uses mult, max, min for percent, max dmg possible, min dmg possible
		//If mult is 0, effect is nothing
		//If percent is true, multiplier becomes percent (out of 100)
		std::vector<bool> percent;
		//Accuracy, pierce, crit are percent based (out of 100)
		//Crit increases the magnitude of effect. Only applies for attacks
		int crit;
		int accuracy;
		//0 for selected ally, 1 for selected enemy, 2 for all allies, 3 for all enemies, 4 for self
		//There can only be one (0 or 1) in the "target" vector because can only choose the target once
		std::vector<int> target;
	public:
		Skill();
		
		//TODO Formulas based on attacker stats/attacked stats. Return damage amount
		
		//****** MUTATORS *********
		void setName(std::string);
		void setChance(int);
		void setManaCost(int);
		void setMaxNumTurns(int);
		void setNumAtksPerHit(int);
		void setReapplyTurn(int, int);
		void setMult(int, int);
		void setMax(int, int);
		void setMin(int, int);
		void setPercent(int, bool);
		void setCrit(int);
		void setAccuracy(int);
		void setTarget(int, int);

		//****** ACCESSORS *********
		std::string getName();
		int getChance();
		int getManaCost();
		int getMaxNumTurns();
		int getNumAtksPerHit();
		std::vector<bool> getReapplyTurn();
		std::vector<int> getMult();
		std::vector<int> getMax();
		std::vector<int> getMin();
		std::vector<bool> getPercent();
		int getCrit();
		int getAccuracy();
		std::vector<int> getTarget();
		
		//***** UTILITY ************
		int checkForSelection();
		
		//***** DAMAGE UTILITY ************
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
