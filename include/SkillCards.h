#include "SpriteManager.h"
#include "Skill.h"
#include "ClickButton.h"

#ifndef SKILLCARDS_H
#define SKILLCARDS_H

class SkillCards
{
	private:
		sf::Texture iconTexture;
		sf::CircleShape icon;
		ClickButton equip;
		sf::RectangleShape cardBackground;
		//TODO Maybe a star system to indicate weaker/stronger skills?
	public:
		SkillCards();
		void setupCard(Skill, int);
		void setPosition(sf::Vector2f, sf::View);
		bool selectSkill(sf::RenderWindow&);

		void drawAll(sf::RenderWindow&);
};

#endif
