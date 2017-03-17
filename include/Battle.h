#include "Enemy.h"
#include "UIOverlay.h"

class Player;

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles class Battle
class Battle
{
	private:
		//Player options
		std::vector<sf::CircleShape> tempCircleStore;
		std::vector<std::vector<sf::CircleShape>> allyOptions;
		std::vector<sf::RectangleShape> gridRect;
		int numSkills;
		int currentSkill;
		int currentOptionsShow;
		bool playerCanAttack;
		int initHp;

		//TO keep track of battles
		std::vector<bool> currentCanAtk;
		std::vector<int> enemySelected;
		int totalAlly;

		int attackXDisp;
		int nextAttack;

		//Skill type
		int skillType;
		int currentEnemySelected;

		//Skill Pressed
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		Enemy temp;
		std::vector<Enemy> enemies;
		int goalPlace;
		int numEnemies;

		//Check for competion
		bool hpComplete;
		bool animComplete;

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;
	public:
		Battle();

		void setupBattle(std::vector<Enemy>, Player&, std::vector<bool>);
		void startBattle();
		void endBattle(int&);

		//Battle state 0
		void changeEnemyFocus();
		void changeCurrentSkill();
		int chooseCurrentSkill();

		//Battle state 1
		void findFastestChar(Player&);
		void attackManager(int&, Player&);

		//Battle state 1.5
		void playerTurnHandle();
		void playerAttackAnimation(int&, Player&);
		void enemyTurnHandle();
		void enemyAttackAnimation(int&);
		
		//Battle state 2
		void hpCalculate(int&, Player&, UIOverlay&);
		int findHpChangeSign(int, int);
		void playerHpChange(int, Player&, UIOverlay&, int&);
		void enemyHpChange(int, int&);
		void playerPostAttackAnimation(Player&);
		void enemyPostAttackAnimation();
		void checkForCompletion(int&);
		
		//Battle state 3
		bool checkPlayerDeath(Player&);
		bool checkEnemyDeaths();
		void checkEndBattle(Player&, int&, int&);
		void currentEnemyDeath();
		void newTurn();
		
		//Drawing
		void drawEnemies(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);
		void setInitHp(int);

		//Accessors
		int getEnemyHp(int);
		int getNumEnemies();

		//Utility
		int getMaxNum(int, int);
};

#endif
