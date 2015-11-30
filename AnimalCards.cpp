//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#include "AnimalCards.h"

#include <iostream>

using namespace std;

char AnimalCard::getAnimalChar(Animal animal) {
	switch (animal) {
	case Animal::BEAR: return 'b';
	case Animal::DEER: return 'd';
	case Animal::HARE: return 'h';
	case Animal::MOOSE: return 'm';
	case Animal::WOLF: return 'w';
	case Animal::JOKER: return 'j';
	case Animal::START: return 'c';
	default: return ' ';
	}
}

void AnimalCard::printRow(EvenOdd evenOdd) {
	switch (evenOdd) {
	case EvenOdd::EVEN:
		cout << getAnimalChar(_animals[0][0]) << getAnimalChar(_animals[0][1]);
		break;
	case EvenOdd::ODD:
		cout << getAnimalChar(_animals[1][0]) << getAnimalChar(_animals[1][1]);
		break;
	default: 
		cout << "  ";
	}
}