OBJ = main.o Textbox.o Npc.o Player.o Mouse.o Map.o


all: game

game: $(OBJ)
	g++ $(OBJ) -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./sfml-app -g

$(objects): %.o: %.cpp %.h
	g++ -std=c++11 -c %.cpp
