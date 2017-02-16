#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef BATTLE_H
#define BATTLE_H

class Battle
{
	public:
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
		//sf::Texture enemyTexture;
		//std::vector<sf::Sprite> enemySprite;
		//std::vector<int> enemyHp;
		//std::vector<int> enemyType;
		//std::vector<int> enemyLvls;
		//std::vector<int> enemyAtk;
		//std::vector<int> enemyAttackDelay;
		//std::vector<int> enemiesAliveIndex;
		std::vector<Enemy> enemies;
		int numEnemies;
		int currentEnemySelected;

		//Time management
		sf::Clock clock;
		sf::Time time;
		float currentTime;
	private:
		Battle();
		void setupBattle(int, int, int);
		void startBattle();
		void endBattle(int&);
		void changeEnemyTarget();
		void checkEnemyDeaths();
		void playerAttack();
		void activateAttack();
		void enemyAttack();
		void setPlayerHp(int);
		void setEnemyHp(int, int);
		int getPlayerHp();
		int getEnemyHp(int);
		int getNumEnemies();
};

#endif
