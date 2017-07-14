#include <SFML/Graphics.hpp>
#include "SkillCards.h"
#include <iostream>

SkillCards::SkillCards()
{
	currentPage = maxPage = 1;
	font.loadFromFile("font/Ubuntu.ttf");
	name.setFont(font);
	description.setFont(font);
	pageIndicate.setFont(font);

	nextPage.setType(1);
	prevPage.setType(1);
}

void SkillCards::updatePosition(sf::View view)
{
}
