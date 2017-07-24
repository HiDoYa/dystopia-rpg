#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager
{
	private:
		//TODO Instead of making new font instance in classes, make one font instance in statemanager and pass them into various classes
		//TODO Make "updatePosition" (uses "view") centralized: maybe wrapper?
		//For reading data
		FileReader fileReader;

		//State control
		int currentState;
		int currentBattleState;
		std::vector<bool> stateFlag;
	
		//Menu (state 0)
		MainMenu mainMenu;
		bool menuLoaded;

		//Map (state 1)
		bool mapLoaded;

		UIOverlay overlay;
		Textbox textbox;

		std::unique_ptr<Map> ground;
		std::unique_ptr<Map> background;
		std::unique_ptr<Map> collision;

		std::vector<std::shared_ptr<Npc>> npc;
		bool speaking;

		std::vector<std::shared_ptr<Item>> itemList;
		//Each integer indicates how many of each item is held
		std::vector<int> itemHeld;

		std::vector<std::shared_ptr<Character>> ally;
		//Allies that are discovered (0 is there by default)
		std::vector<int> allyFound;
		//Allies that are in party (0 is there by default)
		std::vector<int> allyInParty;

		MapPlayer player;

		//Map specific
		int prevZ;
		int prevM;
		int startPosX;
		int startPosY;
		int currentZone;
		int currentMap;
		int encounterRate;
		std::vector<std::shared_ptr<Character>> enemyListStore;

		//Battle (state 2)
		std::vector<std::shared_ptr<Skill>> skillList;
		std::vector<int> unlockedSkills;
		bool battleLoaded;
		int nextBattleState;
		int milliDelay;
		std::unique_ptr<Battle> battle;

		//Map Menu (state 3)
		MapMenu mapMenu;
		int menuOption;
		bool mapMenuLoaded;

	public:
		StateManager();

		//Menu
		void loadMenu();
		void updateMenu(sf::RenderWindow&);

		//Map
		void loadMap(sf::RenderWindow&);
		void updateMap(sf::RenderWindow&, sf::View&);
		void renderMap(sf::RenderWindow&, sf::View&);

		//Battle
		void loadBattle(sf::RenderWindow&, sf::View&);
		void updateBattle(sf::RenderWindow&, sf::View&);
		void renderBattle(sf::RenderWindow&, sf::View&);

		//Map Menu
		void loadMapMenu(sf::RenderWindow&, sf::View);
		void updateMapMenu(sf::RenderWindow&, sf::View);
		void renderMapMenu(sf::RenderWindow&);

		//Accessors
		int getCurrentState();
};

#endif
