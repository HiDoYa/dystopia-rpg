#include <iostream>
#include <fstream>

#include "Character.h"
#include "Skill.h"

#include "FileReader.h"

FileReader::FileReader()
{
}

//Game loading
void FileReader::loadAlly(std::vector<Character*>& ally)
{
	std::ifstream allyFile;
	allyFile.open("data/allyList");
	std::string inp;
	int allyCounter = -1;

	allyFile >> inp;

	do
	{
		if(inp == "Ally")
		{
			ally.push_back(new Character);
			allyCounter++;
			allyFile >> inp;
		}
		if(inp == "Name")
		{
			ally[allyCounter]->setName(getWholeText(allyFile));
		}
		if(inp == "Level")
		{
			allyFile >> inp;
			ally[allyCounter]->setLevel(atoi(inp.c_str()));
		}
		if(inp == "Hp")
		{
			allyFile >> inp;
			ally[allyCounter]->setCurrentHp(atoi(inp.c_str()));
			ally[allyCounter]->setHpFinal(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setMaxHp(atoi(inp.c_str()));
		}
		if(inp == "Mana")
		{
			allyFile >> inp;
			ally[allyCounter]->setCurrentMana(atoi(inp.c_str()));
			ally[allyCounter]->setManaFinal(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setMaxMana(atoi(inp.c_str()));
		}
		if(inp == "Strength")
		{
			allyFile >> inp;
			ally[allyCounter]->setStrength(atoi(inp.c_str()));
		}
		if(inp == "Defense")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefense(atoi(inp.c_str()));
		}
		if(inp == "Agility")
		{
			allyFile >> inp;
			ally[allyCounter]->setAgility(atoi(inp.c_str()));
		}
		if(inp == "Image")
		{
			allyFile >> inp;
			ally[allyCounter]->setTextureSprite(inp);

			allyFile >> inp;
			ally[allyCounter]->setTextureRect(0, atoi(inp.c_str()));
		}
		//TODO Exp and ally is in party?
		
		allyFile >> inp;
	} while(!allyFile.eof());
	allyFile.close();
}

void FileReader::loadSkill(std::vector<Skill*>& skillList)
{
	std::string strInp;
	std::ifstream skillFile("data/skillList");
	int skillCounter = -1;
	int type;

	while(!skillFile.eof())
	{
		skillFile >> strInp;
		if(strInp == "Skill")
		{
			skillFile >> strInp;
			skillCounter++;
			skillList.push_back(new Skill);
		}
		else if(strInp == "Name")
		{
			skillList[skillCounter]->setName(getWholeText(skillFile));
		}
		else if(strInp == "Type")
		{
			skillFile >> strInp;
			if(strInp == "Damage")
			{
				type = 0;
			}
			else if(strInp == "Heal")
			{
				type = 1;
			}
			else if(strInp == "Debuff")
			{
				type = 2;
			}
			else if(strInp == "Buff")
			{
				type = 3;
			}
		}
		else if(strInp == "Reapply")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setReapplyTurn(type, atoi(strInp.c_str()));
		}
		else if(strInp == "Percent")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setPercent(type, atoi(strInp.c_str()));
		}
		else if(strInp == "Mult")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setMult(type, atof(strInp.c_str()));
		}
		else if(strInp == "Max")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setMax(type, atoi(strInp.c_str()));
		}
		else if(strInp == "Min")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setMin(type, atoi(strInp.c_str()));
		}
		else if(strInp == "ManaCost")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setManaCost(atoi(strInp.c_str()));
		}
		else if(strInp == "Crit")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setCrit(atoi(strInp.c_str()));
		}
		else if(strInp == "Accuracy")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setAccuracy(atoi(strInp.c_str()));
		}
		else if(strInp == "EnemyPrio")
		{
			skillFile >> strInp;
			skillList[skillCounter]->setChance(atoi(strInp.c_str()));
		}
	}
	skillFile.close();
}

void FileReader::loadMapEnemies(std::vector<Character>& enemyListStore, std::string enemyList)
{
	//Temp variables
	std::string strInp;
	int tempCounter = -1;

	//Read from enemyFile to create enemyListStore purely for storing enemy info
	enemyListStore.clear();
	std::ifstream enemyFile(enemyList);
	while(!enemyFile.eof())
	{
		enemyFile >> strInp;
		//TODO Enemy file also stores which skills the enemy should use
		if(strInp == "Enemy")
		{
			tempCounter++;
			enemyListStore.push_back(*new Character);
			enemyListStore[tempCounter].setAlive(true);
			enemyFile >> strInp;
		}
		if(strInp == "Name")
		{
			enemyListStore[tempCounter].setName(getWholeText(enemyFile));
		}
		if(strInp == "Level")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setLevel(atoi(strInp.c_str()));
		}
		if(strInp == "Hp")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setMaxHp(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setCurrentHp(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setHpFinal(atoi(strInp.c_str()));
		}
		if(strInp == "Mana")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setMaxMana(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setCurrentMana(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setManaFinal(atoi(strInp.c_str()));
		}
		if(strInp == "Strength")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setStrength(atoi(strInp.c_str()));
		}
		if(strInp == "Defense")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setDefense(atoi(strInp.c_str()));
		}
		if(strInp == "Agility")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setAgility(atoi(strInp.c_str()));
		}
		if(strInp == "Chance")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setChance(atoi(strInp.c_str()));
		}
		if(strInp == "Image")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setTextureSprite(strInp);
			enemyFile >> strInp;
			//TODO where the enemy is located in the file (y location)
			enemyListStore[tempCounter].setTextureRect(0, atoi(strInp.c_str()));
		}
	}
	enemyFile.close();
}

