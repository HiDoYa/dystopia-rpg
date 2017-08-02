#include <iostream>
#include <fstream>

#include "Character.h"
#include "Skill.h"

#include "FileReader.h"

FileReader::FileReader()
{
}

//Game loading
void FileReader::loadAlly(std::vector<std::shared_ptr<Character>>& ally)
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
			std::shared_ptr<Character> tempPtr (new Character);
			ally.push_back(tempPtr);
			allyCounter++;
			//Get rid of the extra number
			allyFile >> inp;
		}
		else if(inp == "Name")
		{
			ally[allyCounter]->setName(getWholeText(allyFile));
		}
		else if(inp == "Level")
		{
			allyFile >> inp;
			ally[allyCounter]->setLevel(atoi(inp.c_str()));
		}
		else if(inp == "Hp")
		{
			allyFile >> inp;
			ally[allyCounter]->setCurrentHp(atoi(inp.c_str()));
			ally[allyCounter]->setHpFinal(atoi(inp.c_str()));
			ally[allyCounter]->setMaxHp(atoi(inp.c_str()));
		}
		else if(inp == "Mana")
		{
			allyFile >> inp;
			ally[allyCounter]->setCurrentMana(atoi(inp.c_str()));
			ally[allyCounter]->setManaFinal(atoi(inp.c_str()));
			ally[allyCounter]->setMaxMana(atoi(inp.c_str()));
		}
		else if(inp == "Strength")
		{
			allyFile >> inp;
			ally[allyCounter]->setStrength(atoi(inp.c_str()));
		}
		else if(inp == "Defense")
		{
			allyFile >> inp;
			ally[allyCounter]->setDefense(atoi(inp.c_str()));
		}
		else if(inp == "Agility")
		{
			allyFile >> inp;
			ally[allyCounter]->setAgility(atoi(inp.c_str()));
		}
		else if(inp == "Image")
		{
			allyFile >> inp;
			ally[allyCounter]->setTextureSprite(inp);

			allyFile >> inp;
			ally[allyCounter]->setTextureRect(atoi(inp.c_str()), 0);
		}
		else if(inp == "Skill")
		{
			std::vector<int> tempStore = ally[allyCounter]->getPossibleSkillNum();

			while(allyFile.peek() != '\n')
			{
				allyFile >> inp;
				tempStore.push_back(atoi(inp.c_str()));
			}

			ally[allyCounter]->setPossibleSkillNum(tempStore);
		}
		//TODO Exp and ally is in party?
		
		allyFile >> inp;
	} while(!allyFile.eof());
	allyFile.close();
}

void FileReader::loadSkill(std::vector<std::shared_ptr<Skill>>& skillList)
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
			skillCounter++;
			std::shared_ptr<Skill> tempPtr (new Skill);
			skillList.push_back(tempPtr);
			//Get rid of the extra number
			skillFile >> strInp;
		}
		else if(strInp == "Name")
		{
			skillList[skillCounter]->setName(getWholeText(skillFile));
		}
		else if(strInp == "Description")
		{
			skillList[skillCounter]->setDescription(getWholeText(skillFile));
		}
		else if(strInp == "PowerRating")
		{
			int intInp;
			skillFile >> intInp;
			skillList[skillCounter]->setPowerRating(intInp);
		}
		else if(strInp == "PrimaryType")
		{
			skillFile >> strInp;
			if(strInp == "Damage")
			{
				skillList[skillCounter]->setPrimaryType(0);
			}
			else if(strInp == "Heal")
			{
				skillList[skillCounter]->setPrimaryType(1);
			}
			else if(strInp == "Debuff")
			{
				skillList[skillCounter]->setPrimaryType(2);
			}
			else if(strInp == "Buff")
			{
				skillList[skillCounter]->setPrimaryType(3);
			}
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
		else if(strInp == "BuffType")
		{
			skillFile >> strInp;
			if(strInp == "Strength")
			{
				skillList[skillCounter]->setBuffType(0);
			}
			else if(strInp == "Defense")
			{
				skillList[skillCounter]->setBuffType(1);
			}
			else if(strInp == "Agility")
			{
				skillList[skillCounter]->setBuffType(2);
			}
		}
		else if(strInp == "DebuffType")
		{
			skillFile >> strInp;
			if(strInp == "Strength")
			{
				skillList[skillCounter]->setDebuffType(0);
			}
			else if(strInp == "Defense")
			{
				skillList[skillCounter]->setDebuffType(1);
			}
			else if(strInp == "Agility")
			{
				skillList[skillCounter]->setDebuffType(2);
			}
		}
		else if(strInp == "Target")
		{
			skillFile >> strInp;
			if(strInp == "SingleAlly")
			{
				skillList[skillCounter]->setTarget(type, 0);
			}
			else if(strInp == "SingleEnemy")
			{
				skillList[skillCounter]->setTarget(type, 1);
			}
			else if(strInp == "MultAlly")
			{
				skillList[skillCounter]->setTarget(type, 2);
			}
			else if(strInp == "MultEnemy")
			{
				skillList[skillCounter]->setTarget(type, 3);
			}
			else if(strInp == "Self")
			{
				skillList[skillCounter]->setTarget(type, 4);
			}
		}
		else if(strInp == "Ally")
		{
			std::vector<int> tempStore;
			while(skillFile.peek() != '\n')
			{
				skillFile >> strInp;
				tempStore.push_back(atoi(strInp.c_str()));
			}
			skillList[skillCounter]->setAllyEquip(tempStore);
		}
	}
	skillFile.close();
}

