//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "Player.h"

//why return ?!?! dis is stupid
string Player::swapSecretAnimal(string & animal) {
	string temp = animal;
	animal = secretAnimal;
	secretAnimal = temp;
	return secretAnimal;
}

string Player::getSecretAnimal() {
	return secretAnimal;
}

void Player::print() {
	cout << "Player Name: " << playerName << endl;
	cout << "Secret Animal: " << secretAnimal << endl;
	//	cout << "Hand: " << endl  << hand.print();
}