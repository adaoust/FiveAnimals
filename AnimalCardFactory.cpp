//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263
// CSI2772 Project
//

#include "AnimalCardFactory.h"

#include "ActionCards.h"
#include "AnimalCards.h"
#include <algorithm>
#include <random>

AnimalCardFactory::AnimalCardFactory() {

	// Seed for random permutations of cards.
	srand((int) time(0));

	_deck = Deck<AnimalCard>();
	_deck.push_back(make_shared<AnimalCard>(Joker()));

	// Create 5 ActionCards.
	_deck.push_back(make_shared<BearAction>(BearAction()));
	_deck.push_back(make_shared<DeerAction>(DeerAction()));
	_deck.push_back(make_shared<HareAction>(HareAction()));
	_deck.push_back(make_shared<MooseAction>(MooseAction()));
	_deck.push_back(make_shared<WolfAction>(WolfAction()));

	// Create 10 SplitTwo Cards.
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::BEAR, Animal::DEER)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::DEER, Animal::HARE)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::HARE, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::WOLF, Animal::BEAR)));

	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::BEAR, Animal::HARE)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::DEER, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::HARE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::MOOSE, Animal::BEAR)));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::WOLF, Animal::DEER)));

	// Create 20 SplitThree
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::DEER, Animal::HARE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::HARE, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::WOLF, Animal::BEAR)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::BEAR, Animal::DEER)));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::HARE, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::WOLF, Animal::BEAR)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::BEAR, Animal::DEER)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::DEER, Animal::HARE)));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::WOLF, Animal::BEAR)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::BEAR, Animal::DEER)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::DEER, Animal::HARE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::HARE, Animal::MOOSE)));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::DEER, Animal::HARE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::HARE, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::WOLF, Animal::BEAR)));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::BEAR, Animal::DEER)));

	// Create 15 SplitFour
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::BEAR, Animal::DEER, Animal::HARE, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::DEER, Animal::HARE, Animal::MOOSE, Animal::WOLF)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::HARE, Animal::MOOSE, Animal::WOLF, Animal::BEAR)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::MOOSE, Animal::WOLF, Animal::BEAR, Animal::DEER)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::WOLF, Animal::BEAR, Animal::DEER, Animal::HARE)));

	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::BEAR, Animal::DEER, Animal::MOOSE, Animal::HARE)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::DEER, Animal::HARE, Animal::WOLF, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::HARE, Animal::MOOSE, Animal::BEAR, Animal::WOLF)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::MOOSE, Animal::WOLF, Animal::DEER, Animal::BEAR)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::WOLF, Animal::BEAR, Animal::HARE, Animal::DEER)));

	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::BEAR, Animal::MOOSE, Animal::HARE, Animal::DEER)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::DEER, Animal::WOLF, Animal::MOOSE, Animal::HARE)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::HARE, Animal::BEAR, Animal::WOLF, Animal::MOOSE)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::MOOSE, Animal::DEER, Animal::BEAR, Animal::WOLF)));
	_deck.push_back(make_shared<SplitFour>(SplitFour(Animal::WOLF, Animal::HARE, Animal::DEER, Animal::BEAR)));

	shuffle(begin(_deck), end(_deck), default_random_engine());

}