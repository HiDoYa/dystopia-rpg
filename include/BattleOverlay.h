#include "Character.h"
#include "SpriteManager.h"

#ifndef BATTLEOVERLAY_H
#define BATTLEOVERLAY_H

class BattleOverlay
{
	private:
		SpriteManager bgSprite;

		sf::Font font;

		//Current char description
		sf::Text currentCharDesc;

		sf::Text battleLog;
		sf::Text damageNumbers;
	public:
		BattleOverlay();

		//Current Char
		void showCurrentCharDesc();
		void showCurrentCharDesc(Character);

		//TODO Char attack order?

		//Battle log
		void attackedLog(std::string, std::string, int);
		void healedLog(std::string, std::string, int);
		void buffedLog(std::string, std::string, std::string, int);
		void debuffedLog(std::string, std::string, std::string, int);

		void genericSkillLog(std::string, std::string);
		void updateBattleLog(std::string strInp, bool replace = true);

		void drawAll(sf::RenderWindow&);
};

#endif
