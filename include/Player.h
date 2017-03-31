#include <SFML/Audio.hpp>
#include "SpriteManage.h"

#include "Skill.h"

class Map;
class UIOverlay;

#ifndef PLAYER_H
#define PLAYER_H

class Player: public SpriteManage
{
	private:
		//Skill
		std::vector<Skill> skills;

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
		int level;
		int maxHp;
		int currentHp;
		int maxMana;
		int currentMana;
		int agility;
		int atk;
		int exp;
		int currency;

		int battlePos;

		//Prohibit movement
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;

		//To check for enemy
		bool checkEncounter;
	public:
		Player();

		//***** Mutators *******
		void setLevel(int, UIOverlay&);
		void setCurrentHp(int, UIOverlay&);
		void setMaxHp(int, UIOverlay&);
		void setCurrentMana(int, UIOverlay&);
		void setMaxMana(int, UIOverlay&);
		void setAgility(int);
		void setAtk(int);
		void setExp(int, UIOverlay&);
		void setCurrency(int, UIOverlay&);
		void setBattlePos(int);

		//***** Accessor *******
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();
		int getAgility();
		int getAtk();
		int getExp();
		int getCurrency();

		int getBattlePos();
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
