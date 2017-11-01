#include "IO.h"
#include "Position.h"

//bool isValidInput(string s);

void IO::moveInput(){
	string move;
	cout<<"Enter your move (column row)"<<endl;
	cin>>move;
	Position pos = Position::positionFromString(move);
	while (pos.getX()== 0){ // positionFromString() renvoie une Position(0,0) si le string n'est pas valide (donc pos.x =0)
		cout<<"Not a valid move, try again"<<endl;
		cin>>move;
		pos = Position::positionFromString(move);
		
	cout << "move accepted" << endl;
	
	}
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
