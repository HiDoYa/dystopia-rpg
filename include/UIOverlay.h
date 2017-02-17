#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef UIOVERLAY_H
#define UIOVERLAY_H

class UIOverlay
{
	private:
		sf::Texture mainWrapperTexture;
		sf::Sprite mainWrapperSprite;

		//Health bars
		sf::RectangleShape hpBar;
		sf::RectangleShape damageBar;

		//TODO Energy Bars?

		//Exp bar and level indicator
		sf::Text levelNum;
		sf::CircleShape levelNumWrapper;
		sf::RectangleShape expBar;

		//Equipped skills
		std::vector<sf::Texture> skillIconTextures;
		std::vector<sf::CircleShape> skillIcons;

		//Currency and other data
		sf::Text miscText;

		//TODO Minimap [low-prio]

	public:
		UIOverlay();

		//Mutators
		void setPosition(int, int);
		void setCurrencyText(float);
		void setLevelText(int);
		void setMaxHealth(int);
		void setCurrentHealth(int);
		void setExpBar(int);

		//Accessors
		sf::Vector2f getPosition();
		float getCurrencyText();
		int getLevelText();
		int getMaxHealth();
		int getCurrentHealth();
		int getExpBar();

		void move();
};

#endif
