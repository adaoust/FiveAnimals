//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "Table.h"
#include <iomanip>

//If direction = 0, card1 at the left of card2
//If direction = 1, card1 at the top of card2
//If direction = 2, card1 at the right of card2
//If direction = 3, card1 at the bottom of card2
int Table::match(shared_ptr<AnimalCard> card1, shared_ptr<AnimalCard> card2, int direction) {
	int match = 0;
    Animal animal1 = (Animal) NULL;
	Animal animal2 = (Animal) NULL;
	Animal animal3 = (Animal) NULL;
	Animal animal4 = (Animal) NULL;
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

void Table::setRange() {
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
    // Devrait aussi permettre de jouer autour de la start card et jouer le joker.
	int countMatch = 0;
    bool besideStart = false;
    if (table[row][col - 1] != nullptr) {
        countMatch += match(table[row][col - 1], card, 0);
        if (besideStart == false) {
            besideStart = (row == startRow && col - 1 == startCol);
        }
    }
    if (table[row][col + 1] != nullptr) {
        countMatch += match(table[row][col + 1], card, 2);
        if (besideStart == false) {
            besideStart = (row == startRow && col + 1 == startCol);
        }
    }
    if (table[row - 1][col] != nullptr) {
        countMatch += match(table[row - 1][col], card, 1);
        if (besideStart == false) {
            besideStart = (row - 1 == startRow && col == startCol);
        }
    }
    if (table[row + 1][col] != nullptr) {
       countMatch += match(table[row + 1][col], card, 3);
        if (besideStart == false) {
            besideStart = (row + 1 == startRow && col == startCol);
        }
    }
	if (countMatch > 0 || besideStart) {
		table[row][col] = card;
        setRange();
	} else {
		throw string("IllegalPlacementException");
	}
	return countMatch;
}


shared_ptr<AnimalCard> Table::pickAt(int row, int col) {
	if (table[row][col]) {
		shared_ptr<AnimalCard> temp = table[row][col];
		table[row][col] = NULL;
		return temp;
	} else {
		return NULL;
	}
}

shared_ptr<AnimalCard> Table::get(int row, int col) {
	if (table[row][col]) {
		return table[row][col];
	} else {
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
        } else {
            cout << setfill('0') << setw(2) << row;
            for (int col = minCol - 1; col < maxCol + 2; col++) {
                cout << " ";
                if (get(row, col).get() != nullptr) {
                    get(row, col).get()->printRow(EvenOdd::EVEN);
                } else cout << "  ";
            }
            cout << endl << "  ";
            for (int col = minCol - 1; col < maxCol + 2; col++) {
                cout << " ";
                if (get(row, col).get() != nullptr) {
                    get(row, col).get()->printRow(EvenOdd::ODD);
                } else cout << "  ";
            }
            if (row != maxRow + 1) cout << endl << endl;
        }
    }
    cout << endl;
}

bool Table::win(string & animal) {
	return false; //impossible to win HEHEHE
}