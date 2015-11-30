//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef ANIMALCARDFACTORY_H
#define ANIMALCARDFACTORY_H

#include "Deck.h"
#include "AnimalCards.h"

using namespace std;

class AnimalCardFactory {

private:

	AnimalCardFactory(); // Prevents creation
	AnimalCardFactory(const AnimalCardFactory&) {} // Prevents copy constructor
	AnimalCardFactory& operator= (const AnimalCardFactory&) {} // Prevents Assignment

	Deck<AnimalCard> _deck;

public:

	static AnimalCardFactory* getFactory() {
		static AnimalCardFactory* _factory = new AnimalCardFactory();
		return _factory;
	}

	Deck<AnimalCard> getDeck() {
		return _deck;
	}

};

#endif