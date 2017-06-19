#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager
{
	private:
		//For reading data
		FileReader fileReader;

		//State control
		int currentState;
		int currentBattleState;
		std::vector<bool> stateFlag;
	
		//Menu (state 0)
		bool menuLoaded;
		MainMenu mainMenu;

		//Map (state 1)
		bool mapLoaded;

		UIOverlay overlay;
		Textbox textbox;

		std::unique_ptr<Map> ground;
		std::unique_ptr<Map> background;
		std::unique_ptr<Map> collision;

		std::vector<Npc*> npc;
		bool speaking;

		std::vector<Character*> ally;
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
		std::vector<Character> enemyListStore;

		//Battle (state 2)
		std::vector<Skill*> skillList;
		bool battleLoaded;
		std::unique_ptr<Battle> battle;

	public:
		StateManager();

		//Menu
		void allMenu(sf::RenderWindow&);
		void loadMenu();
		void updateMenu(sf::RenderWindow&);

		//Map
		void allMap(sf::RenderWindow&, sf::View&);
		void loadMap(sf::RenderWindow&);
		void updateMap(sf::RenderWindow&, sf::View&);
		void renderMap(sf::RenderWindow&, sf::View&);

		//Battle
		void allBattle(sf::RenderWindow&, sf::View&);
		void loadBattle(sf::RenderWindow&, sf::View&);
		void updateBattle(sf::RenderWindow&, sf::View&);
		void renderBattle(sf::RenderWindow&, sf::View&);

		//Accessors
		int getCurrentState();
};

#endif
