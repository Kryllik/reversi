#include "IO.h"
#include <vector>

Position IO::moveInput(Game const & game, cellContent playerContent){
	Position pos;
	string move;
	while (true) {
		cout<<"Enter your move (column row)"<<endl;
		cin>>move;
		pos = Position::positionFromString(move);
		if (pos.isValid()) {
			if (game.isValidMove(playerContent,pos)) {
				return pos;
			} else {
				cout << "Not a valid move, try again" << endl;
			}
		} else {
			cout << "Not a correct syntax, try again" << endl;
		}
	}
}

void IO::display(Board & board, const cellContent playerContent, Game const& game, Position pos){
	string playerContentString;
	string otherPlayerString;
	cellContent otherPlayer;
	if(playerContent==Black){
		playerContentString = "Noir";
		otherPlayerString = "Blanc";
		otherPlayer = White;
	}else{
		playerContentString = "Blanc";
		otherPlayerString = "Noir";
		otherPlayer = Black;
	}
	cout << "Le joueur " << playerContentString << " vient de jouer en : " << pos.toString() << endl;
	cout << "mise à jour du board " << endl;
	boardDisplay(board);
}

void IO::displayWhoPlays(const cellContent playerContent, Game const& game){
	string playerContentString;
	if(playerContent==Black){
		playerContentString = "Noir";
	}else{
		playerContentString = "Blanc";
	}
	cout << "Au joueur " << playerContentString << " de jouer" << endl;
	displayValidMoves(playerContent,game);
}


void IO::displayFirstTurn(Board & board, Game const& game) {
	boardDisplay(board);
}

void IO::displayValidMoves(const cellContent playerContent, Game const& game) {
	std::vector<Position> v = game.validMoves(playerContent);
	cout << "Valid moves : ";
	for (int i = 0; i<v.size(); i++) {
		if (i != v.size()-1) {
			cout << v[i].toString() << " - ";
		} else {
			cout << v[i].toString() << endl;
		}
	}
}

void IO::boardDisplay(Board & board){
	cout<<"       a b c d e f g h  " << endl; //Impression des numéros de ligne
	for(unsigned int line =1; line <= 8; line++){
		cout<< "     "<<(line)<< " "; // Impression des numéros de colonne
		for(unsigned int col = 1; col <=8; col++){
			switch(board.getContentAt(Position(col,line))){
				case Empty: cout << ". "; break;
				case Black: cout << "B "; break;
				case White: cout << "W "; break;
			}
		}
		cout << (line) << endl;
	}
	cout<<"       a b c d e f g h  "<< endl;
}

void IO::displayScore(int blackScore, int whiteScore) {
	cout << "Black score : " << blackScore << " - " << "White score : " << whiteScore << endl;
	if (blackScore>whiteScore) {
		cout << "Victoire du joueur Noir" << endl;
	}
	if (whiteScore>blackScore) {
		cout << "Victoire du joueur Blanc" << endl;
	}
	if (blackScore==whiteScore) {
		cout << "Match nul" << endl;
	}
}