void FileReader::loadItem(std::vector<std::shared_ptr<Item>>& itemList)
{
	std::string strInp;
	int intInp;

	std::ifstream itemFile("data/itemList");

	while(!itemFile.eof())
	{
		itemFile >> strInp;
		if(strInp == "Item")
		{
			itemFile >> strInp;
			itemList.push_back(std::shared_ptr<Item>(new Item));
		}
		else if(strInp == "Name")
		{
			itemFile >> strInp;
			itemList[itemList.size() - 1]->setName(strInp);
		}
		else if(strInp == "Description")
		{
			itemFile >> strInp;
			itemList[itemList.size() - 1]->setDescription(strInp);
		}
		else if(strInp == "SellPrice")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setSellPrice(intInp);
		}
		else if(strInp == "ItemType")
		{
			itemFile >> strInp;
			if(strInp == "Weapon")
			{
				itemList[itemList.size() - 1]->setItemType(0);
			}
			else if(strInp == "Armor")
			{
				itemList[itemList.size() - 1]->setItemType(1);
			}
			else if(strInp == "ProcessingUnit")
			{
				itemList[itemList.size() - 1]->setItemType(2);
			}
			else if(strInp == "Consumable")
			{
				itemList[itemList.size() - 1]->setItemType(3);
			}
			else if(strInp == "QuestItem")
			{
				itemList[itemList.size() - 1]->setItemType(4);
			}
		}
		else if(strInp == "StrIncrease")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setStrIncrease(intInp);
		}
		else if(strInp == "DefIncrease")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setDefIncrease(intInp);
		}
		else if(strInp == "AgiIncrease")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setAgiIncrease(intInp);
		}
		else if(strInp == "HpIncrease")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setHpIncrease(intInp);
		}
		else if(strInp == "ManaIncrease")
		{
			itemFile >> intInp;
			itemList[itemList.size() - 1]->setManaIncrease(intInp);
		}
	}
}

void FileReader::loadMapEnemies(std::vector<std::shared_ptr<Character>>& enemyListStore, std::string enemyList)
{
	//Temp variables
	std::string strInp;
	int intInp;
	int tempCounter = -1;

	//Read from enemyFile to create enemyListStore purely for storing enemy info
	enemyListStore.clear();
	std::ifstream enemyFile(enemyList);
	while(!enemyFile.eof())
	{
		enemyFile >> strInp;
		if(strInp == "Enemy")
		{
			tempCounter++;
			std::shared_ptr<Character> tempPtr (new Character);
			enemyListStore.push_back(tempPtr);
			enemyListStore[tempCounter]->setAlive(true);
			enemyListStore[tempCounter]->setCanAtk(true);
			//Get rid of the extra number
			enemyFile >> strInp;
		}
		else if(strInp == "Name")
		{
			enemyListStore[tempCounter]->setName(getWholeText(enemyFile));
		}
		else if(strInp == "Level")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setLevel(intInp);
		}
		else if(strInp == "Hp")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setMaxHp(intInp);
			enemyListStore[tempCounter]->setCurrentHp(intInp);
			enemyListStore[tempCounter]->setHpFinal(intInp);
		}
		else if(strInp == "Mana")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setMaxMana(intInp);
			enemyListStore[tempCounter]->setCurrentMana(intInp);
			enemyListStore[tempCounter]->setManaFinal(intInp);
		}
		else if(strInp == "Strength")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setStrength(intInp);
		}
		else if(strInp == "Defense")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setDefense(intInp);
		}
		else if(strInp == "Agility")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setAgility(intInp);
		}
		else if(strInp == "Chance")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setChance(intInp);
		}
		else if(strInp == "Image")
		{
			enemyFile >> strInp;
			enemyListStore[tempCounter]->setTextureSprite(strInp);

			//Where the enemy is located in the file (y location)
			enemyFile >> intInp;
			enemyListStore[tempCounter]->setTextureRect(0, intInp);
		}
		else if(strInp == "Skill")
		{
			std::vector<int> tempStore;

			while(enemyFile.peek() != '\n')
			{
				enemyFile >> strInp;
				tempStore.push_back(atoi(strInp.c_str()));
			}

			enemyListStore[tempCounter]->setSkillNum(tempStore);
		}
		else if(strInp == "Drop")
		{
			enemyFile >> intInp;
			enemyListStore[tempCounter]->pushDropItemId(intInp);

			enemyFile >> intInp;
			enemyListStore[tempCounter]->pushDropItemChance(intInp);
		}
	}
	enemyFile.close();
}

