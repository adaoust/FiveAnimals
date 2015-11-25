//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime BÈlair - 7432263
// CSI2772 Project
//

#ifndef HAND_H
#define HAND_H

#include "Cards/AnimalCard/AnimalCard.h"
#include <list>

using namespace std;

class Hand {
    
private :
    
    list<shared_ptr<AnimalCard>> _cards;
    
public :
    
    Hand& operator += (shared_ptr<AnimalCard>);
    Hand& operator -= (shared_ptr<AnimalCard>);
    shared_ptr<AnimalCard> operator [] (int);
    int numCards();
    void print();
    
};

#endif
