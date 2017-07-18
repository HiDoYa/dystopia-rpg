#include <SFML/Graphics.hpp>
#include "SkillMenu.h"
#include <iostream>

SkillMenu::SkillMenu()
{
}

void SkillMenu::setupSkill(std::vector<int> unlockedSkills, 
			   std::vector<std::shared_ptr<Skill>> skillList, int allyIndex)
{
	//Finds all unlocked skills for an ally and sets it up
	for(int i = 0; i < unlockedSkills.size(); i++)
	{
		std::vector<int> allyEquip = skillList[unlockedSkills[i]]->getAllyEquip();
		for(int j = 0; j < allyEquip.size(); j++)
		{
			if(allyIndex == allyEquip[j])
			{
				skillCards.push_back(std::shared_ptr<SkillCards>(new SkillCards));
				skillCards[skillCards.size()].setupCard(*skillList[i]);
			}
		}
	}
}

void SkillMenu::setPosition(sf::Vector2f pos, sf::View view)
{
	for(int i = 0; i < skillCards.size(); i++)
	{
		skillCards.setPosition(pos, view);
	}
}

void SkillMenu::drawAll(sf::RenderWindow& win)
{
	for(int i = 0; i < skillCards.size(); i++)
	{
		skillCards[i]->drawAll(win);
	}
}
