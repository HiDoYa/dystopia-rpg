#include <SFML/Graphics.hpp>
#include <iostream>

#include "Item.h"

Item::Item()
{
	strIncrease = defIncrease = agiIncrease = hpIncrease = manaIncrease = 0;
}

//Mutators
void Item::setName(std::string inp)
{
	name = inp;
}

void Item::setDescription(std::string inp)
{
	description = inp;
}

void Item::setSellPrice(int inp)
{
	sellPrice = inp;
}

void Item::setImage(std::string inp)
{
	image.setTextureSprite(inp);
}

void Item::setItemType(int inp)
{
	itemType = inp;
}

void Item::setStrIncrease(int inp)
{
	strIncrease = inp;
}

void Item::setDefIncrease(int inp)
{
	defIncrease = inp;
}

void Item::setAgiIncrease(int inp)
{
	agiIncrease = inp;
}

void Item::setHpIncrease(int inp)
{
	hpIncrease = inp;
}

void Item::setManaIncrease(int inp)
{
	manaIncrease = inp;
}

//Acessors

std::string Item::getName()
{
	return name;
}

std::string Item::getDescription()
{
	return description;
}

int Item::getSellPrice()
{
	return sellPrice;
}

int Item::getItemType()
{
	return itemType;
}

int Item::getStrIncrease()
{
	return strIncrease;
}

int Item::getDefIncrease()
{
	return defIncrease;
}

int Item::getAgiIncrease()
{
	return agiIncrease;
}

int Item::getHpIncrease()
{
	return hpIncrease;
}

int Item::getManaIncrease()
{
	return manaIncrease;
}
