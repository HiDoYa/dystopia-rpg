#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteManage.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public SpriteManage
{
	private:
		//Time management for box open/close
		sf::Clock clock;
		sf::Time time;
		float lastTimeAnim;
		float lastTimeMu;
		float currentTime;
		int spriteAnimationDelay;
		int stepSoundDelay;

		//Music and time management for music
		sf::Music step1;
		sf::Music step2;
		int curStep;

		//Movement
		int speed;
		int xSpeed;
		int ySpeed;
		int lastDirection;
		int texturePosX;
		int texturePosY;
		bool moving;
		int movingNum;

		//Attributes
		int hp;

		//Prohibit movement
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;
	public:
		Player(int, int);

		//***** Mutators *******
		void setHp(int);

		//***** Accessor *******
		int getHp();

		//***** Etc *******
		void stepSound();
		void standStill();
		void movePos();
		void spriteAnimation();
		bool collisionZones(int, int);
};

#endif
