OBJ = main.o Textbox.o Npc.o Player.o Mouse.o Map.o

all: game

game: $(OBJ)
	g++ $(OBJ) -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app -g

main.o: main.cpp
	g++ -std=c++11 -c $<

Textbox.o: include/Textbox.cpp include/Textbox.h
	g++ -std=c++11 -c $<

Npc.o: include/Npc.cpp include/Npc.h
	g++ -std=c++11 -c $<

Player.o: include/Player.cpp include/Player.h
	g++ -std=c++11 -c $<

Mouse.o: include/Mouse.cpp include/Mouse.h
	g++ -std=c++11 -c $<

Map.o: include/Map.cpp include/Map.h
	g++ -std=c++11 -c $<
