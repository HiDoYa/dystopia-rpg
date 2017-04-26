#include "Character.h"
#include "UIOverlay.h"

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles class Battle
class Battle
{
	private:
		//TODO REMOVE TOTALALLY AND NUMENEMIES

		//Ally options
		sf::CircleShape tempCircle;
		std::vector<sf::CircleShape> allyOptions;
		int currentOption;
		int currentOptionsShow;
		//TODO take care of inithp (final hp calculation NOT JUST DAMAGE) in skill class
		int initHp;

		//For changing position of char
		sf::Clock clk;
		sf::Time tme;
		float currentTime;
		float lastTime;
		std::vector<sf::RectangleShape> gridRect;
		int newPos;
		bool blinkTurn;

		//TO keep track of battles
		std::vector<int> enemySelected;

		int attackXDisp;
		int nextCharType;
		int nextCharCounter;
		int goalPlace;

		//Skill type
		int skillType;
		int currentEnemySelected;
		//TODO Choosing of currentAllySelected
		int currentAllySelected;

		//Skill Pressed
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		std::vector<Character*> ally;
		std::vector<Character> enemies;

		//Check for competion
		bool hpComplete;
		bool animComplete;

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;

		//Temp TO DELETE
		int nextAttack;
	public:
		Battle();

		void setupBattle(std::vector<Character>, std::vector<Character*>&);

		//Battle state 0
		void findFastestChar();
		void checkForChoice(int&);

		//Battle state 1
		//TODO Different selection types (e.g. attacking all enemies, ally targetting skill)
		//TODO The focus changes when hovering over different skills
		void changeEnemyFocus();
		void changeCurrentSkill();
		void chooseCurrentSkill(int&);

		//Battle state 2
		void attackManager(int&, int&);

		void allyTurnHandle(int&);
		void enemyTurnHandle();

		//For various damaging of enemies
		void allyAttackHandle();
		void attemptFlee(int&);
		void allyChangePos();
		void allyItem();
		void allyAttackAnimation(int&);
		void enemyAttackAnimation(int&);
		
		//Battle state 3
		void hpCalculate(int&, UIOverlay&);
		int findHpChangeSign(int, int);

		//Takes extra integer indicating which enemy will be targeted. Recursion to finish all hp changes.
		void allyHpChange(int, int&);
		void enemyHpChange(int, int&);

		void allyPostAttackAnimation();
		void enemyPostAttackAnimation();
		void checkForCompletion(int&);
		
		//Battle state 4
		bool checkAllyDeath();
		bool checkEnemyDeaths();
		void checkEndBattle(int&, int&);
		void currentEnemyDeath();
		void newTurn();
		
		//Drawing
		void setCirclePos();
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);
		void setInitHp();

		//Utility
		int getMaxNum(int, int);
};

#endif
