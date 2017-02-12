#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;

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

		//Prohibit movement
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;
	public:
		Player(int, int);
		void setPos(int, int);
		void stepSound();
		void standStill();
		void movePos();
		void spriteAnimation();
		void collisionZones(int, int);
		sf::Vector2f getPosition();
		sf::Sprite getSprite();
};

#endif
