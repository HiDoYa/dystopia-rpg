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
		bool canMoveUp;   //0
		bool canMoveDown; //1
		bool canMoveLeft; //2
		bool canMoveRight;//3

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
		void keyPressAction(int, bool);
		void encounter(int, int&);
		void spriteAnimation();
		bool collisionZones(int, int);
};

#endif
