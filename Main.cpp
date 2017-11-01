#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Game.h"
#include "IO.h"
using namespace std;


int main(int argc, char **argv)
{
		
	Game *game = new Game();
	game->gameStartPvP();
	delete game;
	
	return 0;
}
