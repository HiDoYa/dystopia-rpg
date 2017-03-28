#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager
{
	private:
		//State control
		int currentState;
		int currentBattleState;
	
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

		Npc tempNpc;
		std::vector<Npc> npc;
		bool speaking;

		Ally tempAlly;
		std::vector<Ally> ally;

		Player player;

		//Map specific
		int prevZ;
		int prevM;
		int startPosX;
		int startPosY;
		int currentZone;
		int currentMap;
		int encounterRate;
		Enemy tempEnemy;
		std::vector<Enemy> enemyListStore;

		//Battle (state 2)
		bool battleLoaded;
		std::unique_ptr<Battle> battle;

	public:
		StateManager();

		//Menu
		void allMenu(sf::RenderWindow&);
		void loadMenu();
		void loadAlly();
		void updateMenu(sf::RenderWindow&);

		//Map
		void allMap(sf::RenderWindow&, sf::View&);
		void loadMap(sf::RenderWindow&);
		void loadMapEnemies(std::string);
		void loadMainMapFile(std::string);
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
