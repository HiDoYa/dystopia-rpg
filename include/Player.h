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
		sf::Music step3;
		int curStep;
		double lastTimeMu;
		double currentTimeMu;

		//Movement
		bool canMoveUp;
		bool canMoveDown;
		bool canMoveRight;
		bool canMoveLeft;
		int texturePosX;
		int texturePosY;
	public:
		Player(int, int);
		void setTexture(sf::String);
		void setScale(float);
		void setPos(int, int);
		void stepSound();
		void movePos(int, float&, float&);
		void spriteAnimation(int);
		void setCollisionBools(sf::Sprite, int);
		void dashMove(int);
		sf::Vector2f getPos();
		void mouseAndCharAngle(sf::Vector2i);
		void rotatePos(int);
		sf::Texture getTexture();
		sf::Sprite getSprite();
		sf::RectangleShape getCollisionRectangle();
};

#endif
