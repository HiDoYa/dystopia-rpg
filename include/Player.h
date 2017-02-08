#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::RectangleShape collisionRectangle;
		sf::Vector2f collisionSize;

		//Time management for box open/close
		sf::Clock clk;
		sf::Time tme;
		double lastTime;
		double currentTime;
		int spriteAnimationDelay;
		int stepSoundDelay;
		int dashMoveDelay;

		//Music and time management for music
		sf::Music step1;
		sf::Music step2;
		int curStep;
		double lastTimeMu;
		double currentTimeMu;

		//Movement
		int speedRegular;
		int speedSlow;
		int xSpeed;
		int ySpeed;
		int lastDirection;
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;
		int texturePosX;
		int texturePosY;
	public:
		Player(int, int);
		void setScale(float);
		void setPos(int, int);
		void stepSound();
		void setCollisionBools(sf::Sprite);
		void setCollisionBools(sf::RectangleShape);
		void standStill();
		void movePos(float&, float&);
		void spriteAnimation(int);
		void dashMove(int);
		sf::Vector2f getPos();
		sf::Texture getTexture();
		sf::Sprite getSprite();
		sf::RectangleShape getCollisionRectangle();
};

#endif
