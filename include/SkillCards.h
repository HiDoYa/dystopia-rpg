#include "SpriteManager.h"
#include "Skill.h"
#include "ClickButton.h"

#ifndef SKILLCARDS_H
#define SKILlCARDS_H

class SkillCards
{
	private:
		sf::CircleShape icon;
		sf::RectangleShape cardBackground;
		//TODO Maybe a star system to indicate weaker/stronger skills?
		SpriteManager skillRating;

		sf::Font font;
		sf::Text name;
		sf::Text description;
	public:
		SkillCards();
		void setupCard(Skill);
		void updatePosition(sf::View);

		void setupCard(Skill);
		void drawAll(sf::RenderWindow&);
};

#endif
