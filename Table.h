//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <memory>
#include "AnimalCards.h"

using namespace std;

class Table {
    
private:
    
    static const int startRow = 52;
    static const int startCol = 52;
    
    int minRow;
    int maxRow;
    int minCol;
    int maxCol;

	//keep how many of each animals there is on the board
	int numBear = 0;
	int numDeer = 0;
	int numHare = 0;
	int numMoose = 0;
	int numWolf = 0;
	void updateAnimalCount(shared_ptr<AnimalCard> card, bool isAddAction);
	void updateAnimalCount(Animal animal, bool isAddAction);
    
    void setRange();
    
protected:
    
	shared_ptr<AnimalCard> ** table;
	bool match(Animal, Animal);
    
public:
    
	Table();
	void addWithoutCheck(shared_ptr<AnimalCard>, int row, int col);
	int addAt(shared_ptr<AnimalCard>, int row, int col);
	shared_ptr<AnimalCard> pickAt(int row, int col);
	shared_ptr<AnimalCard> get(int row, int col);
	bool win(Animal& animal);
    void print();
};

#endif 