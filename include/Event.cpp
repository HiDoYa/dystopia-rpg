#include <iostream>

#include "Event.h"

Event::Event()
{
}

void Event::addItem(int itemId)
{
}

void Event::removeItem(int itemId)
{
}

void Event::addAlly(int allyInd)
{
}

void Event::addSkill(int skillId, int allyNum)
{
}

void Event::cutscene(int dialogueNum)
{
	//TODO Play dialogue
	//TODO cant also set the background (e.g. place characters in certain maps, etc)
	
	std::string file = "data/dialogue/script" + std::string(dialogueNum);
	std::string currentName;

	file >> currentName;
	currentName.pop_back();

	//TODO get whole text
}

void Event::panCamera(int posX, int posY)
{
}

void Event::teleport(int zone, int map)
{
}
