
/* Reversi Project - INFOH-304
 * membres du groupe : DESLYPERRE Clara, GOOSSENS Victor, MOREAU Lila, VERSTRAETEN Maxime
*/

//Main file of the game, includes main()

#include <iostream>
#include "Game.h"
#include "IO.h"
using namespace std;

int main(int argc, char **argv)
{
	pair<char,char> players = IO::playerCreation();
	Game *game = new Game(players.first, players.second);
	game->gameStart();
	delete game;
	
	return 0;
}
