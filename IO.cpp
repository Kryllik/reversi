#include "IO.h"
//bool isValidInput(string s);

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
				cout << "not valid move" << endl;
			}
		} else {
			cout << "Not a correct syntax, try again" << endl;
		}
	}
}

void IO::display(Board & board, cellContent playerContent){
	string playerContentString;
	if(playerContent== Black){
		playerContentString = "Noir";
	}
	else{
		playerContentString = "Blanc";
	}
	cout << "C'est au joueur " << playerContentString << " de jouer" << endl;
	cout << "mise à jour du board " << endl;
	board.display();
	cout << "" << endl; 
}
	

/*
bool isValidInput(string s){
	int a=s[1]-'0';
	if (s.size()==2 && s[0]<='h' && a>=1 && a<=8){
		return true;
	}	
	else{
		return false;
	}
}*/
