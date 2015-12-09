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
AnimalCardFactory::AnimalCardFactory() {

	_deck = Deck<AnimalCard>();
	_deck.push_back(make_shared<Joker>(Joker()));

	// Create 15 ActionCards.
    for (int i = 0; i < 3; i++) {
        _deck.push_back(make_shared<BearAction>(BearAction()));
        _deck.push_back(make_shared<DeerAction>(DeerAction()));
        _deck.push_back(make_shared<HareAction>(HareAction()));
        _deck.push_back(make_shared<MooseAction>(MooseAction()));
        _deck.push_back(make_shared<WolfAction>(WolfAction()));
    }
    
    // Create 5 NoSplit Cards.
    _deck.push_back(make_shared<NoSplit>(NoSplit(Animal::BEAR)));
    _deck.push_back(make_shared<NoSplit>(NoSplit(Animal::DEER)));
    _deck.push_back(make_shared<NoSplit>(NoSplit(Animal::HARE)));
    _deck.push_back(make_shared<NoSplit>(NoSplit(Animal::MOOSE)));
    _deck.push_back(make_shared<NoSplit>(NoSplit(Animal::WOLF)));
    
	// Create 10 SplitTwo Cards. (With a random orientation)
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::BEAR, Animal::DEER, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::DEER, Animal::HARE, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::HARE, Animal::MOOSE, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::MOOSE, Animal::WOLF, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::WOLF, Animal::BEAR, (bool) (rand() % 2))));

	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::BEAR, Animal::HARE, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::DEER, Animal::MOOSE, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::HARE, Animal::WOLF, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::MOOSE, Animal::BEAR, (bool) (rand() % 2))));
	_deck.push_back(make_shared<SplitTwo>(SplitTwo(Animal::WOLF, Animal::DEER, (bool) (rand() % 2))));

	// Create 20 SplitThree Card. (With a random orientation)
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::DEER, Animal::HARE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::HARE, Animal::MOOSE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::MOOSE, Animal::WOLF, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::WOLF, Animal::BEAR, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::BEAR, Animal::DEER, (int) (rand() % 4))));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::HARE, Animal::MOOSE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::MOOSE, Animal::WOLF, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::WOLF, Animal::BEAR, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::BEAR, Animal::DEER, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::DEER, Animal::HARE, (int) (rand() % 4))));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::MOOSE, Animal::WOLF, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::WOLF, Animal::BEAR, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::BEAR, Animal::DEER, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::DEER, Animal::HARE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::HARE, Animal::MOOSE, (int) (rand() % 4))));

	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::BEAR, Animal::DEER, Animal::HARE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::DEER, Animal::HARE, Animal::MOOSE, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::HARE, Animal::MOOSE, Animal::WOLF, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::MOOSE, Animal::WOLF, Animal::BEAR, (int) (rand() % 4))));
	_deck.push_back(make_shared<SplitThree>(SplitThree(Animal::WOLF, Animal::BEAR, Animal::DEER, (int) (rand() % 4))));

	// Create 15 SplitFour Cards.
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

	shuffle(begin(_deck), end(_deck), default_random_engine((int) time(0)));

}