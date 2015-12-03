//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "Table.h"
#include <iomanip>

//
bool Table::match(Animal a1, Animal a2) {
	return a1 == a2 || a1 == Animal::JOKER || a1 == Animal::START || a2 == Animal::JOKER || a2 == Animal::START;
}

Table::Table() {
	table = new shared_ptr<AnimalCard> *[103];
	for (int i = 0; i < 103; i++) {
		table[i] = new shared_ptr<AnimalCard>[103];
	}
	table[startRow][startCol] = make_shared<AnimalCard>(StartCard());
	minRow = 103, minCol = 103;
	maxRow = 0, maxCol = 0;
	setRange();
}
/*
This function is called with action card, there is a possibility when a player
want to play the HareAction (move a card on another emplacement) and he moves the card
so the card match itself (move by one tile). To prevent this, we have to remove the card
from the board before adding it at the other location. The problem is if someone play the
WolfAction (remove a card from the table) before and the card we want to move is disconnected,
we won't be able to insert the card again. So we will call this function that will allow us
to put a card on the table without performing any check
(note it's only in that particular case we will use this function)
*/
void Table::addWithoutCheck(shared_ptr<AnimalCard> card, int row, int col) {
	table[row][col] = card;
	setRange();
}

void Table::setRange() {
    
    // Reset the values so that if the table gets smaller it still works.
    minRow = 103, minCol = 103;
    maxRow = 0, maxCol = 0;
    
	for (int i = 0; i < 103; i++) {
		for (int j = 0; j < 103; j++) {
			if (table[i][j] != NULL) {
				minRow = (i < minRow) ? i : minRow;
				minCol = (j < minCol) ? j : minCol;
				maxRow = (i > maxRow) ? i : maxRow;
				maxCol = (j > maxCol) ? j : maxCol;
			}
		}
	}
}

int Table::addAt(shared_ptr<AnimalCard> card, int row, int col) {
	if (table[row][col] != nullptr) {
		throw string("IllegalPlacementException");
	}
	int countMatch = 0;
	if (card->getAnimal(0, 0) == Animal::JOKER) {
		countMatch += (table[row - 1][col] == nullptr) ? 0 : 1;
		countMatch += (table[row + 1][col] == nullptr) ? 0 : 1;
		countMatch += (table[row][col - 1] == nullptr) ? 0 : 1;
		countMatch += (table[row][col + 1] == nullptr) ? 0 : 1;
		if (countMatch < 1) {
			throw string("IllegalPlacementException");
		}
		table[row][col] = card;
		setRange();
		return countMatch;
	}
	//variable temporaire pour savoir si les animaux aux positions 1,2,3 ou 4 ont un match
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

	if ((col != 0 && table[row][col - 1] != nullptr && match(card->getAnimal(0, 0), table[row][col - 1]->getAnimal(0, 1))) || (row != 0 && table[row - 1][col] != nullptr && match(card->getAnimal(0, 0), table[row - 1][col]->getAnimal(1, 0)))) {
		count1 = 1;
		countMatch++;
	}
	//animal at 0,0 and 0,1 are the same and is already matched
	if (match(card->getAnimal(0, 0), card->getAnimal(0, 1)) && count1 == 1) {
		count2 = 1;
	}
	else {
		if ((row != 0 && table[row - 1][col] != nullptr && match(card->getAnimal(0, 1), table[row - 1][col]->getAnimal(1, 1))) || (col != 102 && table[row][col + 1] != nullptr && match(card->getAnimal(0, 1), table[row][col + 1]->getAnimal(0, 0)))) {
			count2 = 1;
			countMatch++;
		}
	}

	//animal at 0,0 and 1,0 are the same and is already matched
	if (match(card->getAnimal(0, 0), card->getAnimal(1, 0)) && count1 == 1) {
		count3 = 1;
	}
	else {
		if ((col != 0 && table[row][col - 1] != nullptr && match(card->getAnimal(1, 0), table[row][col - 1]->getAnimal(1, 1))) || (row != 102 && table[row + 1][col] != nullptr && match(card->getAnimal(1, 0), table[row + 1][col]->getAnimal(0, 0)))) {
			count3 = 1;
			countMatch++;
		}
	}

	//animal at 1,0 and 1,1 are the same and is already matched
	if (match(card->getAnimal(1, 0), card->getAnimal(1, 1)) && count3 == 1) {
		count4 = 1;
	}
	//animal at 0,1 and 1,1 are the same and is already matched
	else if (match(card->getAnimal(0, 1), card->getAnimal(1, 1)) && count2 == 1) {
		count4 = 1;
	}
	else {
		if ((col != 102 && table[row][col + 1] != nullptr && match(card->getAnimal(1, 1), table[row][col + 1]->getAnimal(1, 0))) || (row != 102 && table[row + 1][col] != nullptr && match(card->getAnimal(1, 1), table[row + 1][col]->getAnimal(0, 1)))) {
			count4 = 1;
			countMatch++;
		}
	}
	if (countMatch < 1) {
		throw string("IllegalPlacementException");
	}
	table[row][col] = card;
	setRange();
	return countMatch;
}


shared_ptr<AnimalCard> Table::pickAt(int row, int col) {
	if (table[row][col]) {
		shared_ptr<AnimalCard> temp = table[row][col];
		table[row][col] = NULL;
		setRange();
		return temp;
	}
	else {
		return NULL;
	}
}

shared_ptr<AnimalCard> Table::get(int row, int col) {
	if (table[row][col]) {
		return table[row][col];
	}
	else {
		return NULL;
	}
}

void Table::print() {
	// Printing column and row numbers for clarity.
	// Also adding a column and row at the end of the table.
	cout << "Table: " << endl << endl;
	for (int row = minRow - 2; row < maxRow + 2; row++) {
		if (row == minRow - 2) {
			cout << "   ";
			for (int col = minCol - 1; col < maxCol + 2; col++) {
				cout << setfill('0') << setw(2) << col << setfill(' ') << setw(1) << ' ';
			}
			cout << endl << endl;
		}
		else {
			cout << setfill('0') << setw(2) << row;
			for (int col = minCol - 1; col < maxCol + 2; col++) {
				cout << " ";
				if (get(row, col).get() != nullptr) {
					get(row, col).get()->printRow(EvenOdd::EVEN);
				}
				else cout << "  ";
			}
			cout << endl << "  ";
			for (int col = minCol - 1; col < maxCol + 2; col++) {
				cout << " ";
				if (get(row, col).get() != nullptr) {
					get(row, col).get()->printRow(EvenOdd::ODD);
				}
				else cout << "  ";
			}
			if (row != maxRow + 1) cout << endl << endl;
		}
	}
	cout << endl;
}

bool Table::win(string & animal) {
	return false; //impossible to win HEHEHE
}