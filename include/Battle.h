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
		int currentPlayerForOption;                //Stores which character to show the options around
		int currentOptionAlly;                     //Stores the option chosen by ally
		int currentOptionEnemy;                    //Stores the skill the enemy chooses

		//Time management
		sf::Clock clk;
		sf::Time tme;
		float currentTime;
		float lastTime;

		//For changing position
		std::vector<sf::RectangleShape> gridRect;
		int newPos;
		bool blinkTurn;

		//For animation
		int attackXDisp;
		int goalPlace;

		//Flags
		bool finishedEnemyFocus;
		bool processTargetting;
		bool animComplete;
		bool singularAllyFocus;
		bool singularEnemyFocus;

		int currentSkillCheck; //To iterate through skills to check for effects
		int currentTarget;
		std::vector<int> currentEnemySelected;
		std::vector<int> currentAllySelected;

		//Skill Pressed
		bool spaceNotPressed;
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//Characters and skills
		std::vector<Character*> ally;
		std::vector<Character> enemy;
		std::vector<Skill> allySkill;
		std::vector<Skill> enemySkill;
		int nextCharType;    //0 if ally, 1 if enemy, -1 if nobody
		int nextCharCounter; //The index in the array (ally and enemy)

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;
	public:
		Battle();

		void setupBattle(std::vector<Character>, std::vector<Character*>&, std::vector<Skill>, std::vector<Skill>, std::vector<int>);

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
		int findNextTarget(int);
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
		void handleEffect(int&);
		int findHpChangeSign(int, int);

		void allyTurnHandle(int&);
		void allySkillCalc();
		void allyItem();
		void allyChangePos();
		void allyAttemptFlee(int&);

		void enemyTurnHandle(int&);
		void enemySkillCalc();

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
