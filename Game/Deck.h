//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime B�lair - 7432263 
// CSI2772 Project
//
#ifndef DECK_H
#define DECK_H
#include <vector>
#include <memory>

template <typename T>
class Deck : public std::vector<T> {
public:
	std::shared_ptr<T> draw() {
		T last = back();
		std::shared_ptr<T> ptr(new T(last));
		pop_back();
		return  ptr;
	};
		
};
#endif


