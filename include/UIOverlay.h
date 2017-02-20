#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef UIOVERLAY_H
#define UIOVERLAY_H

class UIOverlay
{
	private:
		//Mainwrapper
		sf::Texture mainWrapperTexture;
		sf::Sprite mainWrapperSprite;

		//Font Used
		sf::Font font;

		//Bars
		sf::RectangleShape maxHpBar;
		sf::RectangleShape currentHpBar;
		sf::RectangleShape maxManaBar;
		sf::RectangleShape currentManaBar;
		sf::RectangleShape maxExpBar;
		sf::RectangleShape currentExpBar;

		//Exp bar and level indicator
		sf::CircleShape levelNumWrapper;
		sf::Text levelText;

		//Equipped skills
		std::vector<sf::Texture> skillIconTextures;
		std::vector<sf::CircleShape> skillIcons;

		//Currency and other data
		sf::Text currencyText;
	public:
		UIOverlay();

		//Mutators
		void setPosition(sf::View);
		void setCurrency(int);
		void setLevel(int);
		void setHealth(int, int);
		void setMana(int, int);
		void setExp(int, int);
		//TODO Skill display
		//TODO Minimap [low-prio]

		//Etc
		void drawAll(sf::RenderWindow&);
};

#endif
