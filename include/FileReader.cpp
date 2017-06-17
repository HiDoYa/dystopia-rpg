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
	allyFile.open("data/ally/allyList");
	std::string inp;
	int allyCounter = -1;

	allyFile >> inp;

	do
	{
		if(inp == "Ally")
		{
			ally.push_back(new Character());
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
			ally[allyCounter]->setFinalHp(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setMaxHp(atoi(inp.c_str()));
		}
		if(inp == "Mana")
		{
			allyFile >> inp;
			ally[allyCounter]->setCurrentMana(atoi(inp.c_str()));

			allyFile >> inp;
			ally[allyCounter]->setMaxMana(atoi(inp.c_str()));
		}
		if(inp == "Strength")
		{
			allyFile >> inp;
			ally[allyCounter]->setStrength(atoi(in.c_str()));
		}
		if(inp == "Defense")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefense(atoi(in.c_str()));
		}
		if(inp == "Agility")
		{
			allyFile >> inp;
			ally[allyCounter]->setAgility(atoi(in.c_str()));
		}
		if(inp == "Image")
		{
			allyFile >> inp;
			ally[allyCounter]->setTextureSprite(inp);

			allFile >> inp;
			ally[allyCounter]->setTextureRect(0, atoi(inp.c_str()));
		}
		//TODO Exp and ally is in party?
		
		allyFile >> inp;
	} while(!allyFile.eof());
	allyFile.close();
}

void FileReader::loadSkill(std::vector<Skill>& skill)
{
}

//Per each map
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
			enemyListStore.push_back(new Character());
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
			enemyListStore[tempCounter].setFinalHp(atoi(strInp.c_str()));
		}
		if(strInp == "Mana")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter].setMaxMana(atoi(strInp.c_str()));
			enemyListStore[tempCounter].setCurrentMana(atoi(strInp.c_str()));
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

void loadMainMapFile(std::string fileNm, std::vector<Npc*>& npc, std::vector<Character>& enemyListStore, int& prevZ, int& prevM, int& startPosX, int& startPosY, int& currentZone, int& currentMap, int& encounterRate)
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
			npc.push_back(new Npc());
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
std::string FileReader::getWholeText(ifstream& fileObject)
{
	char readText;
	std::string stringStore;
	
	while(fileObject.peek() != '\n')
	{
		fileObject.get(readText);
		stringStore += readText;
	}

	return stringStore;
}
