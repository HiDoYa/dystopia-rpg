#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "UIOverlay.h"
#include "SpriteManage.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public SpriteManage
{
	private:
		//Time management for box open/close
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

		//To check for enemy
		bool checkEncounter;
	public:
		Player(int, int);

		//***** Mutators *******
		void setCurrentHp(int, UIOverlay);
		void setMaxHp(int, UIOverlay);
		void setCurrentMana(int, UIOverlay);
		void setMaxMana(int, UIOverlay);
		void setLevel(int, UIOverlay);
		void setExp(int, UIOverlay);
		void setCurrency(float, UIOverlay);

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
		void encounter(int, int&);
		void spriteAnimation();
		bool collisionZones(int, int);
};

#endif
