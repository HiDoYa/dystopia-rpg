#include <SFML/Graphics.hpp>
#include "SpriteManage.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public SpriteManage 
{
	private:
		int id;
		int hp;
		int level;
		int atk;
		int delay;
		bool alive;
	public:
		Enemy(int, int, int);

		//Mutators
		void setId(int);
		void setHp(int);
		void setLevel(int);
		void setAtk(int);
		void setDelay(int);
		void setAlive(bool);

		//Accessors
		int getLevel();
		int getHp();
		int getAtk();
		int getDelay();
		bool getAlive();
};

#endif
