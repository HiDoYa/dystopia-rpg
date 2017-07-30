#include "SpriteManager.h"
#include "StatBar.h"
#include <memory>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character: public SpriteManager
{
	private:
		std::string name;

		StatBar hp;
		StatBar mana;

		//Attributes
		int level;
		int currentHp;
		int maxHp;
		int currentMana;
		int maxMana;

		int strength;
		int defense;
		int agility;

		//For use in battle
		int buffStr;
		int buffDef;
		int buffAgi;

		//Shows the items equipped (index 0 -> weapon, 1 -> armor, 2 -> OS)
		std::vector<int> itemEquipped;

		//Stores ID for each skill
		std::vector<int> skillNum;         //For use in battle
		std::vector<int> possibleSkillNum; //For all possible equippable skills (for allies)

		//TODO Rework persistent skills
		//For continuous/status effects. Can be damaging/debuff
		std::vector<int> persistentSkillNum;
		std::vector<int> numTurnsSkill;

		bool alive;
		bool canAtk;

		int hpFinal;   //Stores target value after change
		int manaFinal; //Stores target value after change
		int battlePos;

		//For allies
		float currentExp;
		float requiredExp;
		//TODO Number determining the exp curve? (seed?)
		
		//For enemies
		//Chance of showing (out of 100)
		int chance;
		std::vector<int> dropItemId;
		std::vector<int> dropItemChance;
	public:
		Character();

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

		void setBuffStr(int);
		void setBuffDef(int);
		void setBuffAgi(int);

		void setSkillNum(std::vector<int>);
		void setPossibleSkillNum(std::vector<int>);
		void setPersistentSkillNum(std::vector<int>);
		void setNumTurnsSkill(std::vector<int>);
		void decrementNumTurnsSkill(int);

		void setAlive(bool);
		void setCanAtk(bool);
		void setBattlePos(int);

		void setCurrentExp(float);
		void setRequiredExp();

		void setChance(int);

		void setDropItemId(std::vector<int>);
		void setDropItemChance(std::vector<int>);

		void pushDropItemId(int);
		void pushDropItemChance(int);

		void setHpFinal(int);
		void setManaFinal(int);

		//****** Accessors ********
		std::string getName();
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();

		int getStrength();
		int getDefense();
		int getAgility();

		int getBuffStr();
		int getBuffDef();
		int getBuffAgi();

		std::vector<int> getSkillNum();
		std::vector<int> getPossibleSkillNum();
		std::vector<int> getPersistentSkillNum();
		std::vector<int> getNumTurnsSkill();

		bool getAlive();
		bool getCanAtk();
		int getBattlePos();

		float getCurrentExp();
		float getRequiredExp();

		int getChance();
		std::vector<int> getDropItemId();
		std::vector<int> getDropItemChance();

		int getHpFinal();
		int getManaFinal();

		//STAT IN BATTLE
		int getTotalStrength();
		int getTotalDefense();
		int getTotalAgility();

		//TODO Calculate requiredExp based on level and slight randomization
		//********* ETC ***********
		void statBarUpdate();
		void drawBars(sf::RenderWindow&);
		void levelUp();
		void copy(std::shared_ptr<Character>);
};

#endif
