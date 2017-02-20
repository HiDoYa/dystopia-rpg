#include <SFML/Graphics.hpp>
#include "SpriteManage.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public SpriteManage 
{
	private:
		sf::Text name;
		int level;
		int currentHp;
		int maxHp;
		int currentMana;
		int maxMana;
		int agility;
		int atk;
		bool alive;

		//Bars
		sf::RectangleShape maxHpBar;
		sf::RectangleShape currentHpBar;
		sf::RectangleShape maxManaBar;
		sf::RectangleShape currentManaBar;
		sf::RectangleShape timeReq;
		sf::RectangleShape timeFilled;
	public:
		Enemy(int, int);

		//Mutators
		void setName(sf::String);
		void setLevel(int);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);
		void setAgility(int);
		void setAtk(int);
		void setAlive(bool);

		//Accessors
		sf::String getName();
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();
		int getAgility();
		int getAtk();
		bool getAlive();

		//Draw bars
		void drawHealthBar(sf::RenderWindow&);
		void drawTimeBar(sf::RenderWindow&);
		void drawAll(sf::RenderWindow&);
};

#endif
