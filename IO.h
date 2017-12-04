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
	static pair<char,char> playerCreation();
	static Position moveInput(const Game & game, const cellContent playerContent);
	static void display(Board & board, const Player &player, Game const& game,  Position pos);
	static void displayWhoPlays(const Player &player, Game const& game);
	static void displayFirstTurn(Board & board, Game const& game);
	static void displayScore(int blackScore, int whiteScore);
	static void displayValidMoves(std::vector<Position> v);
	static void boardDisplay(Board & board);
	private:
	
	static void displayValidMoves(const Player &player, Game const& game);
	
};

#endif
