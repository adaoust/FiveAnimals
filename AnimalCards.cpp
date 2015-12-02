//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#include "AnimalCards.h"

#include <iostream>

using namespace std;

string AnimalCard::getAnimalString(const Animal animal) {
    switch (animal) {
        case Animal::BEAR: return "Bear";
        case Animal::DEER: return "Deer";
        case Animal::HARE: return "Hare";
        case Animal::MOOSE: return "Moose";
        case Animal::WOLF: return "Wolf";
        case Animal::JOKER: return "Joker";
        case Animal::START: return "Start";
        default: return " ";
    }
}

char AnimalCard::getAnimalChar(const Animal animal) {
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
		cout << getAnimalChar(getAnimal(0,0)) << getAnimalChar(getAnimal(0,1));
		break;
	case EvenOdd::ODD:
		cout << getAnimalChar(getAnimal(1,0)) << getAnimalChar(getAnimal(1,1));
		break;
	default: 
		cout << "  ";
	}
}