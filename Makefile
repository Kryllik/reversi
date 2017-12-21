all: Game.o Position.o Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Cell.o IO.o
	g++ -std=c++11 -g -O3 -mtune=native Game.o Position.o Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Cell.o IO.o Main.cpp -o projet

%.o: %.cpp
	g++ -std=c++11 -O3 -mtune=native -Wall -g -c -o $@ $<

clean:
	rm -f *.o
	rm -f projet
	rm -f blanc.txt
	rm -f noir.txt


