#include <SFML/Graphics.hpp>
#include "CharacterCards.h"
#include <iostream>

CharacterCards::CharacterCards()
{
	font.loadFromFile("font/Ubuntu.ttf");
	skillToChange = -1;
	itemToChange = -1;
	displaySkills = false;
	displayWeapons = false;
	displayArmor = false;
	displayOs = false;
	existInParty = false;
	allyIndex = -1;

	background.setTextureSprite("images/ui/characterCard.png");

	setupText(name, font, 27);
	setupText(desc, font, 20);
	setupText(str, font, 20);
	setupText(def, font, 20);
	setupText(agi, font, 20);
	setupText(skillItemText, font, 20);
	skillItemText.setString("Skills & Items");

	hp.setLabelPos(0);
	hp.setLabelSize(13);
	hp.setMaxSize(sf::Vector2f(350, 50));
	hp.getCurrentRect()->setFillColor(sf::Color::Red);
	hp.getLabel()->setColor(sf::Color::Black);

	mana.setLabelPos(0);
	mana.setLabelSize(13);
	mana.setMaxSize(sf::Vector2f(350, 50));
	mana.getCurrentRect()->setFillColor(sf::Color::Yellow);
	mana.getLabel()->setColor(sf::Color::Black);

	partyButton.getRect()->setSize(sf::Vector2f(300, 80));
	partyButton.getText()->setCharacterSize(20);
	partyButton.getText()->setColor(sf::Color::Black);

	for(int i = 0; i < 3; i++)
	{
		skillButton.push_back(std::shared_ptr<ClickButton>(new ClickButton));
		skillButton[i]->setType(1);
		skillButton[i]->setHoverText(true);
		skillButton[i]->getHoverText()->setCharacterSize(15);
		skillButton[i]->getHoverText()->setColor(sf::Color::White);
		skillButton[i]->getCirc()->setRadius(50);

		itemButton.push_back(std::shared_ptr<ClickButton>(new ClickButton));
		itemButton[i]->setType(1);
		itemButton[i]->setHoverText(true);
		itemButton[i]->getHoverText()->setCharacterSize(15);
		itemButton[i]->getHoverText()->setColor(sf::Color::White);
		itemButton[i]->getCirc()->setRadius(50);
	}
}


void CharacterCards::setDisplay(bool inp)
{
	displaySkills = inp;
	displayWeapons = inp;
	displayArmor = inp;
	displayOs = inp;
}
void CharacterCards::setupText(sf::Text& txt, sf::Font& font, int charSize)
{
	txt.setCharacterSize(charSize);
	txt.setFont(font);
	txt.setColor(sf::Color::Black);
}

void CharacterCards::updatePosition(std::vector<std::shared_ptr<Character>> ally, sf::View view)
{
	int viewX = view.getCenter().x - (view.getSize().x / 2);
	int viewY = view.getCenter().y - (view.getSize().y / 2);

	skillDispBackground.setPosition(viewX, viewY);
	background.setPosition(viewX, viewY);

	hp.setPosition(sf::Vector2f(180 + viewX, 450 + viewY));
	mana.setPosition(sf::Vector2f(180 + viewX, 580 + viewY));

	name.setPosition(180 + viewX, 150 + viewY);
	desc.setPosition(180 + viewX, 150 + viewY);
	str.setPosition(180 + viewX, 220 + viewY);
	def.setPosition(180 + viewX, 280 + viewY);
	agi.setPosition(180 + viewX, 340 + viewY);

	if(allyIndex != -1)
	{
		ally[allyIndex]->setPosition(470 + viewX, 220 + viewY);
		ally[allyIndex]->setScale(2.5, 2.5);
	}

	skillItemText.setPosition(720 + viewX, 230 + viewY);
	skillButton[0]->updatePositionMap(690, 330, view);
	skillButton[1]->updatePositionMap(790, 260, view);
	skillButton[2]->updatePositionMap(890, 330, view);

	itemButton[0]->updatePositionMap(690, 450, view);
	itemButton[1]->updatePositionMap(790, 530, view);
	itemButton[2]->updatePositionMap(890, 450, view);

	itemButton[0]->getCirc()->setTextureRect(sf::IntRect(0, 0, 64, 64));
	itemButton[1]->getCirc()->setTextureRect(sf::IntRect(64, 0, 64, 64));
	itemButton[2]->getCirc()->setTextureRect(sf::IntRect(128, 0, 64, 64));

	partyButton.updatePositionMap(700, 100, view);

	for(int i = 0; i < skillCards.size(); i++)
	{
		skillCards[i]->setPosition(sf::Vector2f((i % 3) * 300 + 150, (i / 3) * 200 + 100), view);
	}

	for(int i = 0; i < 3; i++)
	{
		skillButton[i]->centerHoverHorizontal();
		itemButton[i]->centerHoverHorizontal();
	}
}

