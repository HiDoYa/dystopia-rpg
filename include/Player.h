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
		int currentHp;
		int maxHp;
		int currentMana;
		int maxMana;

		int level;
		int exp;

		float currency;

		//Prohibit movement
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;
	public:
		Player(int, int);

		//***** Mutators *******
		void setCurrentHp(int);
		void setMaxHp(int);
		void setCurrentMana(int);
		void setMaxMana(int);
		void setLevel(int);
		void setExp(int);
		void setCurrency(float);

		//***** Accessor *******
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();
		int getLevel();
		int getExp();
		float getCurrency();

		//***** Etc *******
		void stepSound();
		void standStill();
		void movePos();
		void spriteAnimation();
		bool collisionZones(int, int);
};

#endif
