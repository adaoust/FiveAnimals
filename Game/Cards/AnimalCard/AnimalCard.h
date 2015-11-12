//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//
#ifndef ANIMALCARD_H
#define ANIMALCARD_H
enum class Orientation { UP, DOWN };
enum class EvenOdd { EVEN, ODD };

class AnimalCard {
protected:
	Orientation orientation;
	EvenOdd evenOdd;
	//Array that contain the card information, the animals are displayed like that on the card:
	// animal[0] animal[1]
	// animal[2] animal[3]
	char animal[4];
public:
	virtual void setOrientation(Orientation o) { orientation = o; };
	virtual void setRow(EvenOdd eo) { evenOdd = eo; };
	//why pass EvenOdd in parameter ?! to complete later...
	virtual void printRow(EvenOdd) {};
};
#endif 