void FileReader::loadMainMapFile(std::string fileNm, std::vector<Npc*>& npc, std::vector<Character>& enemyListStore, int& prevZ, int& prevM, int& startPosX, int& startPosY, int& currentZone, int& currentMap, int& encounterRate)
{
	//Temp variables
	std::string strInp;
	int intInp = 0;
	int numOne, numTwo, numThree;
	numOne = numTwo = numThree = 0;
	int curChoice = 1;

	int npcCounter = -1;
	int currentTextNum = -1;
	npc.clear();

	std::ifstream mainMapFile(fileNm);
	do
	{
		mainMapFile >> strInp;
		if(strInp == "EncRate")
		{
			mainMapFile >> strInp;
			encounterRate = atoi(strInp.c_str());
		}
		if(strInp == "EnemList")
		{
			mainMapFile >> strInp;
			std::string tempEnemyList = "data/enemies/" + strInp;
			loadMapEnemies(enemyListStore, tempEnemyList);
		}
		if(strInp == "PrevZM")
		{
			//TODO
			mainMapFile >> strInp;
			int potenPrevZ = atoi(strInp.c_str());
			mainMapFile >> strInp;
			int potenPrevM = atoi(strInp.c_str());

			//TODO
			mainMapFile >> strInp;
			if(potenPrevZ == prevZ && potenPrevM == prevM)
			{
				mainMapFile >> strInp;
				startPosX = atoi(strInp.c_str()) * 64;
				mainMapFile >> strInp;
				startPosY = atoi(strInp.c_str()) * 64;
			}
			else
			{
				mainMapFile >> strInp;
				mainMapFile >> strInp;
			}
		}
		if(strInp == "Npc")
		{
			//Reset text number
			currentTextNum = -1;

			//Increments and makes new npc
			npcCounter++;
			Npc tempNpc;
			npc.push_back(new Npc);
		}
		if(strInp == "Image")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->setTextureSprite(strInp);
		}
		if(strInp == "ImagePos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			mainMapFile >> numThree;
			npc[npcCounter]->setTextureRect(numOne, numTwo, numThree);
		}
		if(strInp == "Pos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			npc[npcCounter]->setPosition(numOne * 64, numTwo * 64);
		}
		if(strInp == "Name")
		{
			npc[npcCounter]->setName(getWholeText(mainMapFile));
		}
		if(strInp == "Start")
		{
			//The beginning of new text for a npc
			currentTextNum++;
			npc[npcCounter]->pushNextText();
		}
		if(strInp == "CondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(true);
		}
		if(strInp == "CondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(false);
		}
		if(strInp == "Text")
		{
			npc[npcCounter]->pushText(getWholeText(mainMapFile));
		}
		if(strInp == "SetCondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(true);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
		if(strInp == "SetCondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(false);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
		if(strInp == "Choice")
		{
			npc[npcCounter]->curChoiceTrue();
			npc[npcCounter]->pushChoice(getWholeText(mainMapFile));
		}
		if(strInp == "ChoiceOne")
		{
			curChoice = 1;
			npc[npcCounter]->pushChoiceOne(getWholeText(mainMapFile));
		}
		if(strInp == "ChoiceTwo")
		{
			curChoice = 2;
			npc[npcCounter]->pushChoiceTwo(strInp);
		}
		if(strInp == "*SetCondTrue")
		{
			mainMapFile >> intInp;
			if(curChoice == 1)
			{
				npc[npcCounter]->pushChgOneNum(intInp);
				npc[npcCounter]->pushChgOneBool(true);
			}
			else if(curChoice == 2)
			{
				npc[npcCounter]->pushChgTwoNum(intInp);
				npc[npcCounter]->pushChgTwoBool(true);
			}
		}
		if(strInp == "*SetCondFalse")
		{
			mainMapFile >> intInp;
			if(curChoice == 1)
			{
				npc[npcCounter]->pushChgOneNum(intInp);
				npc[npcCounter]->pushChgOneBool(false);
			}
			else if(curChoice == 2)
			{
				npc[npcCounter]->pushChgTwoNum(intInp);
				npc[npcCounter]->pushChgTwoBool(false);
			}
		}
		if(strInp == "*Text")
		{
			if(curChoice == 1)
			{
				npc[npcCounter]->pushChoiceOneDisp(getWholeText(mainMapFile));
			}
			else if (curChoice == 2)
			{
				npc[npcCounter]->pushChoiceTwoDisp(getWholeText(mainMapFile));
			}
		}
	} while(!mainMapFile.eof());
	mainMapFile.close();
}

//Utility
std::string FileReader::getWholeText(std::ifstream& fileObject)
{
	char readText[256];

	//Skip spcae
	fileObject.ignore();

	//Gets the entire text
	fileObject.getline(readText, 256);

	std::string stringStore = readText;

	return stringStore;
}
