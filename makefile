OBJ = main.o Textbox.o SpriteManager.o Map.o Npc.o MapPlayer.o Battle.o UIOverlay.o MainMenu.o StateManager.o Character.o Dialogue.o Skill.o FileReader.o ClickButton.o BattleOverlay.o
all: game

game: $(OBJ)
	g++ $(OBJ) -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app -g

main.o: main.cpp
	g++ -std=c++11 -c $<

Battle.o: include/Battle.cpp
	g++ -std=c++11 -c $<

BattleOverlay.o: include/BattleOverlay.cpp
	g++ -std=c++11 -c $<

Character.o: include/Character.cpp
	g++ -std=c++11 -c $<

ClickButton.o: include/ClickButton.cpp
	g++ -std=c++11 -c $<

Dialogue.o: include/Dialogue.cpp
	g++ -std=c++11 -c $<

FileReader.o: include/FileReader.cpp
	g++ -std=c++11 -c $<

MainMenu.o: include/MainMenu.cpp
	g++ -std=c++11 -c $<

Map.o: include/Map.cpp
	g++ -std=c++11 -c $<

MapMenu.o: include/MapMenu.cpp
	g++ -std=c++11 -c $<

MapPlayer.o: include/MapPlayer.cpp
	g++ -std=c++11 -c $<

Npc.o: include/Npc.cpp
	g++ -std=c++11 -c $<

SpriteManager.o: include/SpriteManager.cpp
	g++ -std=c++11 -c $<

StateManager.o: include/StateManager.cpp
	g++ -std=c++11 -c $<
	
Skill.o: include/Skill.cpp
	g++ -std=c++11 -c $<
	
Textbox.o: include/Textbox.cpp
	g++ -std=c++11 -c $<

UIOverlay.o: include/UIOverlay.cpp
	g++ -std=c++11 -c $<

clean:
	rm *.o
