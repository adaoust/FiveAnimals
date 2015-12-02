//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef ACTIONCARDS_H
#define ACTIONCARDS_H

#include "AnimalCards.h"
#include "QueryResult.h"
#include "Table.h"
#include "Player.h"

class ActionCard : public NoSplit {

protected: 
	ActionCard(Animal a0) : NoSplit(a0) {}

public:
	virtual void printRow(EvenOdd);
	virtual QueryResult query() = 0;
	virtual void perfom(Table&, Player**, QueryResult) = 0;
};

class BearAction : public ActionCard {
public: 
	BearAction() : ActionCard(Animal::BEAR) {}
	QueryResult query();
	void perfom(Table&, Player**, QueryResult);
};

class DeerAction : public ActionCard {
public: 
	DeerAction() : ActionCard(Animal::DEER) {}
	QueryResult query();
	void perfom(Table&, Player**, QueryResult);
};

class HareAction : public ActionCard {
public:
	HareAction() : ActionCard(Animal::HARE) {}
	QueryResult query();
	void perfom(Table&, Player**, QueryResult);
};

class MooseAction : public ActionCard {
public: 
	MooseAction() : ActionCard(Animal::MOOSE) {}
	QueryResult query();
	void perfom(Table&, Player**, QueryResult);
};

class WolfAction : public ActionCard {
public: 
	WolfAction() : ActionCard(Animal::WOLF) {}
	QueryResult query();
	void perfom(Table&, Player**, QueryResult);
};

#endif