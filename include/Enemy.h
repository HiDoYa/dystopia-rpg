#include "SpriteManage.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public SpriteManage 
{
	private:
		sf::Font font;
		sf::Text name;
		int level;
		int currentHp;
		int maxHp;
		int initHp;
		int currentMana;
		int maxMana;

		int strength;
		int defense;
		int agility;

		int chance;
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

		void setStrength(int);
		void setDefense(int);
		void setAgility(int);

		void setAlive(bool);
		void setCanAtk(bool);
		void setChance(int);

		//Accessors
		sf::String getName();
		int getLevel();
		int getMaxHp();
		int getCurrentHp();
		int getInitHp();
		int getMaxMana();
		int getCurrentMana();

		int getStrength();
		int getDefense();
		int getAgility();

		bool getAlive();
		bool getCanAtk();
		int getChance();

		//Draw bars
		void updatePosition();
		void drawAll(sf::RenderWindow&);
};

#endif
