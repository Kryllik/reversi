
/* Reversi Project - INFOH-304
 * membres du groupe : DESLYPERRE Clara, GOOSSENS Victor, MOREAU Lila, VERSTRAETEN Maxime
*/

//Main file of the game, includes main()

#include "Game.h"

int main(int argc, char **argv)
{
		
	Game *game = new Game();
	game->gameStartPvP();
	delete game;
	
	return 0;
}
