#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	/*
	int b(0);
	for (int a = 0; b<10; b++) {
		cout << "a : " << a << endl;
		b++;
	}
	
	int c(0);
	do {
		cin >> c;
		switch(c) {
			case 1:
				cout << "11";
				break;
			case 2:
				cout << "22";
				break;
			default:
				cout <<"def";
				break;
		}
	} while (c!=10);
	*/
	
	int* aPointer = new int;
	int& a = *aPointer;
	
	a = 4;
	
	cout << *aPointer << endl;
	
	
	return 0;
}
