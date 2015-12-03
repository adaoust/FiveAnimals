//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "Player.h"


void Player::swapSecretAnimal(Animal& animal) {
	Animal temp = animal;
	animal = secretAnimal;
	secretAnimal = temp;
}

Animal & Player::getSecretAnimal() {
	return secretAnimal;
}

void Player::print() {
	cout << "Player: " << playerName << endl;
    cout << "Secret Animal: " << AnimalCard::getAnimalString(secretAnimal) << endl;
    cout << "Hand: " << endl << endl;
    hand.print();
}

void Player::swapHand(Hand & h){
	Hand temp = hand;
	hand = h;
	h = temp;
}