void CharacterCards::setupCard(Character chr, int indexInAlly, std::vector<int> allyInParty, 
			    std::vector<std::shared_ptr<Skill>> skillList, 
			    std::vector<int> unlockedSkills,
			    std::vector<std::shared_ptr<Item>> itemList,
			    std::vector<int> itemHeld)
{
	name.setString(chr.getName());

	//TODO Description for each character (fileReader)

	str.setString("Technology:  " + std::to_string(chr.getStrength()));
	def.setString("Durability:  " + std::to_string(chr.getDefense()));
	agi.setString("Agility:  " + std::to_string(chr.getAgility()));
	
	hp.setStats(chr.getCurrentHp(), chr.getMaxHp(), "Health");
	mana.setStats(chr.getCurrentMana(), chr.getMaxMana(), "Energy");

	//Checks whether the ally is already in the party
	existInParty = false;
	allyIndex = indexInAlly;

	for(int i = 0; i < allyInParty.size(); i++)
	{
		if(allyInParty[i] == indexInAlly)
		{
			existInParty = true;
		}
	}

	skillCards.clear();

	for(int i = 0; i < unlockedSkills.size(); i++)
	{
		int currentNum = unlockedSkills[i];
		std::vector<int> equippableAllies = skillList[currentNum]->getAllyEquip();
		for(int j = 0; j < equippableAllies.size(); j++)
		{
			if(equippableAllies[j] == allyIndex)
			{
				skillCards.push_back(std::shared_ptr<SkillCards>(new SkillCards));
				skillCards[skillCards.size() - 1]->setupCard(*skillList[currentNum], currentNum);
			}
		}
	}

	weaponCards.clear();
	armorCards.clear();
	osCards.clear();

	for(int i = 0; i < itemHeld.size(); i++)
	{
		switch(itemList[itemHeld[i]]->getItemType())
		{
			case 0:
				weaponCards.push_back(std::shared_ptr<SkillCards>(new SkillCards));
				weaponCards[weaponCards.size() - 1]->setupCard(*itemList[itemHeld[i]], itemHeld[i]);
				break;
			case 1:
				armorCards.push_back(std::shared_ptr<SkillCards>(new SkillCards));
				armorCards[armorCards.size() - 1]->setupCard(*itemList[itemHeld[i]], itemHeld[i]);
				break;
			case 2:
				osCards.push_back(std::shared_ptr<SkillCards>(new SkillCards));
				osCards[osCards.size() - 1]->setupCard(*itemList[itemHeld[i]], itemHeld[i]);
				break;
		}
	}

	for(int i = 0; i < 3; i++)
	{
		switch(skillList[chr.getSkillNum()[i]]->getPrimaryType())
		{
			case 0:
				skillButton[i]->getCirc()->setTextureRect(sf::IntRect(0, 0, 64, 64));
				break;
			case 1:
				skillButton[i]->getCirc()->setTextureRect(sf::IntRect(64, 0, 64, 64));
				break;
			case 2:
				skillButton[i]->getCirc()->setTextureRect(sf::IntRect(128, 0, 64, 64));
				break;
			case 3:
				skillButton[i]->getCirc()->setTextureRect(sf::IntRect(192, 0, 64, 64));
				break;
		}
		skillButton[i]->getHoverText()->setString(skillList[chr.getSkillNum()[i]]->getName());
	}

	if(allyIndex == 0)
	{
		partyButton.getText()->setString("Cannot Remove");
	}
	else if(existInParty)
	{
		partyButton.getText()->setString("Remove from Party");
	}
	else if(allyInParty.size() == 3)
	{
		partyButton.getText()->setString("Party is full.");
	}
	else if(!existInParty)
	{
		partyButton.getText()->setString("Add to Party");
	}
}

