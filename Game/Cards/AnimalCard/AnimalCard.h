//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//
#ifndef ANIMALCARD_H
#define ANIMALCARD_H

enum class Animal { BEAR, DEER, HARE, MOOSE, WOLF, ALL };
enum class Orientation { UP, DOWN };
enum class EvenOdd { EVEN, ODD };

class AnimalCard {
protected:
	Orientation orientation;
	EvenOdd evenOdd;
	Animal animals [2][2];
public:
	virtual void setOrientation(Orientation o) { orientation = o; };
	virtual void setRow(EvenOdd eo) { evenOdd = eo; };
	virtual void printRow(EvenOdd) {};
	virtual Animal getAnimal(int i, int j) {
		if (orientation == Orientation::UP) {
			return animals[i][j];
		}else {			
			return animals[i == 0 ? 1 : 0][j == 0 ? 1 : 0];
		}
	};
};
#endif