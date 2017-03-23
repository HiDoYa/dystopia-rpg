#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dialogue.h"

Dialogue::Dialogue()
{
}

void Dialogue::pushText(std::string textInp)
{
	text.push_back(textInp);
}

void Dialogue::pushCondition(int condInp)
{
	condition.push_back(condInp);
}

void Dialogue::pushConditionNeg(bool condNegInp)
{
	conditionNeg.push_back(condNegInp);
}

void Dialogue::pushChgCheck(bool chgChkInp)
{
	chgCheck.push_back(chgChkInp);
}

void Dialogue::pushChgNeg(bool chgNegInp)
{
	chgNeg.push_back(chgNegInp);
}

void Dialogue::pushChgNum(int chgNumInp)
{
	chgNum.push_back(chgNumInp);
}

void Dialogue::pushChoiceCheck(bool choiceChkInp)
{
	choiceCheck.push_back(choiceChkInp);
}

void Dialogue::pushChoiceOne(std::string choiceOneInp)
{
	choiceOne.push_back(choiceOneInp);
}

void Dialogue::pushChoiceTwo(std::string choiceTwoInp)
{
	choiceTwo.push_back(choiceTwoInp);
}

void Dialogue::pushChgChoice(
