#ifndef IO_H
#define IO_H


#include <iostream>
#include "Position.h"
#include "Game.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


class IO{
	public:
	static Position moveInput(const Game & game, const cellContent playerContent);
	static void display(Board & board, const cellContent playerContent, Game const& game,  Position pos);
	static void displayFirstTurn(Board & board, Game const& game);

	private:
	static void boardDisplay(Board & board);
	static void displayValidMoves(const cellContent playerContent, Game const& game);
};

#endif
