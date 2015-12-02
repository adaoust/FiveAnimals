//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "AnimalCards.h"

#include <string>
#include <iostream>

using namespace std;

class Player {

protected:

	string playerName;
	Animal secretAnimal;
	Hand hand;

public:

    // Asked the teacher to change secret animal from string to Animal.
	Player(string name, Animal animal) {
		playerName = name;
		secretAnimal = animal;
        hand = Hand();
	}
    
	void swapSecretAnimal(Animal&);
	Animal getSecretAnimal();
    
    void print();
    Hand& getHand() { return hand; }

};

#endif
