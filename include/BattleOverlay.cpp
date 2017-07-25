#include <SFML/Graphics.hpp>
#include <iostream>

#include "BattleOverlay.h"

BattleOverlay::BattleOverlay()
{
	bgSprite.setTextureSprite("images/ui/battleUi.png");

	font.loadFromFile("font/Ubuntu.ttf");

	battleLog.setFont(font);
	currentCharDesc.setFont(font);
	damageNumbers.setFont(font);

	currentCharDesc.setCharacterSize(15);
	damageNumbers.setCharacterSize(15);

	//Current char

	//Battle log
	battleLog.setCharacterSize(15);
	battleLog.setPosition(sf::Vector2f(100, 670));
	currentCharDesc.setPosition(sf::Vector2f(100, 200));

	battleLog.setColor(sf::Color::Black);
}

//Clear the current char description
void BattleOverlay::showCurrentCharDesc()
{
}

//Show the character's description
void BattleOverlay::showCurrentCharDesc(Character chr)
{
}

void BattleOverlay::attackedLog(std::string user, std::string target, int amount)
{
	std::string tempStr;
	if(amount != -1)
	{
		tempStr = user + " attacked " + target + " for " + std::to_string(amount) + " damage!";
	}
	else
	{
		tempStr = user + " attacked " + target + "!";
	}
	updateBattleLog(tempStr, false);
}

void BattleOverlay::healedLog(std::string user, std::string target, int amount)
{
	std::string tempStr;
	if(amount!= -1)
	{
		tempStr = user + " healed " + target + " for " + std::to_string(amount) + " health!";
	}
	else
	{
		tempStr = user + " healed " + target + "!";
	}
	updateBattleLog(tempStr, false);
}

void BattleOverlay::buffedLog(std::string user, std::string target, std::string stat, int amount)
{
	std::string tempStr;

	target = targetNameExceptions(target);

	if(amount != -1)
	{
		tempStr = user + " buffed " + target + stat + " for " + std::to_string(amount) + "!";
	}
	else
	{
		tempStr = user + " buffed " + target + stat + "!";
	}
	updateBattleLog(tempStr, false);
}

void BattleOverlay::debuffedLog(std::string user, std::string target, std::string stat, int amount)
{
	std::string tempStr;

	target = targetNameExceptions(target);

	if(amount != -1)
	{
		tempStr = user + " debuffed " + target + stat + " for " + std::to_string(amount) + "!";
	}
	else
	{
		tempStr = user + " debuffed " + target + stat + "!";
	}
	updateBattleLog(tempStr, false);
}

void BattleOverlay::genericSkillLog(std::string user, std::string skillName)
{
	updateBattleLog(user + " used " + skillName + ".");
}

std::string BattleOverlay::targetNameExceptions(std::string target)
{
	std::string targetName;
	if(target == "You")
	{
		targetName = "Your ";
	}
	else
	{
		targetName = target + "'s ";
	}
	return targetName;
}

void BattleOverlay::updateBattleLog(std::string strInp, bool replace)
{
	std::string tempStr;
	if(!replace)
	{
		tempStr = battleLog.getString();
		tempStr += '\n' + strInp;
	}
	battleLog.setString(strInp);
}

void BattleOverlay::drawAll(sf::RenderWindow& win)
{
	bgSprite.drawSprite(win);
	win.draw(battleLog);
	win.draw(currentCharDesc);
	win.draw(damageNumbers);
}
