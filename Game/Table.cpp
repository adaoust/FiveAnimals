//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//
#include "Table.h"

//If direction = 0, card1 at the left of card2
//If direction = 1, card1 at the top of card2
//If direction = 2, card1 at the right of card2
//If direction = 3, card1 at the bottom of card2
int Table::match(shared_ptr<AnimalCard> card1, shared_ptr<AnimalCard> card2, int direction){
	int match = 0;
	Animal animal1;
	Animal animal2;
	Animal animal3;
	Animal animal4;
	switch (direction) {
	case 0:
		animal1 = card1->getAnimal(0, 1);
		animal2 = card2->getAnimal(0, 0);
		animal3 = card1->getAnimal(1, 1);
		animal4 = card2->getAnimal(1, 0);
		break;
	case 1:
		animal1 = card1->getAnimal(1, 0);
		animal2 = card2->getAnimal(0, 0);
		animal3 = card1->getAnimal(1, 1);
		animal4 = card2->getAnimal(0, 1);
		break;
	case 2:
		animal1 = card1->getAnimal(0, 0);
		animal2 = card2->getAnimal(0, 1);
		animal3 = card1->getAnimal(1, 0);
		animal4 = card2->getAnimal(1, 1);
		break;
	case 3:
		animal1 = card1->getAnimal(0, 0);
		animal2 = card2->getAnimal(1, 0);
		animal3 = card1->getAnimal(0, 1);
		animal4 = card2->getAnimal(1, 1);
		break;
	}

	if (animal1 == animal2) match++;
	if (animal3 == animal4 && !(animal1 == animal3 || animal2 == animal4)) match++;
	return match;
}

Table::Table(){
	table = new shared_ptr<AnimalCard> *[103];
	for (int i = 0; i < 103; i++) {
		table[i] = new shared_ptr<AnimalCard>[103];
	}
	table[52][52] = make_shared<AnimalCard>(StartCard());
}

int Table::addAt(shared_ptr<AnimalCard> card, int row, int col){
	int countMatch = 0;
	countMatch += match(table[row][col - 1], card, 0);
	countMatch += match(table[row][col + 1], card, 2);
	countMatch += match(table[row - 1][col], card, 1);
	countMatch += match(table[row + 1][col], card, 3);
	if (countMatch > 0) {
		table[row][col] = card;
	}
	else {
		throw "IllegalPlacement";
	}
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
