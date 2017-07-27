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
		//TODO Wait for click before continuing in certain areas
		//TODO Update battle log

		//Ally options
		sf::Color gridDefault;
		sf::Color allyOptionSelect;
		sf::Color allyOptionDeselect;
		std::vector<std::shared_ptr<ClickButton>> allyOptions; //Stores actual option shapes

		//TODO Draw grid (when there aren't buttons). Make it transparent
		std::vector<std::shared_ptr<ClickButton>> chooseAlly;  //Grid for allies
		std::vector<std::shared_ptr<ClickButton>> chooseEnemy; //Grid for enemies
		int currentPlayerForOption;                //Stores which character to show the options around
		int currentOption;                     //Stores the option chosen by ally

		//Time management
		sf::Clock clk;
		sf::Time tme;
		float currentTime;
		float lastTime;
		bool lastTimeSet;

		//For animation
		int attackXDisp;
		int goalPlace;
		int oldBattlePos;

		//Flags
		bool animComplete;
		bool singularAllyFocus;
		bool singularEnemyFocus;
		bool multAllyFocus;
		bool multEnemyFocus;

		int currentSkillCheck; //To iterate through skills to check for effects
		
		//Only stores singular targets
		//TODO These can be stored in a single variable
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
	public:
		Battle();

		void setupBattle(std::vector<std::shared_ptr<Character>>,
				std::vector<std::shared_ptr<Character>>&,
				std::vector<std::shared_ptr<Skill>>, std::vector<int>);

		//Battle state 0
		void findFastestChar(int&);
		void setSkillNames();

		//Battle state 1
		void statusHandle(int&);
		void checkForStatus();
		void allyStatusEffect();
		void enemyStatusEffect();
		
		//Battle state 2
		void allySkillChoiceHandler(int&, sf::RenderWindow&);

		//Battle state 3
		void allyChooseFocus(int&, sf::RenderWindow&);
		void findSingularFocus();
		bool changeAllyFocus(sf::RenderWindow&);
		bool changeEnemyFocus(sf::RenderWindow&);
		void resetGrid();

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
		void handleEffect(int&, sf::RenderWindow&);
		int findHpChangeSign(int, int);

		int findNextTarget(int);
		int processSkillTargetting();

		bool allyTurnHandle(int&, sf::RenderWindow&);

		void allySkillCalc();
		void allySkillCalcHealth();
		void allySkillCalcStat();

		void allyItem();
		bool allyChangePos(sf::RenderWindow& win);
		bool changePosAnimation();
		void allyAttemptFlee(int&);

		void enemyTurnHandle(int&);
		void enemySkillCalc();
		void enemySkillCalcHealth();
		void enemySkillCalcStat();

		//Battle state 7
		void hpAnimate(int&);
		void allyHpChange();
		void enemyHpChange();
		//TODO Generic buff, debuff, attack, heal animations
		//TODO For enemies, simply filp the textures
		void allySkillAnimate();
		void enemySkillAnimate();
		void checkForCompletion(int&);

		//Battle state 8
		void moveBackwardAnimation(int&);
		void allyPostAttackAnimation(int&);
		void enemyPostAttackAnimation(int&);
		
		//Battle state 9
		bool checkAllyDeath();
		bool checkEnemyDeaths();
		void checkEndBattle(int&, int&, std::vector<int>, 
				std::vector<std::shared_ptr<Character>>);
		void newTurn();
		
		//Drawing
		void drawAll(sf::RenderWindow&, int);

		//Utility
		int getMaxNum(int, int);
		void showCharacterInfo(sf::RenderWindow&);
		void delayState(int&, int);
};

#endif