void FileReader::loadMainMapFile(std::string fileNm,
		std::vector<std::shared_ptr<Npc>>& npc,
		std::vector<std::shared_ptr<Character>>& enemyListStore,
		int& prevZ, int& prevM,
		int& startPosX, int& startPosY,
		int& currentZone, int& currentMap,
		int& encounterRate)
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
	mainMapFile >> strInp;
	do
	{
		if(strInp == "EncRate")
		{
			mainMapFile >> strInp;
			encounterRate = atoi(strInp.c_str());
		}
		else if(strInp == "EnemList")
		{
			mainMapFile >> strInp;
			std::string tempEnemyList = "data/enemies/" + strInp;
			loadMapEnemies(enemyListStore, tempEnemyList);
		}
		else if(strInp == "PrevZM")
		{
			mainMapFile >> strInp;
			int potenPrevZ = atoi(strInp.c_str());
			mainMapFile >> strInp;
			int potenPrevM = atoi(strInp.c_str());

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
		else if(strInp == "Npc")
		{
			//Reset text number
			currentTextNum = -1;

			//Increments and makes new npc
			npcCounter++;
			std::shared_ptr<Npc> tempPtr (new Npc);
			npc.push_back(tempPtr);

			int numInp;
			mainMapFile >> strInp;
			mainMapFile >> numInp;

			if(strInp == "CondTrue")
			{
				npc[npcCounter]->npcExistCondition(numInp, true);
			}
			else if(strInp == "CondFalse")
			{
				npc[npcCounter]->npcExistCondition(numInp, false);
			}
		}
		else if(strInp == "Image")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->setTextureSprite(strInp);
		}
		else if(strInp == "ImagePos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			mainMapFile >> numThree;
			npc[npcCounter]->setTextureRect(numOne, numTwo, numThree);
		}
		else if(strInp == "Pos")
		{
			mainMapFile >> numOne;
			mainMapFile >> numTwo;
			npc[npcCounter]->setPosition(numOne * 64, numTwo * 64);
		}
		else if(strInp == "Name")
		{
			npc[npcCounter]->setName(getWholeText(mainMapFile));
		}
		else if(strInp == "Start")
		{
			//The beginning of new text for a npc
			currentTextNum++;
			npc[npcCounter]->pushNextText();
		}
		else if(strInp == "CondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(true);
		}
		else if(strInp == "CondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushCondition(atoi(strInp.c_str()));
			npc[npcCounter]->pushConditionCheck(false);
		}
		else if(strInp == "Text")
		{
			npc[npcCounter]->pushText(getWholeText(mainMapFile));
		}
		else if(strInp == "SetCondTrue")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(true);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
		else if(strInp == "SetCondFalse")
		{
			mainMapFile >> strInp;
			npc[npcCounter]->pushChgCheck(false);
			npc[npcCounter]->pushChgNum(atoi(strInp.c_str()));
		}
		else if(strInp == "Give")
		{
			int idNum;
			mainMapFile >> strInp;
			if(strInp == "Ally")
			{
				npc[npcCounter]->pushGiveType(0);
				mainMapFile >> idNum;
				npc[npcCounter]->pushGiveId(idNum);
			}
			else if(strInp == "Skill")
			{
				npc[npcCounter]->pushGiveType(1);
				mainMapFile >> idNum;
				npc[npcCounter]->pushGiveId(idNum);
			}
		}
		else if(strInp == "Choice")
		{
			npc[npcCounter]->curChoiceTrue();
			npc[npcCounter]->pushChoice(getWholeText(mainMapFile));
		}
		else if(strInp == "ChoiceOne")
		{
			curChoice = 1;
			npc[npcCounter]->pushChoiceOne(getWholeText(mainMapFile));
		}
		else if(strInp == "ChoiceTwo")
		{
			curChoice = 2;
			npc[npcCounter]->pushChoiceTwo(getWholeText(mainMapFile));
		}
		else if(strInp == "*SetCondTrue")
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
		else if(strInp == "*SetCondFalse")
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
		else if(strInp == "*Give")
		{
			int idNum;
			mainMapFile >> strInp;

			if(curChoice == 1)
			{
				if(strInp == "Ally")
				{
					npc[npcCounter]->pushGiveOneType(0);
				}
				else if(strInp == "Skill")
				{
					npc[npcCounter]->pushGiveOneType(1);
				}
				mainMapFile >> idNum;
				npc[npcCounter]->pushGiveOneId(idNum);
			}
			else if(curChoice == 2)
			{
				if(strInp == "Ally")
				{
					npc[npcCounter]->pushGiveTwoType(0);
				}
				else if(strInp == "Skill")
				{
					npc[npcCounter]->pushGiveTwoType(1);
				}
				mainMapFile >> idNum;
				npc[npcCounter]->pushGiveTwoId(idNum);
			}
			//Regular text
			else
			{
				if(strInp == "Ally")
				{
					npc[npcCounter]->pushGiveType(0);
				}
				else if(strInp == "Skill")
				{
					npc[npcCounter]->pushGiveType(1);
				}
				mainMapFile >> idNum;
				npc[npcCounter]->pushGiveId(idNum);
			}
		}
		else if(strInp == "*Text")
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

		mainMapFile >> strInp;
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
