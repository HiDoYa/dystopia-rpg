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

		//Time management for box open/close
		sf::Clock clk;
		sf::Time tme;
		double lastTime;
		double currentTime;

		//Music and time management for music
		sf::Music step1;
		sf::Music step2;
		int curStep;
		double lastTimeMu;
		double currentTimeMu;

		//Movement
		//Regular/slow stores actual speed while primary/secondary is for changing speed for actual implementation
		int speedRegular;
		int speedSlow;
		int primarySpeed;
		int secondarySpeed;
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
		void standStill();
		void movePos(float&, float&);
		void spriteAnimation(int);
		void setCollisionBools(sf::Sprite, int);
		void dashMove(int);
		sf::Vector2f getPos();
		sf::Texture getTexture();
		sf::Sprite getSprite();
		sf::RectangleShape getCollisionRectangle();
};

#endif
