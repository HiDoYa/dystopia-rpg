#include <SFML/Graphics.hpp>
#include "SpriteManage.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public SpriteManage 
{
	private:
		int id;
		int currentHp;
		int maxHp;
		int level;
		int atk;
		int delay;
		bool alive;

		//Health bars
		sf::RectangleShape health;
		sf::RectangleShape damage;
	public:
		Enemy(int, int, int);

		//Mutators
		void setId(int);
		void setCurrentHp(int);
		void setMaxHp(int);
		void setLevel(int);
		void setAtk(int);
		void setDelay(int);
		void setAlive(bool);

		//Accessors
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getAtk();
		int getDelay();
		bool getAlive();
};

#endif
