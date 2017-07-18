#include "SkillCards.h"

#ifndef SKILLMENU_H
#define SKILLMENU_H
class SkillMenu
{
	private:
		std::vector<std::shared_ptr<SkillCards>> skillCards;
	public:
		SkillMenu();
		void setupSkill(std::vector<int>, std::vector<std::shared_ptr<Skill>>, int);
		void setPosition(sf::Vector2f, sf::View);
		void drawAll(sf::RenderWindow&);
};
#endif
