//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#ifndef HAND_H
#define HAND_H

#include "AnimalCards.h"

#include <list>
#include <memory>
#include <iomanip>
#include <iostream>

using namespace std;

class Hand {

private:

	list<shared_ptr<AnimalCard>> _cards;

public:

	Hand& operator += (shared_ptr<AnimalCard>);
	Hand& operator -= (shared_ptr<AnimalCard>);
	shared_ptr<AnimalCard> operator [] (int);
	int numCards();
	void print();

};

#endif