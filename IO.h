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
	static Position moveInput(const Game & game, cellContent playerContent);
	
	private:
	void display(Board & board, cellContent playerContent);
	
	};

#endif
