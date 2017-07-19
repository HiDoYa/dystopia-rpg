#include <SFML/Graphics.hpp>
#include <iostream>

#include "Textbox.h"
#include "UIOverlay.h"

#include "Npc.h"

Npc::Npc()
{
	name = "default name";

	//Gets texture of sprite
	setTextureRect(0, 0);

	//Initializes speaking bool
	speaking = false;
	colliding = false;
}

void Npc::npcExistCondition(int flagNum, bool flagBool)
{
	npcExistNum = flagNum;
	npcExistCond = flagBool;
}

bool Npc::npcExists(std::vector<bool> stateFlag)
{
	if(stateFlag[npcExistNum] == npcExistCond)
	{
		return true;
	}
	return false;
}

//Gets the converted vector, deals with animation/textbox calls, and deals with multiple textboxes
void Npc::speak(std::vector<bool>& stateFlag, std::vector<int>& allyFound, std::vector<int>& unlockedSkills, Textbox& box, MapPlayer& player, sf::RenderWindow& win)
{
	bool cond = !player.getMoving() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if(colliding)
	{
		for(int i = 0; i < getCondition().size(); i++)
		{
			bool allowText = true;
			for(int j = 0; j < getCondition()[i].size(); j++)
			{
				if(stateFlag[getCondition()[j][i]] != getConditionCheck()[j][i])
				{
					allowText = false;
				}
			}

			if(allowText)
			{
				if(getChoiceFlag()[i])
				{
					switch(box.choiceBoxDisp(name, getText()[i], getChoiceDisp()[i], getChoiceOne()[i], getChoiceTwo()[i], getChoiceOneDisp()[i], getChoiceTwoDisp()[i], cond, speaking, win))
					{
						case 0:
							//Choice box is not completed yet
							break;
						case 1:
							//Change assuming the first choice
							changeStateFlag(stateFlag, i, 1);
							giveToPlayer(allyFound, unlockedSkills, i, 1);
							break;
						case 2:
							//Change assuming the second choice
							changeStateFlag(stateFlag, i, 2);
							giveToPlayer(allyFound, unlockedSkills, i, 2);
							break;
					}
				}
				else if(box.textHandler(name, getText()[i], cond, speaking))
				{
					changeStateFlag(stateFlag, i, 0);
					giveToPlayer(allyFound, unlockedSkills, i, 0);
				}
				break;
			}
		}
	}
}

void Npc::giveToPlayer(std::vector<int>& allyFound, std::vector<int>& unlockedSkills, int textNum, int type)
{
	if(type == 0)
	{
		for(int i = 0; i < getGiveType()[textNum].size(); i++)
		{
			if(getGiveType()[textNum][i] == 0)
			{
				allyFound.push_back(getGiveId()[textNum][i]);
			}
			else if(getGiveType()[textNum][i] == 1)
			{
				unlockedSkills.push_back(getGiveId()[textNum][i]);
			}
		}
	}
	else if(type == 1)
	{
		for(int i = 0; i < getGiveOneType()[textNum].size(); i++)
		{
			if(getGiveOneType()[textNum][i] == 0)
			{
				allyFound.push_back(getGiveOneId()[textNum][i]);
			}
			else if(getGiveType()[textNum][i] == 1)
			{
				unlockedSkills.push_back(getGiveOneId()[textNum][i]);
			}
		}
	}
	else if(type == 2)
	{
		for(int i = 0; i < getGiveTwoType()[textNum].size(); i++)
		{
			if(getGiveTwoType()[textNum][i] == 0)
			{
				allyFound.push_back(getGiveTwoId()[textNum][i]);
			}
			else if(getGiveTwoType()[textNum][i] == 1)
			{
				unlockedSkills.push_back(getGiveTwoId()[textNum][i]);
			}
		}
	}

	ascendSort(allyFound);
	removeDup(allyFound);
	ascendSort(unlockedSkills);
	removeDup(unlockedSkills);
}

//Insertion sort
void Npc::ascendSort(std::vector<int>& toSort)
{
	for(int i = 1; i < toSort.size(); i++)
	{
		int curIndex = i;
		while(curIndex > 0 && toSort[curIndex] < toSort[curIndex - 1])
		{
			int tempSwap = toSort[curIndex];
			toSort[curIndex] = toSort[curIndex - 1];
			toSort[curIndex - 1] = tempSwap;
			curIndex--;
		}
	}
}

void Npc::removeDup(std::vector<int>& toRemove)
{
	int lastNum = toRemove[0];
	for(int i = 1; i < toRemove.size(); i++)
	{
		if(toRemove[i] == lastNum)
		{
			toRemove.erase(toRemove.begin() + i);
			i--;
		}
		lastNum = toRemove[i];
	}
}

//Type is 0 if regular text, 1 if option one (in choice), 2 if option two (in choice)
void Npc::changeStateFlag(std::vector<bool>& stateFlag, int textNum, int type)
{
	int stateNum, iterations;
	bool changeTo;

	switch(type)
	{
		case 0:
			iterations = getChgNum()[textNum].size();
			break;
		case 1:
			iterations = getChgOneNum()[textNum].size();
			break;
		case 2:
			iterations = getChgTwoNum()[textNum].size();
			break;
	}

	for(int chgCounter = 0; chgCounter < iterations; chgCounter++)
	{
		switch(type)
		{
			case 0:
				stateNum = getChgNum()[textNum][chgCounter];
				changeTo = getChgCheck()[textNum][chgCounter];
				break;
			case 1:
				stateNum = getChgOneNum()[textNum][chgCounter];
				changeTo = getChgOneBool()[textNum][chgCounter];
				break;
			case 2:
				stateNum = getChgTwoNum()[textNum][chgCounter];
				changeTo = getChgTwoBool()[textNum][chgCounter];
				break;
		}
		stateFlag[stateNum] = changeTo;
	}
}

void Npc::collision(MapPlayer& player)
{
	colliding = player.collisionZones(getPosition().x / 64, getPosition().y / 64);
}

//********* MUTATORS  *********
void Npc::setName(std::string inp)
{
	name = inp;
}

//********* ACCESSORS *********
bool Npc::getSpeaking()
{
	return speaking;
}

std::string Npc::getName()
{
	return name;
}
