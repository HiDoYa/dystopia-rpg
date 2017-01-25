main: main.cpp include/Textbox.cpp
	g++ -c main.cpp include/Textbox.cpp
	g++ main.o Textbox.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app


