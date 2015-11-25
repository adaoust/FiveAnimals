//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//
#include "Table.h"

Table::Table(){
	table = new shared_ptr<AnimalCard> *[103];
	for (int i = 0; i < 103; i++) {
		table[i] = new shared_ptr<AnimalCard>[103];
	}
	table[52][52] = make_shared<AnimalCard>(StartCard());
}

int Table::addAt(shared_ptr<AnimalCard> card, int row, int col){
	int countMatch;
	table[row][col] = card;
	return countMatch;
}

shared_ptr<AnimalCard> Table::pickAt(int row, int col){
	if (table[row][col]) {
		shared_ptr<AnimalCard> temp = table[row][col];
		table[row][col] = make_shared<AnimalCard>();
		return temp;
	}
	else {
		return make_shared<AnimalCard>();
	}
}

shared_ptr<AnimalCard> Table::get(int row, int col){
	if (table[row][col]) {
		return table[row][col];
	}
	else {
		return make_shared<AnimalCard>();
	}
}

bool Table::win(string & animal){
	return false; //impossible to win HEHEHE
}
