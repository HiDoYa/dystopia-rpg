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
		int initHp;
		int currentMana;
		int maxMana;
		int agility;
		int atk;
		bool alive;
		bool canAtk;

		int length;

		//Bars
		sf::RectangleShape maxHpBar;
		sf::RectangleShape currentHpBar;
		sf::RectangleShape maxManaBar;
		sf::RectangleShape currentManaBar;
	public:
		Enemy();

		//Mutators
		void setName(sf::String);
		void setLevel(int);
		void setMaxHp(int);
		void setCurrentHp(int);
		void setInitHp(int);
		void setMaxMana(int);
		void setCurrentMana(int);
		void setAgility(int);
		void setAtk(int);
		void setAlive(bool);
		void setCanAtk(bool);

		//Accessors
		sf::String getName();
		int getLevel();
		int getMaxHp();
		int getCurrentHp();
		int getInitHp();
		int getMaxMana();
		int getCurrentMana();
		int getAgility();
		int getAtk();
		bool getAlive();
		bool getCanAtk();

		//Draw bars
		void updatePosition();
		void drawAll(sf::RenderWindow&);
};

#endif
