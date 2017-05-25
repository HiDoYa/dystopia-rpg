#include "Character.h"
#include "UIOverlay.h"

#ifndef BATTLE_H
#define BATTLE_H

//Handles enemies and battles class Battle
class Battle
{
	private:
		//TODO Keep "skills" in file for enemy, file for ally. When accessing skill, only use the number (id number associated with skill)

		//Ally options
		sf::CircleShape tempCircle;
		std::vector<sf::CircleShape> allyOptions;
		int currentOption;
		int currentOptionsShow;

		//For changing position of char
		sf::Clock clk;
		sf::Time tme;
		float currentTime;
		float lastTime;
		std::vector<sf::RectangleShape> gridRect;
		int newPos;
		bool blinkTurn;

		//TO keep track of battles
		std::vector<int> enemySelected;

		int attackXDisp;
		//nextCharType is 0 if ally, 1 if enemy, -1 if nobody
		int nextCharType;
		//nextCharCounter is the index in the array (for ally and enemies)
		int nextCharCounter;
		int goalPlace;

		//TODO If all players or all enemies are to be targeted, don't need to SELECT which target
		
		//int currentEnemySelected;
		//TODO Change currenyEnemySelected and currenyAllySelected to vector in cpp file
		int currentTarget;
		std::vector<int> currentEnemySelected;
		//Allies in front more likely to be chosen, otherwise randomized
		//TODO Allow player to choose allies (for healing abilities)
		std::vector<int> currentAllySelected;

		//For keeping track of whether the user can target enemy or ally (only for singular)
		bool singularAllyFocus;
		bool singularEnemyFocus;

		//Skill Pressed
		bool qNotPressed;
		bool wNotPressed;
		bool aNotPressed;
		bool sNotPressed;
		bool dNotPressed;
		
		//For enemies
		std::vector<Character*> ally;
		std::vector<Character> enemies;

		//Check for competion
		//TODO Think of an alternative or complete hpComplete change
		std::vector<bool> hpComplete;
		bool animComplete;

		//Grid battle
		std::vector<sf::Vector2f> allyPos;
		std::vector<sf::Vector2f> enemyPos;
		std::vector<sf::Vector2f> optionsPos;
	public:
		Battle();

		void setupBattle(std::vector<Character>, std::vector<Character*>&);

		//Battle state 0
		void findFastestChar();
		void checkForNextChar(int&);

		//Battle state 1
		void setCirclePos();
		void changeCurrentSkill();
		void chooseCurrentSkill(int&);

		//Battle state 2
		void attackEnemyType(Skill);
		void changeAllyFocus();
		void changeEnemyFocus();

		//Battle state 3
		void attackManager(int&, int&);
		void allyTurnHandle(int&, int&);
		void enemyChooseTarget();

		//For various damaging of enemies
		void allyAttackHandle();
		void attemptFlee(int&);
		void allyChangePos();
		void allyItem();
		void allyAttackAnimation(int&);
		void enemyAttackAnimation(int&);
		
		//Battle state 4
		//TODO void hpCalculate(int&, UIOverlay&);
		//TODO Do I need?
		int findHpChangeSign(int, int);

		//Takes extra integer indicating which enemy will be targeted. Recursion to finish all hp changes.
		void allyHpChange(int, int&);
		void enemyHpChange(int, int&);

		void allyPostAttackAnimation();
		void enemyPostAttackAnimation();
		void checkForCompletion(int&);
		
		//Battle state 5
		bool checkAllyDeath();
		bool checkEnemyDeaths();
		void checkEndBattle(int&, int&);
		void currentEnemyDeath();
		void newTurn();
		
		//Drawing
		void drawAll(sf::RenderWindow&, int);

		//Mutators
		void setEnemyHp(int, int);

		//Utility
		int getMaxNum(int, int);
};

#endif
