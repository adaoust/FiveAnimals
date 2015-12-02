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
    
    void setRange();
    
protected:
    
	shared_ptr<AnimalCard> ** table;
	bool match(Animal, Animal);
    
public:
    
	Table();
	int addAt(shared_ptr<AnimalCard>, int row, int col);
	shared_ptr<AnimalCard> pickAt(int row, int col);
	shared_ptr<AnimalCard> get(int row, int col);
	bool win(string& animal);
    void print();
};

#endif 