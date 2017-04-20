#include "Enemy.h"
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
		int currentSkill;
		int currentOptionsShow;
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

		//Skill Pressed
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		Enemy temp;
		std::vector<Enemy> enemies;

		//Check for competion
		bool hpComplete;
		bool animComplete;

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;

		//Temp TO DELETE
		int nextAttack;
		bool playerCanAtk;
	public:
		Battle();

		void setupBattle(std::vector<Enemy>, std::vector<Ally*>&);

		//Battle state 0
		void findFastestChar(std::vector<Ally*>);
		void checkForChoice(int&, std::vector<Ally*>&);

		//Battle state 1
		//TODO Different selection types (e.g. attacking all enemies, ally targetting skill)
		//TODO The focus changes when hovering over different skills
		void changeEnemyFocus();
		void changeCurrentSkill();
		void chooseCurrentSkill(int&);

		//Battle state 2
		void attackManager(int&, std::vector<Ally*>&, int&);

		void playerTurnHandle(int&);
		void allyTurnHandle(int&, std::vector<Ally*>&);
		void enemyTurnHandle();

		//For various damaging of enemies
		void playerAllyAttackHandle();
		void attemptFlee(int&);

		void playerItem();
		void playerChangePos();

		void allyItem(std::vector<Ally*>&);
		void allyChangePos(std::vector<Ally*>&);

		void playerAttackAnimation(int&);
		void allyAttackAnimation(int&, std::vector<Ally*>&);
		void enemyAttackAnimation(int&);
		
		//Battle state 3
		void hpCalculate(int&, UIOverlay&);
		int findHpChangeSign(int, int);

		//Takes extra integer indicating which enemy will be targeted. Recursion to finish all hp changes.
		void playerHpChange(int, UIOverlay&, int&);
		void allyHpChange(int, std::vector<Ally*>&, int&);
		void enemyHpChange(int, int&);

		void playerPostAttackAnimation();
		void allyPostAttackAnimation(std::vector<Ally*>&);
		void enemyPostAttackAnimation();
		void checkForCompletion(int&);
		
		//Battle state 4
		bool checkAllyDeath(std::vector<Ally*>&);
		bool checkEnemyDeaths();
		void checkEndBattle(std::vector<Ally*>&, int&, int&);
		void currentEnemyDeath();
		void newTurn(std::vector<Ally*>&);
		
		//Drawing
		void setCirclePos();
		void drawAlly(sf::RenderWindow&, std::vecto<Ally*>&);
		void drawEnemies(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);
		void setInitHp(int);

		//Utility
		int getMaxNum(int, int);
};

#endif
