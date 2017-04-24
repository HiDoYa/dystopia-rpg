#include <SFML/Audio.hpp>
#include "SpriteManager.h"

#ifndef MAPPLAYER_H
#define MAPPLAYER_H

class MapPlayer: public SpriteManager
{
	private:
		//Time management for sprite animation
		sf::Clock clock;
		sf::Time tme;
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
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;

		//To check for enemy
		bool checkEncounter;
	public:
		MapPlayer();

		//***** Accessor *******
		bool getMoving();

		//***** Etc *******
		void stepSound();
		void standStill();
		void movePos();
		void encounter(int, int&);
		void spriteAnimation();
		bool collisionZones(int, int);
};

#endif
