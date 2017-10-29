#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
bool isValidInput(string s);

void move_input(){
	string move;
	cout<<"Enter your move (column row)"<<endl;
	cin>>move;
	while (!isValidInput(move)){
		cout<<"Not a valid move, try again"<<endl;
		cin>>move;
	}
}

bool isValidInput(string s){
	int a=s[1]-'0';
	if (s.size()==2 && s[0]<='h' && a>=1 && a<=8){
		return true;
	}	
	else{
		return false;
	}
}
