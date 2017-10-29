#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Game.h"
using namespace std;


int main(int argc, char **argv)
{
		
	Game *game = new Game();
	
	Position pos = Position::positionFromString("b3");
	if (game->isValidMove(Black,pos)) {
		cout << pos.toString() << " is valid move" << endl;
	}
	
	pos = Position::positionFromString("d4");
	if (game->isValidMove(Black,pos)) {
		cout << pos.toString() << " is valid move" << endl;
	}
	
	pos = Position::positionFromString("c5");
	if (game->isValidMove(Black,pos)) {
		cout << pos.toString() << " is valid move" << endl;
	}
	
	pos = Position::positionFromString("e6");
	if (game->isValidMove(Black,pos)) {
		cout << pos.toString() << " is valid move" << endl;
	}
	
	delete game;
	
	return 0;
}
