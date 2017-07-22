#include "BattleOverlay.h"
#include "ClickButton.h"
#include "Character.h"
#include "Skill.h"
#include "UIOverlay.h"

#include <memory>

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemy and battles class Battle
class Battle
{
	private:
		BattleOverlay battleOverlay;
		//TODO Keep "skills" in file for enemy, file for ally. When accessing skill, only use the number (id number associated with skill)

		//Ally options
		sf::Color allyOptionSelect;
		sf::Color allyOptionDeselect;
		std::vector<std::shared_ptr<ClickButton>> allyOptions; //Stores actual option shapes

		//TODO Draw grid (when there aren't buttons). Make it transparent
		std::vector<std::shared_ptr<ClickButton>> chooseAlly;  //Grid for allies
		std::vector<std::shared_ptr<ClickButton>> chooseEnemy; //Grid for enemies
		int currentPlayerForOption;                //Stores which character to show the options around
		int currentOptionAlly;                     //Stores the option chosen by ally
		int currentOptionEnemy;                    //Stores the skill the enemy chooses

		//Time management
		sf::Clock clk;
		sf::Time tme;
		float currentTime;
		float lastTime;

		//For animation
		int attackXDisp;
		int goalPlace;

		//Flags
		bool animComplete;
		bool singularAllyFocus;
		bool singularEnemyFocus;
		bool multAllyFocus;
		bool multEnemyFocus;

		int currentSkillCheck; //To iterate through skills to check for effects
		int currentTarget;
		
		//Only stores singular targets
		int currentEnemySelected;
		int currentAllySelected;
		
		//Characters and skills
		std::vector<std::shared_ptr<Character>> ally;
		std::vector<std::shared_ptr<Character>> enemy;
		std::vector<std::shared_ptr<Skill>> skillList; //Use for both ally and enemy
		int nextCharType;    //0 if ally, 1 if enemy, -1 if nobody
		int nextCharCounter; //The index in the array (ally and enemy)

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;
	public:
		Battle();

		void setupBattle(std::vector<std::shared_ptr<Character>>,
				std::vector<std::shared_ptr<Character>>&,
				std::vector<std::shared_ptr<Skill>>, std::vector<int>);

		//Battle state 0
		void findFastestChar(int&);

		//Battle state 1
		void statusHandle(int&);
		void checkForStatus();
		void allyStatusEffect();
		void enemyStatusEffect();
		
		//Battle state 2
		void allySkillChoiceHandler(int&, sf::RenderWindow&);
		void setCirclePos();

		//Battle state 3
		void allyChooseFocus(int&, sf::RenderWindow&);
		void findSingularFocus();
		bool changeAllyFocus(sf::RenderWindow&);
		bool changeEnemyFocus(sf::RenderWindow&);

		//Battle state 4
		void enemyDecision(int&);
		void enemyChooseSkill();
		void enemyChooseAlly();
		void enemyChooseEnemy();

		//Battle state 5
		void moveForwardAnimation(int&);
		void allyAttackAnimation(int&);
		void enemyAttackAnimation(int&);

		//Battle state 6
		void handleEffect(int&);
		int findHpChangeSign(int, int);

		int findNextTarget(int);
		int processSkillTargetting();

		void allyTurnHandle(int&);

		void allySkillCalc();
		void allySkillCalcHealth();
		void allySkillCalcStat();

		void allyItem();
		void allyChangePos();
		void allyAttemptFlee(int&);

		void enemyTurnHandle(int&);
		void enemySkillCalc();
		void enemySkillCalcHealth();
		void enemySkillCalcStat();

		//Battle state 7
		void hpAnimate(int&);
		void allyHpChange();
		void enemyHpChange();
		void checkForCompletion(int&);

		//Battle state 8
		void moveBackwardAnimation(int&);
		void allyPostAttackAnimation(int&);
		void enemyPostAttackAnimation(int&);
		
		//Battle state 9
		bool checkAllyDeath();
		bool checkEnemyDeaths();
		void checkEndBattle(int&, int&, std::vector<int>, std::vector<std::shared_ptr<Character>>);
		void currentEnemyDeath();
		void newTurn();
		
		//Drawing
		void drawAll(sf::RenderWindow&, int);

		//Utility
		int getMaxNum(int, int);
};

#endif
