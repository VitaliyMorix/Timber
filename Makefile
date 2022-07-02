all:
	g++ -c main.cpp
	g++ main.o -o timber -lsfml-graphics -lsfml-window -lsfml-system