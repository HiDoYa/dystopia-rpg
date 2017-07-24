#include "SpriteManager.h"

#ifndef BATTLEOVERLAY_H
#define BATTLEOVERLAY_H

class BattleOverlay
{
	private:
		SpriteManager bgSprite;

		sf::Font font;

		sf::Text battleLog;
		sf::Text currentCharDesc;
		sf::Text damageNumbers;
	public:
		BattleOverlay();
		void showCurrentCharDesc();

		//Current Char
		//TODO If current char is attacking, show its stats
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
