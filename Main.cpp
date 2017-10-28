#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Board.h"
using namespace std;


int main(int argc, char **argv)
{
		
	cout << "bienvenue dans ce super jeu" << endl;
	Board *board = new Board(); //Crée un nouveau Board et l'initialise. Renvoie un pointeur.
	board->Display();
	delete board;
	return 0;
}
