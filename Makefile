all: Game.o Position.o Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Cell.o
	g++ -std=c++11 Position.o Board.o Player.o HumanPlayer.o FilePlayer.o AIPlayer.o Cell.o Main.cpp -o projet

#Game.o:
#	g++ -std=c++11 -c Game.cpp

#Board.o:
#	g++ -std=c++11 -c Board.cpp

#Player.o:
#	g++ -std=c++11 -c Player.cpp

#HumanPlayer.o:
#	g++ -std=c++11 -c HumanPlayer.cpp

#FilePlayer.o:
#	g++ -std=c++11 -c FilePlayer.cpp

#AIPlayer.o:
#	g++ -std=c++11 -c AIPlayer.cpp

#Cell.o:
#	g++ -std=c++11 -c Cell.cpp



### Permet d'éviter de devoir écrire la compilation en .o pour chaque nouveau fichier !
### $@ correspond à l'entrée (.o) et $< correspond à la sortie (.cpp)

%.o: %.cpp
	g++ -std=c++11 -c -o $@ $<



clean:
	rm *.o
	rm projet


