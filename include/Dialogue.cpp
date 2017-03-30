#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dialogue.h"

//Flag 0 is always false and flag 1 is always true

Dialogue::Dialogue()
{
}

void Dialogue::pushNextText()
{
	std::vector<int> newIntVec;
	std::vector<bool> newBoolVec;

	condition.push_back(newIntVec);
	conditionCheck.push_back(newBoolVec);
	chgNum.push_back(newIntVec);
	chgCheck.push_back(newBoolVec);
}

void Dialogue::pushText(std::string textInp)
{
	text.push_back(textInp);
}

void Dialogue::pushCondition(int condInp)
{
	condition[condition.size() - 1].push_back(condInp);
}

void Dialogue::pushConditionCheck(bool condCheckInp)
{
	conditionCheck[conditionCheck.size() - 1].push_back(condCheckInp);
}

void Dialogue::pushChgNum(int chgNumInp)
{
	chgNum[chgNum.size() - 1].push_back(chgNumInp);
}

void Dialogue::pushChgCheck(bool chgChkInp)
{
	chgCheck[chgCheck.size() - 1].push_back(chgChkInp);
}

//******** ACCESSORS **********
std::vector<std::string> Dialogue::getText()
{
	return text;
}

std::vector<std::vector<int>> Dialogue::getCondition()
{
	return condition;
}

std::vector<std::vector<bool>> Dialogue::getConditionCheck()
{
	return conditionCheck;
}

std::vector<std::vector<int>> Dialogue::getChgNum()
{
	return chgNum;
}

std::vector<std::vector<bool>> Dialogue::getChgCheck()
{
	return chgCheck;
}
