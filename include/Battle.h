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

		//Battle state 1 (find enemies that should attack and go to 2 OR go to 0)
		void findFastestChar(Player&);
		void attackManager(int&, Player&);

		//Battle state 1.5 (animate attack, animate hp going down)
		void playerAttackAnimation(int&, Player&);
		void enemyAttackAnimation(int&);
		
		//Battle state 2 (ending animation, hp calculations)
		
		//Battle state 3 (check for game over. go back to 0 if not game over)
		
		bool checkPlayerDeath(Player);
		bool checkEnemyDeaths();
		void enemyAttack(int, Player);
		void drawEnemies(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);

		//Accessors
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
