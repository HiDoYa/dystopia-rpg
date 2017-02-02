#include <iostream>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy 
{
	private:
		//Top and bottom of sprite
		sf::Sprite sprite-fore;
		sf::Sprite sprite-mid;

		sf::Texture texture;
		int health;
		int attackDmg;
		
		//Time Management
		sf::Clock clk;
		sf::Time tme;
		int attackInterval;
	public:
		Enemy();
		void setPosition(int, int);
		void setScale(int);
		void setHealth(int);
		void setAttackDmg(int);
		sf::Sprite getSprite();
		bool mouseOver(sf::Sprite);
		bool getColliding(sf::Sprite);
		bool getColliding(sf::RectangleShape);
		int getHealth();
		int getAttackDmg();
}

#endif
