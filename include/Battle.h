#include "Enemy.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles
class Battle
{
	private:
		//For player
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		bool qNotPressed;
		
		//For enemies
		std::vector<Enemy> enemies;
		int numEnemies;
		int currentEnemySelected;

		//Time management
		sf::Clock clock;
		sf::Time tme;
		float currentTime;
	public:
		Battle();

		void setupBattle(sf::String);
		void startBattle();
		void endBattle(int&);

		void changeEnemyFocus();
		bool checkPlayerDeath(Player);
		bool checkEnemyDeaths();
		void enemyAttack(int, Player);
		void drawEnemies(sf::RenderWindow&);

		//Mutators
		void setEnemyHp(int, int);

		//Accessors
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
