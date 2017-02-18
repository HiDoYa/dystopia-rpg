#include "UIOverlay.h"

UIOverlay::UIOverlay()
{
}

//********** MUTATORS

void UIOverlay::setPosition(int x, int y)
{
}

void UIOverlay::setCurrency(float cur)
{
}

void UIOverlay::setLevel(int lvl)
{
	level = lvl;
	//set levelText to "Gold: " + level;
}

void UIOverlay::setMaxHealth(int max)
{
}

void UIOverlay::setCurrentHealth(int cur)
{
}

void UIOverlay::setExp(int curExP)
{
}

//********** ACCESSORS 

sf::Vector2f UIOverlay::getPosition()
{
	return mainWrapperSprite.getPosition();
}

float UIOverlay::getCurrency()
{
}

int UIOverlay::getLevel()
{
}

int UIOverlay::getMaxHealth()
{
}

int UIOverlay::getCurrentHelath()
{
}

int UIOverlay::getExp()
{
}

//********** ACCESSORS 

void UIOverlay::move()
{
}
