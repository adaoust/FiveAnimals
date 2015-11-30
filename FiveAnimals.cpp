//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include <iostream>
#include <string>

#include "AnimalCardFactory.h"
#include "Deck.h"

using namespace std;

int main() {
	AnimalCardFactory* factory = AnimalCardFactory::getFactory();
	Deck<AnimalCard> deck = factory->getDeck();

	while (deck.size() > 0) {
		shared_ptr<AnimalCard> card = deck.draw();

		card->printRow(EvenOdd::EVEN);
		cout << endl;
		card->printRow(EvenOdd::ODD);
		cout << endl << "--" << endl;
	}

	string s;
	cin >> s;
	return 0;
}