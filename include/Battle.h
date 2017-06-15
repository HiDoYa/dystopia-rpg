#include "Character.h"
#include "Skill.h"
#include "UIOverlay.h"

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemy and battles class Battle
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
		//TODO do i need?
		std::vector<int> enemySelected;
		bool finishedEnemyFocus;

		int attackXDisp;
		//nextCharType is 0 if ally, 1 if enemy, -1 if nobody
		int nextCharType;
		//nextCharCounter is the index in the array (for ally and enemy)
		int nextCharCounter;
		int goalPlace;

		//TODO If all players or all enemy are to be targeted, don't need to SELECT which target
		
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
		
		//For enemy
		std::vector<Character*> ally;
		std::vector<Character> enemy;
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
		void findFastestChar(int&);

		//Battle state 1
		void statusHandle(int&);
		void checkForStatus();
		void allyStatusEffect();
		void enemyStatusEffect();
		
		//Battle state 2
		void allySkillChoiceHandler(int&);
		void setCirclePos();
		void changeCurrentSkill();
		bool chooseCurrentSkill();

		//Battle state 3
		void chooseEnemyFocus(int&);
		void processSkillTargetting();
		void attackEnemyType();
		void changeAllyFocus();
		void changeEnemyFocus();

		//Battle state 4
		void enemyDecision(int&);
		void enemyChooseSkill();
		void enemyChooseTarget();

		//Battle state 5
		void moveForwardAnimation(int&);
		void allyAttackAnimation(int&);
		void enemyAttackAnimation(int&);

		//Battle state 6
		void effectCalc(int&);
		int findHpChangeSign(int, int);
		void regularSkillCalc();

		void allyTurnHandle(int&, int&);
		void allyItem();
		void allyChangePos();
		void attemptFlee(int&);

		void allyHpChange(int&);
		void enemyHpChange(int&);
		void checkForCompletion(int&);

		//Battle state 7
		void moveBackwardAnimation(int&);
		void allyPostAttackAnimation();
		void enemyPostAttackAnimation();
		
		//Battle state 8
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
