#include "SpriteManager.h"
#include "Skill.h"
#include "ClickButton.h"

#ifndef SKILLCARDS_H
#define SKILlCARDS_H

class SkillCards
{
	private:
		SpriteManager icon;
		SpriteManager background;
		//TODO Maybe a star system to indicate weaker/stronger skills?
		SpriteManager skillRating;

		sf::Font font;
		sf::Text name;
		sf::Text description;

		ClickButton nextPage;
		ClickButton prevPage;
		sf::Text pageIndicate;
		int currentpage;
		int maxPage;
	public:
		SkillCards();
		void updatePosition(sf::View);

		void setupCard(Skill);
		void drawAll(sf::RenderWindow&);
};

#endif
