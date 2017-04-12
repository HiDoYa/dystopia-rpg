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
		std::vector<Skill> skill;

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

		//Attributes
		int level;
		int maxHp;
		int currentHp;
		int maxMana;
		int currentMana;

		int strength;
		int defense;
		int agility;

		//Etc
		int exp;
		int currency;
		int battlePos;
	public:
		Player();

		//***** Mutators *******
		void setLevel(int, UIOverlay&);
		void setCurrentHp(int, UIOverlay&);
		void setMaxHp(int, UIOverlay&);
		void setCurrentMana(int, UIOverlay&);
		void setMaxMana(int, UIOverlay&);

		void setStrength(int);
		void setDefense(int);
		void setAgility(int);

		void setExp(int, UIOverlay&);
		void setCurrency(int, UIOverlay&);
		void setBattlePos(int);

		//***** Accessor *******
		int getLevel();
		int getCurrentHp();
		int getMaxHp();
		int getCurrentMana();
		int getMaxMana();

		int getStrength();
		int getDefense();
		int getAgility();

		int getExp();
		int getCurrency();
		int getBattlePos();
		std::vector<Skill> getSkill();

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
