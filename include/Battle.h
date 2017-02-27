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
		bool qNotPressed;

		//Player options
		std::vector<sf::CircleShape> playerOptions;
		int numSkills;

		
		//For enemies
		std::vector<Enemy> enemies;
		int numEnemies;
		int currentEnemySelected;

		//Time management
		sf::Clock clock;
		sf::Time tme;
		float currentTime;
		float lastTime;
	public:
		Battle();

		void setupBattle(sf::String);
		void startBattle();
		void tickBattle();
		void endBattle(int&);

		void changeEnemyFocus();
		bool checkPlayerDeath(Player);
		bool checkEnemyDeaths();
		void enemyAttack(int, Player);
		void drawEnemies(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);

		//Mutators
		void setEnemyHp(int, int);

		//Accessors
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
