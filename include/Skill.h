#ifndef SKILL_H
#define SKILL_H

class Skill
{
	private:
		//For enemy, all skills are equipped.
		//For ally/player, only some skills are equipped
		std::string name;
		std::string description;
		int powerRating;
		int manaCost;

		//Shows multiple damage nums for one attack (think trip strike)
		int numAtksPerHit;

		//If attack misses
		bool missed;

		//Whether to reapply effect each turn. Uses oldVal and adds newVal on top for the new change.
		//Stores the number of turns for the effect. (0 if no reapply)
		std::vector<int> reapplyTurn;
		//Old value stores the past health change and buff amounts. Used because buff/debuff amounts are constant for the duration in which they act, and health changes can increase each turn 
		std::vector<int> oldVal;

		//Element 0 for damage, 1 for heals, 2 for debuffs, 3 for buffs
		std::vector<float> mult;
		std::vector<int> max;
		std::vector<int> min;
		//If mult is 0, effect is nothing

		//If percent is true, multiplier becomes percent (out of 100)
		std::vector<bool> percent;
		//Accuracy, pierce, crit are percent based (out of 100)
		
		//Type is 0 for strength, 1 for defense, 2 for agility
		//TODO CHange to vector (for multiple stat changes)
		int buffType;
		int debuffType;

		//Crit increases the magnitude of effect. Only applies for attacks
		int crit;
		int accuracy;
		//There can only be one (0 or 1) in the "target" vector because can only choose the target once

		//For enemies: chance that the skill is chosen
		int chance;

		//0 for selected ally, 1 for selected enemy, 2 for all allies, 3 for all enemies, 4 for self
		std::vector<int> target;
		//Includes indexes of allies which can equip the skill
		std::vector<int> allyEquip;
	public:
		Skill();
		
		//TODO Formulas based on attacker stats/attacked stats. Return damage amount
		
		//****** MUTATORS *********
		void setName(std::string);
		void setDescription(std::string);
		void setPowerRating(int);
		void setChance(int);
		void setManaCost(int);
		void setNumTurns(int);
		void setNumAtksPerHit(int);
		void setReapplyTurn(int, int);
		void setOldVal(int, int);
		void setMult(int, float);
		void setMax(int, int);
		void setMin(int, int);
		void setBuffType(int);
		void setDebuffType(int);
		void setPercent(int, bool);
		void setCrit(int);
		void setAccuracy(int);
		void setTarget(int, int);
		void setAllyEquip(std::vector<int>);

		//****** ACCESSORS *********
		std::string getName();
		std::string getDescription();
		int getPowerRating();
		int getChance();
		int getManaCost();
		int getNumTurns();
		int getNumAtksPerHit();
		std::vector<int> getReapplyTurn();
		std::vector<int> getOldVal();
		std::vector<float> getMult();
		std::vector<int> getMax();
		std::vector<int> getMin();
		int getBuffType();
		int getDebuffType();
		std::vector<bool> getPercent();
		int getCrit();
		int getAccuracy();
		std::vector<int> getTarget();
		std::vector<int> getAllyEquip();
		
		//***** UTILITY ************
		int checkForSelection();
		
		//***** DAMAGE UTILITY ************
		int checkForMaxMin(int, int);
		int checkForCrit(int);
		void checkForMiss();

		//****** DAMAGE CALC *********
		int healthChangeHandle(int, int, int, int);
		int statChangeHandle(int, int, int, int);

		int normCalc(int, int, int);
		int percentCalc(int, int, int, int);

		//****** TEXT *********
		std::string dispText(std::string, std::string, int);
};

#endif
