all: compile link

compile:
	g++ -I src/include -c main.cpp

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system