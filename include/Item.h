#include "SpriteManager.h"

#ifndef ITEM_H
#define ITEM_H

class Item
{
	private:
		//Types of items: Equipment, healing (hp/mp), stat buffs, quest items (key item), useless items to sell
		//Types of equipment: Weapon, armor, processing unit
		std::string name;
		std::string description;
		int sellPrice;
		
		SpriteManager image;

		//0 is weapon, 1 is armor, 2 is processing unit, 3 s consumable, 4 is quest item
		int itemType;

		int strIncrease;
		int defIncrease;
		int agiIncrease;
		int hpIncrease;
		int manaIncrease;

	public:
		Item();

		//Mutators
		void setName(std::string);
		void setDescription(std::string);
		void setSellPrice(int);
		void setItemType(int);
		void setEquipmentType(int);
		void setStrIncrease(int);
		void setDefIncrease(int);
		void setAgiIncrease(int);
		void setHpIncrease(int);
		void setManaIncrease(int);

		//Accessors
		std::string getName();
		std::string getDescription();
		int getSellPrice();
		int getItemType();
		int getEquipmentType();
		int getStrIncrease();
		int getDefIncrease();
		int getAgiIncrease();
		int getHpIncrease();
		int getManaIncrease();
};

#endif
