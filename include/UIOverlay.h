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
		//

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
		void setCurrency(float);
		void setLevel(int);
		void setMaxHealth(int);
		void setCurrentHealth(int);
		void setExp(int);

		//Accessors
		sf::Vector2f getPosition();
		float getCurrency();
		int getLevel();
		int getMaxHealth();
		int getCurrentHealth();
		int getExp();

		void move();
};

#endif
