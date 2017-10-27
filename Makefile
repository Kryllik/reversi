all: Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Pawn.o
	g++ Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Pawn.o Game.cpp -o projet

Board.o:
	g++ -c Board.cpp

Player.o:
	g++ -c Player.cpp

HumanPlayer.o:
	g++ -c HumanPlayer.cpp

FilePlayer.o:
	g++ -c FilePlayer.cpp

AIPlayer.o:
	g++ -c AIPlayer.cpp

Pawn.o:
	g++ -c Pawn.cpp


clean:
	rm *.o
