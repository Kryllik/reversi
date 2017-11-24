#ifndef IO_H
#define IO_H


#include <iostream>
#include "Position.h"
#include "Game.h"
#include "Player.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


class IO{
	public:
	static Position moveInput(const Game & game, const cellContent playerContent);
	static void display(Board & board, const Player &player, Game const& game,  Position pos);
	static void displayWhoPlays(const Player &player, Game const& game);
	static void displayFirstTurn(Board & board, Game const& game);
	static void displayScore(int blackScore, int whiteScore);
	static void displayValidMoves(std::vector<Position> v);

	private:
	static void boardDisplay(Board & board);
	static void displayValidMoves(const Player &player, Game const& game);
	
};

#endif
