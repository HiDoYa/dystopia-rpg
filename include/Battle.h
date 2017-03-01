#include "Enemy.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles class Battle
class Battle
{
	private:
		sf::Texture playerTexture;
		sf::Sprite playerSprite;

		//Player options
		std::vector<sf::CircleShape> playerOptions;
		int numSkills;
		int currentSkill;
		bool playerCanAttack;

		//For damage calculation
		int initHp;

		//Skill Pressed
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		Enemy temp;
		std::vector<Enemy> enemies;
		int numEnemies;
		int currentEnemySelected;
		int nextAttack;

		//Time management
		//TODO currently not used
		sf::Clock clock;
		sf::Time tme;
		float currentTime;
		float lastTime;
	public:
		Battle();

		void setupBattle(sf::String);
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
		void playerAttackAnimation(int&, Player&);
		void enemyAttackAnimation(int&);
		
		//Battle state 2
		void hpCalculate(Player&, UIOverlay&);
		void playerHpDecrease(int, Player&, UIOverlay&);
		void enemyHpDecrease(int);
		void playerPostAttackAnimation(Player&);
		void enemyPostAttackAnimation();
		
		//Battle state 3
		bool checkPlayerDeath(Player&);
		bool checkEnemyDeaths();
		void endBattle(Player&);
		
		//Drawing
		void drawEnemies(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);
		void setInitHp(int);

		//Accessors
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
