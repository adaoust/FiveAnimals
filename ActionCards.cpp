//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "ActionCards.h"

void ActionCard::printRow(EvenOdd evenOdd) {
	switch (evenOdd) {
	case EvenOdd::EVEN:
		cout << (char)toupper(getAnimalChar(_animals[0][0])) << (char) toupper(getAnimalChar(_animals[0][1]));
		break;
	case EvenOdd::ODD:
		cout << (char) toupper(getAnimalChar(_animals[1][0])) << (char) toupper(getAnimalChar(_animals[1][1]));
		break;
	default:
		cout << "  ";
	}
}

// Bear Action.
QueryResult BearAction::query() {
	return QueryResult();
}

void BearAction::perfom(Table& table, Player* player, QueryResult queryResult) {
}
 
// Deer Action.
QueryResult DeerAction::query() {
	return QueryResult();
}

void DeerAction::perfom(Table& table, Player* player, QueryResult queryResult) {
}

// Hare Action.
QueryResult HareAction::query() {
	return QueryResult();
}

void HareAction::perfom(Table& table, Player* player, QueryResult queryResult) {
}

// Moose Action.
QueryResult MooseAction::query() {
	return QueryResult();
}

void MooseAction::perfom(Table& table, Player* player, QueryResult queryResult) {
}

// Wolf Action.
QueryResult WolfAction::query() {
	return QueryResult();
}

void WolfAction::perfom(Table& table, Player* player, QueryResult queryResult) {
}