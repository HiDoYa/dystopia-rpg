#include <iostream>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy 
{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		int health;
		int attackDmg;
	public:
		Enemy();
		void setPosition(int, int);
		void setScale(int);
		void setHealth(int);
		void setAttackDmg(int);
		sf::Sprite getSprite();
		int getHealth();
		int getAttackDmg();
}

#endif
