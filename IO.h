#ifndef IO_H
#define IO_H


#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Position.h"
#include "Game.h"
#include "Player.h"

using namespace std;


class IO{
	public:
	static Position moveInput(const Board & gameBoard, const cellContent playerContent);
	static void display(Board & board, const Player &player, Position pos);
	static void displayWhoPlays(const Player &player, Board const& gameBoard);
	static void displayFirstTurn(Board & board);
	static pair<char,char> playerCreation();
	static void displayScore(int blackScore, int whiteScore);
	static void displayValidMoves(std::vector<Position> v);
	static void boardDisplay(Board & board);
	private:
	
	static void displayValidMoves(const Player &player, Board const& gameBoard);
	
};

#endif
