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

		//TODO Mana

		//Exp bar and level indicator
		sf::Text levelText;
		sf::CircleShape levelNumWrapper;
		sf::RectangleShape expBar;

		//Equipped skills
		std::vector<sf::Texture> skillIconTextures;
		std::vector<sf::CircleShape> skillIcons;

		//Currency and other data
		sf::Text currencyText;

		//TODO Minimap [low-prio]

	public:
		UIOverlay();

		//Mutators
		void setPosition(sf::View);
		void setCurrency(float);
		void setLevel(int);
		void setHealth(int, int);
		void setMana(int, int);
		void setExp(int, int);
};

#endif
