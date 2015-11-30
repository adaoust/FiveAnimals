//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

using namespace std;

class Player {

protected:

	string playerName;
	string secretAnimal;
	//Hand hand;

public:

	Player(string name, string animal) {
		playerName = name;
		secretAnimal = animal;
	}
	string swapSecretAnimal(string&);
	string getSecretAnimal();
	void print();

};

#endif
