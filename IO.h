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
	static Position moveInput(const Board & gameBoard, const cellContent playerContent);
	static void display(Board & board, const Player &player, Position pos);
	static void displayWhoPlays(const Player &player, Board const& gameBoard);
	static void displayFirstTurn(Board & board);
	static void displayScore(int blackScore, int whiteScore);
	static void displayValidMoves(std::vector<Position> v);
	static void boardDisplay(Board & board);
	private:
	
	static void displayValidMoves(const Player &player, Board const& gameBoard);
	
};

#endif
