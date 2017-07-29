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

		//Ally options
		sf::Color gridDefault;
		sf::Color allyOptionSelect;
		sf::Color allyOptionDeselect;
		std::vector<std::shared_ptr<ClickButton>> allyOptions; //Stores actual option shapes

		std::vector<std::shared_ptr<ClickButton>> chooseAlly;  //Grid for allies
		std::vector<std::shared_ptr<ClickButton>> chooseEnemy; //Grid for enemies
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
		bool selfFocus;
		bool multAllyFocus;
		bool multEnemyFocus;

		//To iterate through skills to check for effects
		int currentSkillCheck;
		
		//Only stores singular targets
		int currentSelected;
		
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
		void setSkillIcons();

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

		void skillCalc();
		void manaChange();
		void chargeCalc(std::vector<std::shared_ptr<Character>>&);
		void skillCalcHealth(std::vector<std::shared_ptr<Character>>&, 
				std::vector<std::shared_ptr<Character>>&);
		void skillCalcStat(std::vector<std::shared_ptr<Character>>&, 
				std::vector<std::shared_ptr<Character>>&);

		bool allyTurnHandle(int&, sf::RenderWindow&);
		bool allyChangePos(sf::RenderWindow& win);
		bool changePosAnimation();
		void allyAttemptFlee(int&);

		void enemyTurnHandle(int&);

		//Battle state 7
		void hpAnimate(int&);
		void barChangeCalc(std::vector<std::shared_ptr<Character>>&);
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
