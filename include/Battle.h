#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef BATTLE_H
#define BATTLE_H

class Battle
{
	private:
		//For player
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		int playerHp;

		//Key press
		bool keyQUp;
		bool keyWUp;
		bool keyAUp;
		bool keySUp;
		bool keyDUp;

		//For combos
		sf::Texture comboTexture;
		sf::Sprite comboSprite;
		std::string currentCombo;
		std::vector<std::string> validCombos;

		bool nextAttackBlock;
		bool successCombo;
		float immobilizationTime;
		float lastImmobilizationTime;

		//For enemies
		std::vector<Enemy> enemies;
		int numEnemies;
		int currentEnemySelected;

		//Time management
		sf::Clock clock;
		sf::Time time;
		float currentTime;
	public:
		Battle();
		void setupBattle(int, int, int);
		void startBattle();
		void endBattle(int&);

		void changeEnemyTarget();
		void checkEnemyDeaths();
		void playerAttack();
		void activateAttack();
		void enemyAttack(int);
		void drawEnemies(sf::RenderWindow&);

		//Mutators
		void setPlayerHp(int);
		void setEnemyHp(int, int);

		//Accessors
		int getPlayerHp();
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
