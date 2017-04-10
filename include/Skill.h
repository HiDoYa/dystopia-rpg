#ifndef SKILL_H
#define SKILL_H

class Skill
{
	private:
		//For enemy, all skills are equipped.
		//For ally/player, only some skills are equipped
		bool currentlyEquipped;
		int manaCost;

		//Number of turns for effect
		int numTurns;
		//Whether to reapply effect each turn
		bool reapplyTurn;

		//Shows multiple damage nums for one attack (think trip strike)
		int numAtksPerHit;

		//How the attack will be displayed as text
		std::string attackSuccess;
		std::string attackFail;

		//Element 0 for damage/heal, 1 for buffs/debuffs
		std::vector<int> mult;
		std::vector<int> max;
		std::vector<int> min;
		//Accuracy, pierce, crit are percent based (out of 100)
		//Crit increases the magnitude of effect. Pierce for buffs/debuffs does nothing
		std::vector<int> crit;
		std::vector<int> accuracy;
		std::vector<int> pierce;
		//Elements (fire/ice/water/etc). Does nothing for buffs/debuffs
		std::vector<int> element;
		//0 for self, 1 for ally, 2 for enemy. If 0/1 and target is multiple, it targets all of allies
		std::vector<int> target;
		//true if single target, false if multiple targets
		std::vector<bool> targetNum;
	public:
		Skill();
		
		//TODO Formulas based on attacker stats/attacked stats. Return damage amount
		
		//****** MUTATORS *********
		void setMult(int, int);
		void setMax(int, int);
		void setMin(int, int);
		void setCrit(int, int);
		void setAccuracy(int, int);
		void setPierce(int, int);
		void setElement(int, int);
		void setTarget(int, int);
		void setTargetNum(int, bool);

		//****** ACCESSORS *********
		std::vector<int> getMult();
		std::vector<int> getMax();
		std::vector<int> getMin();
		std::vector<int> getCrit();
		std::vector<int> getAccuracy();
		std::vector<int> getPierce();
		std::vector<int> getElement();
		std::vector<int> getTarget();
		std::vector<bool> getTargetNum();
		
		//****** DAMAGE CALC *********
		int getDamageCalc(int, int, int);
		int getNormDamageCalc(int, int);
		int getPercentDamageCalc(int, int, int);
};

#endif