void CharacterCards::checkForButton(std::vector<int>& allyInParty, 
		std::vector<std::shared_ptr<Character>>& ally, int& currentState,
		bool& mapMenuLoaded, sf::RenderWindow& win)
{
	//TODO BattlePos set (make sure they are unique)
	//Party add or remove
	bool pressed = partyButton.mouseClickedInButton(sf::Color::Red, sf::Color::White, win);
	if(pressed && allyInParty.size() < 3 && allyIndex != 0)
	{
		if(existInParty)
		{
			allyInParty.erase(std::remove(allyInParty.begin(), allyInParty.end(), allyIndex), allyInParty.end());
		}
		else
		{
			//Makes sure that allies have their own unique battle position
			std::vector<int> possiblePos = {0, 1, 2, 3, 4, 5};
			for(int i = 0; i < allyInParty.size(); i++)
			{
				possiblePos.erase(std::remove(possiblePos.begin(), possiblePos.end(), ally[i]->getBattlePos()), possiblePos.end());
			}

			allyInParty.push_back(allyIndex);
			ally[allyIndex]->setBattlePos(rand() % possiblePos.size());
		}
		//Goes back to the map
		currentState = 1;
		mapMenuLoaded = false;
	}

	//Skill select

	for(int i = 0; i < skillButton.size(); i++)
	{
		if(skillButton[i]->mouseClickedInButton("images/ally/skillIcons.png", "images/ally/skillIconsSelected.png", win))
		{
			displaySkills = true;
			skillToChange = i;
		}
	}

	//Item select
	for(int i = 0; i < itemButton.size(); i++)
	{
		if(itemButton[i]->mouseClickedInButton("images/ally/itemIcons.png", "images/ally/itemIconsSelected.png", win))
		{
			itemToChange = i;
			switch(i)
			{
				case 0:
					//TODO
					//displayWeapons = true;
					break;
				case 1:
					//displayArmor = true;
					break;
				case 2:
					//displayOs = true;
					break;
			}
		}
	}

	//Skill card select
	for(int i = 0; i < skillCards.size(); i++)
	{
		if(skillCards[i]->selectSkill(win))
		{
			std::vector<int> skillNum = ally[allyIndex]->getSkillNum();

			bool skillExists = false;

			for(int j = 0; j < 3; j++)
			{
				if(skillCards[i]->getId() == skillNum[j])
				{
					skillExists = true;
				}
			}

			if(!skillExists)
			{
				skillNum[skillToChange] = skillCards[i]->getId();
				ally[allyIndex]->setSkillNum(skillNum);
				displaySkills = false;
			}
			else
			{
				//TODO Display warning?
			}
		}
	}
}

void CharacterCards::drawAll(std::vector<std::shared_ptr<Character>> ally, sf::RenderWindow& win)
{
	if(!displaySkills && !displayWeapons && !displayArmor && !displayOs)
	{
		background.drawSprite(win);

		hp.drawAll(win);
		mana.drawAll(win);
		image.drawSprite(win);

		win.draw(name);
		win.draw(desc);

		win.draw(str);
		win.draw(def);
		win.draw(agi);

		ally[allyIndex]->drawSprite(win);

		partyButton.drawAll(win);

		for(int i = 0; i < skillButton.size(); i++)
		{
			skillButton[i]->drawAll(win);
			itemButton[i]->drawAll(win);
		}

		win.draw(skillItemText);
	}
	else if(displaySkills)
	{
		skillDispBackground.drawSprite(win);
		for(int i = 0; i < skillCards.size(); i++)
		{
			skillCards[i]->drawAll(win);
		}
	}
	else if(displayWeapons)
	{
		skillDispBackground.drawSprite(win);
		for(int i = 0; i < weaponCards.size(); i++)
		{
			weaponCards[i]->drawAll(win);
		}
	}
	else if(displayArmor)
	{
		skillDispBackground.drawSprite(win);
		for(int i = 0; i < armorCards.size(); i++)
		{
			armorCards[i]->drawAll(win);
		}
	}
	else if(displayOs)
	{
		skillDispBackground.drawSprite(win);
		for(int i = 0; i < osCards.size(); i++)
		{
			osCards[i]->drawAll(win);
		}
	}
}
