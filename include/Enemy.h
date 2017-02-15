#include <SFML/Graphics.hpp>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
	private:
		int hp;
		int level;
		int atk;
		int delay;
		bool alive;
	public:
		Enemy();

		void setHp(int);
		void setLevel(int);
		void setAtk(int);
		void setDelay(int);
		void setAlive(int);

		int getHp();
		int getLevel();
		int getAtk();
		int getDelay();
		bool getAlive();
}

#endif
