#include <iostream>
#include <SFML/Graphics.hpp>

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
		double currentTime;
		double lastTime;
		float attackInterval;
		bool readyToAttack;
	public:
		Enemy(int, int, sf::String);
		void setPosition(int, int);
		void setScale(int);
		void setHealth(int);
		void setAttackDmg(int);
		void setAttackInterval(float);
		sf::Sprite getSprite();
		void checkAttackInterval(float);
		void attack();
		bool mouseOver(sf::Sprite);
		bool getColliding(sf::Sprite);
		bool getColliding(sf::RectangleShape);
		int getHealth();
		int getAttackDmg();
}

#endif
