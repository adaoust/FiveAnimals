//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#include "AnimalCards.h"

#include <iostream>

using namespace std;

string getAnimalString(const Animal animal) {
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

char getAnimalChar(const Animal animal) {
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

Animal getAnimal(string animal) {
    if (animal == "Bear" || animal == "b") return Animal::BEAR;
    else if (animal == "Deer" || animal == "d") return Animal::DEER;
    else if (animal == "Hare" || animal == "h") return Animal::HARE;
    else if (animal == "Moose" || animal == "m")  return Animal::MOOSE;
    else if (animal == "Wolf" || animal == "w")  return Animal::WOLF;
    else if (animal == "Joker" || animal == "j")  return Animal::JOKER;
    else if (animal == "Start" || animal == "c")  return Animal::START;
    else return (Animal) NULL;
}

Animal getAnimal(char animal) {
    if (animal == 'b') return Animal::BEAR;
    else if (animal == 'd') return Animal::DEER;
    else if (animal == 'h') return Animal::HARE;
    else if (animal == 'm')  return Animal::MOOSE;
    else if (animal == 'w')  return Animal::WOLF;
    else if (animal == 'j')  return Animal::JOKER;
    else if (animal == 'c')  return Animal::START;
    else return (Animal) NULL;
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