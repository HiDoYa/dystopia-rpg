#include "SpriteManager.h"
#include "Skill.h"
#include "Item.h"
#include "ClickButton.h"

#ifndef SKILLCARDS_H
#define SKILLCARDS_H

//IS USED FOR ITEMS AS WELL
class SkillCards
{
	private:
		sf::Texture iconTexture;
		sf::CircleShape icon;
		int skillId;
		ClickButton equip;
		sf::RectangleShape cardBackground;
		//TODO Maybe a star system to indicate weaker/stronger skills?
	public:
		SkillCards();
		void setupCard(Skill, int);
		void setupCard(Item, int);
		void setPosition(sf::Vector2f, sf::View);
		int getSkillId();
		bool selectSkill(sf::RenderWindow&);

		void drawAll(sf::RenderWindow&);
};

#endif
