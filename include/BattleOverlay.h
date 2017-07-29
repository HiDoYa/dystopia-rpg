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
		void attackedLog(std::string, std::string, int = -1);
		void healedLog(std::string, std::string, int = -1);
		void buffedLog(std::string, std::string, std::string, int = -1);
		void debuffedLog(std::string, std::string, std::string, int = -1);

		void chargedLog(std::string, int = -1);

		void genericSkillLog(std::string, std::string);

		std::string targetNameExceptions(std::string);
		void updateBattleLog(std::string strInp, bool replace = true);

		void drawAll(sf::RenderWindow&);
};

#endif
