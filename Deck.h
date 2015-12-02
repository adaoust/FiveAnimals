//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>

using namespace std;

template <typename T>
class Deck : public vector<shared_ptr<T>> {

public:

	shared_ptr<T> draw() {
        shared_ptr<T> ptr = vector<shared_ptr<T>>::back();
		vector<shared_ptr<T>>::pop_back();
		return ptr;
	};
		
};

#endif
