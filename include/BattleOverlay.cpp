#include <SFML/Graphics.hpp>
#include <iostream>

#include "BattleOverlay.h"

BattleOverlay::BattleOverlay()
{
	bgTexture.loadFromFile("images/ui/battleUi.png");
	bgSprite.setTexture(&bgTexture);

	font.loadFromFile("font/Ubuntu.ttf");

	battleLog.setFont(font);
	currentCharDesc.setFont(font);
	damageNumbers.setFont(font);

	battleLog.setCharacterSize(15);
	currentCharDesc.setCharacterSize(15);
	damageNumbers.setCharacterSize(15);

	battleLog.setPosition(sf::Vector2f(100, 600));
	currentCharDesc.setPosition(sf::Vector2f(100, 200));
}

void BattleOverlay::showCurrentCharDesc()
{
}

void BattleOverlay::updateBattleLog()
{
}

void BattleOverlay::drawAll(sf::RenderWindow& win)
{
	win.draw(bgSprite);
	win.draw(battleLog);
	win.draw(currentCharDesc);
	win.draw(damageNumbers);
}
