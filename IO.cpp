#include "IO.h"

//bool isValidInput(string s);

Position IO::moveInput(Game const & game, cellContent playerContent){
	string move;
	cout<<"Enter your move (column row)"<<endl;
	cin>>move;
	Position pos = Position::positionFromString(move);
	while (!pos->isValid()){ // positionFromString() renvoie une Position(0,0) si le string n'est pas valide (donc pos.x =0)
		cout<<"Not a correct syntax, try again"<<endl;
		cin>>move;
		pos = Position::positionFromString(move);
		
	}
	cout << "syntax accepted" << endl;
	
	
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
