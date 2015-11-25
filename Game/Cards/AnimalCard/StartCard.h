//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//
#ifndef STARTCARD_H
#define STARTCARD_H
#include "NoSplit.h"
class StartCard : public NoSplit {
public:
	StartCard() {
		animals[0][0] = Animal::ALL;
		animals[0][1] = Animal::ALL;
		animals[1][0] = Animal::ALL;
		animals[1][1] = Animal::ALL;
	}
};

#endif