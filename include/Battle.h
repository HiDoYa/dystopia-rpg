#include "Character.h"
#include "Skill.h"
#include "UIOverlay.h"

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles class Battle
class Battle
{
	private:
		//TODO Keep "skills" in file for enemy, file for ally. When accessing skill, only use the number (id number associated with skill)

		//Ally options
		std::vector<sf::CircleShape*> allyOptions; //Stores actual option shapes
		int currentOptionShow;                    //Stores which character to show the options around
		int currentOptionAlly;                    //Stores the option chosen

		//Enemy optiosn
		int currentOptionEnem;                    //Stores the skill the enemy chooses

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
		//nextCharType is 0 if ally, 1 if enemy, -1 if nobody
		int nextCharType;
		//nextCharCounter is the index in the array (for ally and enemies)
		int nextCharCounter;
		int goalPlace;

		//TODO If all players or all enemies are to be targeted, don't need to SELECT which target
		
		int currentTarget;
		std::vector<int> currentEnemySelected;
		//Allies in front more likely to be chosen, otherwise randomized
		std::vector<int> currentAllySelected;

		//For keeping track of whether the user can target enemy or ally (only for singular)
		bool singularAllyFocus;
		bool singularEnemyFocus;

		//Skill Pressed
		bool spaceNotPressed;
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		std::vector<Character*> ally;
		std::vector<Character> enemies;
		std::vector<Skill> allySkill;
		std::vector<Skill> enemySkill;

		//Check for competion
		bool animComplete;

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;
	public:
		Battle();

		void setupBattle(std::vector<Character>, std::vector<Character*>&, std::vector<Skill>, std::vector<Skill>);

		//Battle state 0
		void findFastestChar();
		void checkForStatus(int);
		void checkForNextChar(int&);

		//Battle state 1
		void setCirclePos();
		void changeCurrentSkill();
		void chooseCurrentSkill(int&);

		//Battle state 2
		void attackEnemyType();
		void changeAllyFocus();
		void changeEnemyFocus();
		void chooseEnemyFocus(int&);

		//Battle state 3
		void attackManager(int&, int&);
		void allyTurnHandle(int&, int&);

		//For various damaging of enemies
		void attemptFlee(int&);
		void allyChangePos();
		void allyItem();
		void allyAttackAnimation(int&);

		void enemyChooseSkill();
		void enemyChooseTarget();
		void enemyAttackAnimation(int&);

		//Battle state 4
		void effectCalc(int&);
		//TODO Do I need?
		int findHpChangeSign(int, int);

		//TODO Takes extra integer indicating which enemy will be targeted. Recursion to finish all hp changes.
		void allyHpChange(int&);
		void enemyHpChange(int&);

		void allyPostAttackAnimation();
		void enemyPostAttackAnimation();
		void checkForCompletion(int&);
		
		//Battle state 5
		bool checkAllyDeath();
		bool checkEnemyDeaths();
		void checkEndBattle(int&, int&);
		void currentEnemyDeath();
		void newTurn();
		
		//Drawing
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);

		//Utility
		int getMaxNum(int, int);
};

#endif
