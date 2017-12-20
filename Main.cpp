
/* Reversi Project - INFOH-304
 * membres du groupe : DESLYPERRE Clara, GOOSSENS Victor, MOREAU Lila, VERSTRAETEN Maxime
*/

//Main file of the game, includes main()

#include <iostream>
#include "Game.h"
#include "IO.h"
#include <chrono>
#include <sys/resource.h>
using namespace std;

int main(int argc, char **argv)
{
	
	pair<char,char> players = IO::playerCreation();
	Game *game = new Game(players.first, players.second);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	game->gameStart();
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

	std::cout << "Game took (sec) : " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0 <<std::endl;
	
	delete game;
	return 0;
}






