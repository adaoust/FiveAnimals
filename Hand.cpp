//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#include "Hand.h"

Hand& Hand::operator += (shared_ptr<AnimalCard> card) {
	_cards.push_back(card);
	return *this;
}

Hand& Hand::operator -= (shared_ptr<AnimalCard> card) {
	long sizeBefore = _cards.size();
	_cards.remove(card);
	if (sizeBefore == _cards.size()) throw "MissingCardException";
	return *this;
}

shared_ptr<AnimalCard> Hand::operator [] (int index) {
	if (_cards.size() > index) {
		return *next(_cards.begin(), index);
	}
	else throw "IndexOutOfBoundsException";
}

int Hand::numCards() {
	return (int)_cards.size();
}

void Hand::print() {

	for (int i = 0; i < numCards(); i++) {
		cout << setfill('0') << setw(2) << (i + 1) << setfill(' ') << setw(1) << ' ';
	}
	cout << endl;
	for (int i = 0; i < numCards(); i++) {
		(*this)[i]->printRow(EvenOdd::EVEN);
        cout << " ";
	}
	cout << endl;
	for (int i = 0; i < numCards(); i++) {
        (*this)[i]->printRow(EvenOdd::ODD);
        cout << " ";
	}
	cout << endl;

}